REGISTER_FILES := reg_pin.c reg_time.c
REGISTER_TEST_FILES := test_reg.c $(foreach file,$(REGISTER_FILES), test_$(file))

OUT_TEST := /tmp/test_reg

all: $(REGISTER_FILES)
	$(CC) $(FLAGS) -c $(REGISTER_FILES)	
	mv *.o $(BIN_DIR)/

test:
	$(CC) $(FLAGS) -lcheck -o $(OUT_TEST) $(REGISTER_FILES) $(REGISTER_TEST_FILES)
	$(OUT_TEST)
