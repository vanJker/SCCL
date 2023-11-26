import os
import subprocess
import sys

def execute_command(file_path, flag, target):
    print('{}: ...'.format(file_path), end='')

    command = 'tiny.out {} {}'.format(tiny_flag, file_path)
    test_output = subprocess.check_output(command, shell=True, text=True)
    if flag in ['-p', '--print'] and target in [None, file_path]:
        print(test_output)

    grep_command = 'grep error'
    result = subprocess.run(grep_command, input=test_output, shell=True, text=True, capture_output=True)

    if result.returncode == 0:
        print("failed")
        print(test_output)
        return 1
    else:
        print("ok")
        return 0

def traverse_folder(folder_path, flag, target):
    for root, dirs, files in os.walk(folder_path):
        for file in files:
            if file == 'sample.tny':
                continue
            file_path = os.path.join(root, file)
            if execute_command(file_path, flag, target) == 1:
                print("\n===TESTS FAILED===\n")
                sys.exit(1)
        print("\n===ALL TESTS PASSED===\n")
            

tiny_flag = None
if len(sys.argv) >= 2:
    tiny_flag = sys.argv[1];

flag = None
if len(sys.argv) >= 3:
    flag = sys.argv[2];

target = None
if len(sys.argv) >= 4:
    target = sys.argv[3].replace('/', '\\');

samples_folder = 'samples'

traverse_folder(samples_folder, flag, target)
