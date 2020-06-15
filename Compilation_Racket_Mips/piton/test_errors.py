#!/usr/bin/env python3

## run all tests in tests/errors/ directory

import sys
import os
import subprocess
from shutil import copyfile

PITON_PATH = 'src/piton.rkt'
TESTS_PATH = 'tests/errors/'

def scan_tests():
    test_paths = []
    for file in os.scandir(TESTS_PATH):
        if file.is_dir():
            continue
        if not file.name.endswith('.py'):
            continue
        test_paths.append(TESTS_PATH + file.name)
    test_paths.sort()
    return test_paths

def run_test(test_path):
    print("Testing " + test_path + "...")

    copyfile(test_path, '.test_tmp.py')
    compile_cmd = PITON_PATH + ' .test_tmp.py'
    try:
        subprocess.check_output([compile_cmd], shell=True)
        # if compile succeeds, check for runtime error
        run_cmd = 'spim -file .test_tmp.s'
        piton_output = subprocess.check_output([run_cmd], shell=True)
        piton_output = piton_output.decode('utf-8').strip()
        piton_output = '\n'.join(piton_output.split("\n")[5:])
        print(piton_output + '\n')
    except subprocess.CalledProcessError as e:
        print()

def cleanup():
    os.remove('.test_tmp.s')

def main():
    test_paths = scan_tests()
    for test_path in test_paths:
        run_test(test_path)

main()
