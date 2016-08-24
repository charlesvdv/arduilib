export ROOT_DIR := $(realpath .)
export BIN_DIR := $(ROOT_DIR)/bin

SUBDIRS := $(ROOT_DIR)/arduilib $(ROOT_DIR)/register

export CC := gcc
export FLAGS := -std=c99 -ljansson

export DEV_FLAGS := -Wextra -Wall -fsanitize=address -fsanitize=undefined \
					-fno-omit-frame-pointer -g

export TEST_FLAGS := $(FLAGS) $(DEV_FLAGS) -lcmocka -DUNIT_TEST

all: build

build:
	mkdir -p $(BIN_DIR)
	set -e;  \
	$(foreach dir,$(SUBDIRS), cd $(dir) && make all;)
	$(CC) $(FLAGS) -c arduinint.c arduino.c
	mv *.o $(BIN_DIR)/
	$(CC) $(FLAGS) $(BIN_DIR)/*.o -o arduino

check:
	$(foreach dir,$(SUBDIRS), cd $(dir) && make check;)

clean:
	rm -r $(BIN_DIR)
