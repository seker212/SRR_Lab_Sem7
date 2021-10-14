import os
import subprocess
import re
from types import prepare_class

def runLab1(filePath, max_threads_num):
    with open('lab01.txt', 'w+') as output:
        for i in range(1, max_threads_num+1):
            print(f"start: {i}")
            process = subprocess.run([filePath, str(i)], capture_output=True, encoding='utf-8')
            print(f"stop: {i}")
            time_str = re.search(r"czas\s+(\d+\.\d*)\ss", process.stdout).group(1)
            output.writelines(f'{i}\t{time_str}\n')
            print(f"\n========= {i} =========\n" + process.stdout + "\n\n")

if __name__ == '__main__':
    # runLab1('.\\x64\\Release\\Lab01.exe', 24)
    runLab1('.\\Debug\\Lab01.exe', 24)
