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
        ""

rule check_csv:
    input:
        debug_csv
    output:
        temp("checked.csv")
    run:
        import pandas as pd
        # Read the CSV
        df = pd.read_csv(input[0])
        if not df.empty:
            # Save the filtered data (if any) for further processing
            df.to_csv(output[0], index=False)
rule check output:
    input:
        {output}.csv
    output:
        final_output
    shell:
        """
        python {output}.py --input {input} --output {output}
        """