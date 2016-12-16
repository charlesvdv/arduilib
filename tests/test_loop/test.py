from helper import *

def run(data):
    helper = TestHelper(data)

    try:
        for t in range(11):
            helper.is_io_correct(t, 0, 1, 0)

        # We found a value that we should not.
        print('An error occured in the "micros()" function.')
        return TestHelper.FAIL_CODE
    except TestHelperException:
        # It should be normal to have an exception.
        pass

    try:
        helper.is_io_correct(10, 1, 1, 0)
    except TestHelperException as e:
        print(e.msg)
        return TestHelper.FAIL_CODE

    try:
        helper.is_io_correct(11, 2, 1, 0)

        # Fail.
        print('The interpret go above the max running time.')
        return TestHelper.FAIL_CODE
    except TestHelperException:
        pass

    return TestHelper.SUCCESS_CODE

