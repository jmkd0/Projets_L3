#!/usr/bin/env python3

## run all tests in tests/features/ directory
## or with files given as arg (ex ./run_features_tests tests/features/01_decl_assign.py)

import sys
import os
import subprocess
from shutil import copyfile

PITON_PATH = 'src/piton.rkt'
TESTS_PATH = 'tests/features/'
LIB_PATH = 'tests.lib'

def fail(piton_output, python_output):
    print("------------------")
    print("Failed with output:\n" +  piton_output + '\n')
    print("Expected:\n" + python_output + '\n')
    print("------------------")
    sys.exit(1)

def fail_error():
    print("------------------")
    print("Failed with error")
    print("------------------")
    sys.exit(1)

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

    with open(test_path) as f:
        content = f.read()

    # prepare python file including lib
    content = 'from ' +  LIB_PATH + ' import *\n' + content
    with open('.test_tmp.py', 'w') as f:
        f.write(content)
    # run python
    python_cmd = 'python3 .test_tmp.py'
    python_output = subprocess.check_output([python_cmd], shell=True)
    python_output = python_output.decode('utf-8').strip()

    # compile with piton and run spim
    copyfile(test_path, '.test_tmp.py')
    compile_cmd = PITON_PATH +  ' .test_tmp.py'
    try:
        subprocess.check_output([compile_cmd], shell=True)
        run_cmd = 'spim -file .test_tmp.s'
        piton_output = subprocess.check_output([run_cmd], shell=True)
    except subprocess.CalledProcessError as e:
        fail_error()

    # compare outputs
    piton_output = piton_output.decode('utf-8').strip()
    piton_output = '\n'.join(piton_output.split('\n')[5:])
    if piton_output != python_output:
        fail(piton_output, python_output)

def clean_up():
    os.remove('.test_tmp.py')
    os.remove('.test_tmp.s')

def main():
    if len(sys.argv) > 1:
        test_paths = sys.argv[1:]
    else:
        test_paths = scan_tests()

    for test_path in test_paths:
        run_test(test_path)
    print("All tests passed")
    clean_up()

main()
