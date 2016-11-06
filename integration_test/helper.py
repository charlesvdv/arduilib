import json
from io import StringIO

class TestHelper():
    SUCCESS_CODE = 0
    FAIL_CODE = 1

    def __init__(self, data):
        self.json = json.load(StringIO(data))

    def is_errored(self):
        if 'error' in self.json:
            return True
        else:
            return False

    def is_empty(self):
        return not len(self.json)

    def is_io_correct(self, time, pin, value, mode):
        # Get value from the JSON. Raise DataNotFoundException is not found.
        val = self.get_io_data_time(time)
        pin_data = self.get_io_pin(val, pin)

        # Check if value and mode is correct.
        if value != 2 and pin_data['value'] != value:
            raise NotValidException('{} received value is {}'.format(
                    self._format_io_header_exception(time, pin, value, mode),
                    pin_data['value']))
        if mode != 2 and pin_data['mode'] != mode:
            raise NotValidException('{} received mode is {}'.format(
                    self._format_io_header_exception(time, pin, value, mode),
                    pin_data['mode']))

    def _format_io_header_exception(self, time, pin, value, mode):
        return 'Error at time: {}, pin: {}, value: {}, mode: {}'.format(
                time, pin, value, mode)

    def get_io_data(self):
        if 'io' not in self.json:
            raise DataNotFoundException('Unable to find io data')

        return self.json['io']

    def get_io_data_time(self, time):
        for data in self.get_io_data():
            if data['time'] == time:
                return data['value']
        raise DataNotFoundException('Unable to find value at {} time'.format(time))

    def get_io_pin(self, value, pin):
        for val in value:
            if val['pin'] == pin:
                return val
        raise DataNotFoundException('Unable to find the pin {}'.format(pin))

class TestHelperException(Exception):
    def __init__(self, msg):
        super().__init__(msg)
        self.msg = msg

class DataNotFoundException(TestHelperException):
    def __init__(self, msg):
        super().__init__(msg)
        self.msg = msg

class NotValidException(TestHelperException):
    def __init__(self, msg):
        super().__init__(msg)
        self.msg = msg
