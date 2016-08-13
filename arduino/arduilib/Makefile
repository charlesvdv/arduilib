ARDUILIB_FILES := arduilib_io.c arduilib_time.c arduilib_logger.c arduilib_error.c
ARDUILIB_TEST_FILES := test_arduilib.c $(foreach file,$(LIB_FILES), test_$(file))

OUT_TEST := /tmp/test_arduilib

all: $(ARDUILIB_FILES)
	$(CC) $(FLAGS) -c $(ARDUILIB_FILES)
	mv *.o $(BIN_DIR)/

test:
	# $(CC) $(FLAGS) -lcheck -o $(OUT_TEST) $(LIB_FILES) $(REGISTER_TEST_FILES)
	# $(OUT_TEST)
