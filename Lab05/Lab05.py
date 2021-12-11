import subprocess
import re

def runLab5(filePath, min_threads_num, max_threads_num, output_file):
    with open(output_file, 'w+') as output:
        for i in range(min_threads_num, max_threads_num+1):
            print(f"start: {i}")
            process = subprocess.run(['C:\\Program Files\\Microsoft MPI\\Bin\\mpiexec.exe', '-n', str(i), filePath], capture_output=True, encoding='utf-8')
            print(f"stop: {i}")
            time_str = re.search(r"czas\s(\d+\.\d*)", process.stdout).group(1)
            output.writelines(f'{i}\t{time_str}\n')
            print(f"\n========= {i} =========\n" + process.stdout + "\n\n")

if __name__ == '__main__':
    runLab5('..\\x64\\Release\\Lab05.pi.exe', 1, 16, 'Lab05.pi.txt')
    runLab5('..\\x64\\Release\\Lab05.matrix.exe', 2, 16, 'Lab05.matrix.txt')