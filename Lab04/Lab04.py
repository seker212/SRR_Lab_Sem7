import subprocess
import re

def runLab4(filePath, max_threads_num, output_file):
    with open(output_file, 'w+') as output:
        for i in range(1, max_threads_num+1):
            print(f"start: {i}")
            process = subprocess.run(['C:\\Program Files\\Microsoft MPI\\Bin\\mpiexec.exe', '-n', str(i), filePath], capture_output=True, encoding='utf-8')
            print(f"stop: {i}")
            time_str = re.search(r"czas\s(\d+)\s\sms", process.stdout).group(1)
            output.writelines(f'{i}\t{time_str}\n')
            print(f"\n========= {i} =========\n" + process.stdout + "\n\n")

if __name__ == '__main__':
    runLab4('..\\x64\\Release\\Lab04.exe', 16, 'Lab04.txt')