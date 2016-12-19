from tests.helper import TestHelper, TestHelperException

def run(data):
    helper = TestHelper(data)

    try:
        helper.is_io_correct(0, 0, 1, 0)
    except TestHelperException as e:
        print(e.msg)
        return TestHelper.FAIL_CODE

    return TestHelper.SUCCESS_CODE
