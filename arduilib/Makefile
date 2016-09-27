ARDUILIB_FILES := arduilib_io.c arduilib_time.c arduilib_logger.c arduilib_error.c
ARDUILIB_TEST_FILES := test_arduilib.c $(foreach file,$(LIB_FILES), test_$(file))

IO_TEST_FILES := test/wrap_arduilib_error.c test/wrap_arduilib_time.c \
				 test/test_arduilib_io.c arduilib_io.c test/wrap_reg_pin.c
IO_WRAP_FLAGS := -Wl,--wrap=arduilib_handle_error -Wl,--wrap=reg_set_pin_mode \
				 -Wl,--wrap=arduilib_get_time_millis -Wl,--wrap=reg_set_pin_value \
				 -Wl,--wrap=reg_get_pin_mode -Wl,--wrap=reg_get_pin_value
IO_TEST_OUT := /tmp/test_arduilib_io

all: $(ARDUILIB_FILES)
	$(CC) -c $(ARDUILIB_FILES) $(FLAGS)
	mv *.o $(BIN_DIR)/

check: test_io

test_io:
	@echo " === IO Arduino Library Tests === "
	$(CC) $(IO_WRAP_FLAGS) $(IO_TEST_FILES) -o $(IO_TEST_OUT) $(TEST_FLAGS)
	$(IO_TEST_OUT)
