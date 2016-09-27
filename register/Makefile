REGISTER_FILES := reg_pin.c reg_time.c

TIME_TEST_FILES := reg_time.c test/test_reg_time.c
TIME_TEST_OUT := /tmp/test_reg_time

PIN_TEST_FILES := reg_pin.c test/test_reg_pin.c
PIN_TEST_OUT := /tmp/test_reg_pin

all: $(REGISTER_FILES)
	$(CC) -c $(REGISTER_FILES) $(FLAGS)
	mv *.o $(BIN_DIR)/

check: test_time test_pin

test_time: $(TIME_TEST_FILES)
	@echo " === Time Register Tests === "
	$(CC) $(TIME_TEST_FILES) -o $(TIME_TEST_OUT) $(TEST_FLAGS)
	$(TIME_TEST_OUT)

test_pin: $(PIN_TEST_FILES)
	@echo " === Pin Register Tests === "
	$(CC) $(PIN_TEST_FILES) -o $(PIN_TEST_OUT) $(TEST_FLAGS)
	$(PIN_TEST_OUT)
