#!/usr/bin/python3
import importlib
import os
import subprocess
#  from simple_config import test
from helper import TestHelper

INTERPRET_CMD = 'python3 ../arduinint interpret -c {0}/config.json {0}/test.ino'

def run_tests():
    success = 0
    for folder in os.listdir():
        if not os.path.isdir(folder): continue
        if not folder.startswith('test_') : continue

        status = subprocess.run(INTERPRET_CMD.format(folder), shell=True,
                    stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        if status.returncode != 0:
            print('Error while interpreting')
            if status.stdout:
                print('stdout:\n{}'.format(status.stdout))
            if status.stderr:
                print('stderr:\n{}'.format(status.stderr))
            exit(1)
        data = status.stdout.decode('utf-8')

        test_runner = importlib.import_module('{}.test'.format(folder))
        if test_runner.run(data) == TestHelper.FAIL_CODE:
            success += 1
            print('{} failed'.format(folder))
        else:
            print('{} OK!'.format(folder))

    return success

if __name__ == '__main__':
    # Change the working directory.
    testdir = os.path.dirname(os.path.realpath(__file__))
    os.chdir(testdir)

    print('Run integration tests')
    print('------------------------------')
    status = run_tests()
    exit(status)
