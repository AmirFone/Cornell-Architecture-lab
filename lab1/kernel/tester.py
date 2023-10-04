# "python script.py <num_iterations> "<command>""

# srun -p ece5755 -n 1 --mem=1g -w slurm-instructional-compute-01 --pty /bin/bash
import subprocess
import sys
import csv
import re
def execute_srun():
    try:
        srun_output = subprocess.check_output("srun -p ece5755 -n 1 --mem=1g -w slurm-instructional-compute-01 --pty /bin/bash", shell=True, stderr=subprocess.STDOUT, text=True)
        print("srun executed successfully!")
    except subprocess.CalledProcessError as e:
        print(f"Error running the 'srun' command: {e.output}")
        sys.exit(1)

def run_command(command):
    try:
        command= "python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0" +" "+ command
        output = subprocess.check_output(command, shell=True, stderr=subprocess.STDOUT, text=True)
        print(output)
        return output
    except subprocess.CalledProcessError as e:
        print(f"Error running the command: {e.output}")
        return ""

def main(num_iterations, command):
    # List to store output
    output_list = []

    # Run the command multiple times
    for i in range(num_iterations):
        print("Iteration: " + str(i))
        output = run_command(command)
        output_list.append(output)
    # Aggregate output 
    # print(type(output_list),type(output_list[1]))
    # print(output_list[1])
    data={'FE':[],'BAD':[],'BE':[],'RET':[],'MUX':[]}
    for rus in output_list:
        for line in rus.split("\n")[:-2]:
            for key in data.keys():
                if key in line:
                    data[key].append(float('.'.join(re.findall(r'\d+\.\d+|\d+', line))))
        
    filename = 'rul.csv'

    with open(filename, 'w', newline='') as csvfile:
        csvwriter = csv.writer(csvfile)
        
        # Write data
        for key, values in data.items():
            csvwriter.writerow([key] + values)
            
    print(f"Data written to {filename}")


if __name__ == "__main__":
    # execute_srun()
    if len(sys.argv) >= 3:
        num_iterations = int(sys.argv[1])
        command = sys.argv[2]
    else:
        # Default values
        num_iterations = 100
        command = "python3 /usr/local/pmu-tools/pmu-tools/toplev.py --core S0-C0 -l1 -v --no-desc taskset -c 0 ./bubble 5000 input_5000"

    main(num_iterations, command)



