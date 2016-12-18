from tests.helper import TestHelper, TestHelperException

def run(data):
    helper = TestHelper(data)

    if not helper.is_empty():
        print('Data is not empty.')
        return TestHelper.FAIL_CODE

    return TestHelper.SUCCESS_CODE
