import subprocess
import time

# Command to run the binary
command = "./lab5"

# Start measuring time
start_time = time.time()

# Run the binary and capture its output
try:
    process = subprocess.Popen(
        command,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        universal_newlines=True,
        shell=True
    )

    # Print output line by line
    for line in process.stdout:
        print(line.strip())

    process.wait()
except subprocess.CalledProcessError as e:
    print("Error:", e)
finally:
    # Calculate and print execution time
    end_time = time.time()
    execution_time = end_time - start_time
    print(f"Execution time: {execution_time:.2f} seconds")
