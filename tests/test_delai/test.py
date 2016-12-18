from tests.helper import TestHelper, TestHelperException

def run(data):
    helper = TestHelper(data)

    try:
        value = 1
        for t in range(21):
            helper.is_io_correct(t, 0, value, 0)
            if value: value = 0
            else: value = 1
    except TestHelperException as e:
        print(e.msg)
        return TestHelper.FAIL_CODE
    return TestHelper.SUCCESS_CODE
