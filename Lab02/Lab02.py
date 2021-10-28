import subprocess
import re

def runLab2(filePath, max_threads_num, output_file):
    with open(output_file, 'w+') as output:
        for i in range(1, max_threads_num+1):
            print(f"start: {i}")
            process = subprocess.run([filePath, str(i), '878', '800', '900'], capture_output=True, encoding='utf-8')
            print(f"stop: {i}")
            time_str = re.search(r"Time:\s(\d+\.\d*)\ss", process.stdout).group(1)
            output.writelines(f'{i}\t{time_str}\n')
            print(f"\n========= {i} =========\n" + process.stdout + "\n\n")

if __name__ == '__main__':
    runLab2('..\\x64\\Debug\\Lab02.exe', 16, 'd64.txt')
    runLab2('..\\x64\\Release\\Lab02.exe', 16, 'r64.txt')
    runLab2('..\\Win32\\Debug\\Lab02.exe', 16, 'd32.txt')
    runLab2('..\\Win32\\Release\\Lab02.exe', 16, 'r32.txt')