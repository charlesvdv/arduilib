LIB_FILES := arduino_io.c arduino_time.c arduino_logger.c
LIB_TEST_FILES := test_lib.c $(foreach file,$(LIB_FILES), test_$(file))

OUT_TEST := /tmp/test_lib

all: $(LIB_FILES)
	$(CC) $(FLAGS) -ljansson -c $(LIB_FILES) 
	mv *.o $(BIN_DIR)/

test:
	# $(CC) $(FLAGS) -lcheck -o $(OUT_TEST) $(LIB_FILES) $(REGISTER_TEST_FILES)
	# $(OUT_TEST)
