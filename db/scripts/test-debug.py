import asyncio
import asyncpg
import pandas as pd
import dotenv
import os


async def insert_debugged_processes(csv_file: str) -> None:
    """
    Reads a CSV file and inserts its data into the DebuggedProcesses table.
    """
    # Load environment variables
    dotenv.load_dotenv()
    conn_str = os.getenv("POSTGRES_CONN_STR")
    if not conn_str:
        print("Error: POSTGRES_CONN_STR not set in .env file.")
        return

    # Read the CSV file into a pandas DataFrame
    try:
        df = pd.read_csv(csv_file)
    except Exception as e:
        print(f"Error reading CSV file: {e}")
        return

    # Connect to the database
    conn = await asyncpg.connect(conn_str)
    try:
        for _, row in df.iterrows():
            # Handle missing DebugStartTime
            debug_start_time = row['DebugStartTime'] if not pd.isna(row['DebugStartTime']) else None
            try:
                await conn.execute(
                    """
                    INSERT INTO DebuggedProcesses (ProcessName, ProcessPid, DebugStartTime)
                    VALUES ($1, $2, $3)
                    """,
                    row['ProcessName'], 
                    row['ProcessPid'], 
                    debug_start_time
                )
                print(f"Inserted: {row['ProcessName']} (PID: {row['ProcessPid']})")
            except Exception as e:
                print(f"Error inserting row: {row}. Error: {e}")

    finally:
        await conn.close()
        print("Database connection closed.")


if __name__ == "__main__":
    # Replace 'debugged_processes.csv' with the actual path to your CSV file
    csv_file_path = "debugged_processes.csv"
    asyncio.run(insert_debugged_processes(csv_file_path))
