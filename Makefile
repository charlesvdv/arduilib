export ROOT_DIR := $(realpath .)
export BIN_DIR := $(ROOT_DIR)/bin

SUBDIRS := $(ROOT_DIR)/arduilib $(ROOT_DIR)/register

ifndef CC
	export CC := gcc
endif

export FLAGS := -std=c99 -ljansson -fuse-ld=gold

export DEV_FLAGS := -Wextra -Wall -fsanitize=address -fsanitize=undefined \
					-fno-omit-frame-pointer -g

export TEST_FLAGS := -lcmocka $(FLAGS) $(DEV_FLAGS) -DUNIT_TEST

all: build

build:
	mkdir -p $(BIN_DIR)
	set -e;  \
	$(foreach dir,$(SUBDIRS), cd $(dir) && make all;)
	$(CC) -c arduinint.c arduino.c $(FLAGS)
	mv *.o $(BIN_DIR)/
	$(CC) $(BIN_DIR)/*.o -o arduino $(FLAGS)

check:
	$(foreach dir,$(SUBDIRS), cd $(dir) && make check;)

clean:
	rm -r $(BIN_DIR)
