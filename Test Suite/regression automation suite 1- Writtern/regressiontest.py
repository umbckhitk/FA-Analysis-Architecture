import subprocess
import os
import time
import shutil
from datetime import datetime, timedelta

def run_cpp_test(cpp_file, results_dir, duration_hours=1):

    base_name = os.path.splitext(os.path.basename(cpp_file))[0]  # Filename without extension
    test_dir = os.path.join(results_dir, base_name)  
    os.makedirs(test_dir, exist_ok=True)

    start_time = datetime.now()
    end_time = start_time + timedelta(hours=duration_hours)

    log_file = os.path.join(test_dir, f"{base_name}.log")
    result_file = os.path.join(test_dir, f"{base_name}.result")  

    with open(log_file, "w") as log:
        while datetime.now() < end_time:
            try:
                exe_file = os.path.join(test_dir, base_name)
                if not os.path.exists(exe_file) or os.path.getmtime(cpp_file) > os.path.getmtime(exe_file):
                    compile_cmd = ["g++", cpp_file, "-o", exe_file]  
                    subprocess.run(compile_cmd, check=True, stderr=subprocess.PIPE) 

                run_cmd = [exe_file]  
                
                process = subprocess.Popen(run_cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

                while True:
                    stdout_line = process.stdout.readline()
                    if not stdout_line:
                        break
                    print(stdout_line.decode().strip())  
                    log.write(stdout_line.decode())  # Write to log file

                stdout, stderr = process.communicate() 
                log.write(stdout.decode())
                log.write(stderr.decode())

                with open(result_file, "a") as result:  
                    result.write(f"Run at {datetime.now()}: ")
                    if process.returncode == 0:
                        result.write("PASS\n")
                    else:
                        result.write(f"FAIL (Return code: {process.returncode})\n")
                        result.write(stderr.decode()) 

                time.sleep(1)

            except subprocess.CalledProcessError as e:
                print(f"Compilation error for {cpp_file}: {e.stderr.decode()}")
                with open(log_file, "a") as log:
                    log.write(f"Compilation error: {e.stderr.decode()}")
                return 
            except Exception as e:
                print(f"Error running {cpp_file}: {e}")
                with open(log_file, "a") as log:
                    log.write(f"Error: {e}")
                return  

def main():
    test_suite_dir = "Memory Testing -soc" 
    results_dir = "results"
    os.makedirs(results_dir, exist_ok=True)

    for root, _, files in os.walk(test_suite_dir):
        for file in files:
            if file.endswith(".cpp"):
                cpp_file = os.path.join(root, file)
                print(f"Running test: {cpp_file}")
                run_cpp_test(cpp_file, results_dir)
                print(f"Finished test: {cpp_file}")

if __name__ == "__main__":
    main()