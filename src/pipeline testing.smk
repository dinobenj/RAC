# Define input/output files
debug_csv = "debugged_processes.csv"
db_output = "database_inserted.log"
final_output = "process_report.txt"

rule all:
    input:
        final_output

rule create_debugged_csv:
    output:
        debug_csv
    shell:
        """
        python generate_process_data.py > {output}
        """

rule check_csv:
    input:
        debug_csv
    output:
        temp("checked.csv")
    run:
        import pandas as pd
        df = pd.read_csv(input[0])
        if not df.empty:
            df.to_csv(output[0], index=False)
        else:
            open(output[0], "w").close()

rule send_to_database:
    input:
        "checked.csv"
    output:
        db_output
    run:
        import os
        if os.path.getsize(input[0]) > 0:  # Check if the file is non-empty
            import asyncio
            from your_insert_script import insert_debugged_processes
            asyncio.run(insert_debugged_processes(input[0]))
            with open(output[0], "w") as f:
                f.write("Database updated successfully.\n")
        else:
            with open(output[0], "w") as f:
                f.write("No data to update.\n")

rule process_and_output:
    input:
        debug_csv
    output:
        final_output
    shell:
        """
        python analyze_process_data.py --input {input} --output {output}
        """
