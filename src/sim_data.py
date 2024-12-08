import csv
import random
import time
from datetime import datetime

# Function to generate random data for CSV
def generate_random_data():
    # Random timestamp: simulate a realistic timestamp (within the past 24 hours)
    random_timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Random PID (between 1000 and 9999 for simplicity)
    random_pid = random.randint(1000, 9999)

    # Random process name (can be anything like a file name, for example)
    process_names = [
        "/usr/bin/python3", "/usr/bin/bash", "/usr/local/bin/app", "/usr/bin/nginx", 
        "/usr/bin/clang", "/bin/bash", "/usr/bin/firefox", "/usr/bin/gcc"
    ]
    random_process_name = random.choice(process_names)

    return [random_timestamp, random_pid, random_process_name]

# Path to the CSV file
csv_file = 'debugged_processes.csv'

# Writing the CSV file
with open(csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)

    # Write the header
    writer.writerow(["Timestamp", "PID", "Process Name"])

    # Generate and write 100 rows of random data
    for _ in range(100):
        writer.writerow(generate_random_data())

print(f"CSV file '{csv_file}' generated successfully with 100 random rows.")
