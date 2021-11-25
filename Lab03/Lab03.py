import subprocess
import re

def runLab3(filePath, max_threads_num, output_file):
    with open(output_file, 'w+') as output:
        for i in range(1, max_threads_num+1):
            print(f"start: {i}")
            process = subprocess.run([filePath, str(i)], capture_output=True, encoding='utf-8')
            print(f"stop: {i}")
            time_str = re.search(r"czas\s\s(\d+\.\d*)", process.stdout).group(1)
            output.writelines(f'{i}\t{time_str}\n')
            print(f"\n========= {i} =========\n" + process.stdout + "\n\n")

if __name__ == '__main__':
    runLab3('..\\x64\\Release\\Lab03.exe', 16, 'Lab03.pi_r64(PAD8).txt')