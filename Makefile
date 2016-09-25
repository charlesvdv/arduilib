export ROOT_DIR := $(realpath .)
export BIN_DIR := $(ROOT_DIR)/bin

SUBDIRS := $(ROOT_DIR)/arduilib $(ROOT_DIR)/register

export CC := gcc
export FLAGS := -std=c99 $(foreach dir,$(SUBDIRS), -I $(dir)) \
		 -Wextra -Wall -fsanitize=address -fsanitize=undefined \
		 -fno-omit-frame-pointer -g -ljansson

all: build

build:
	mkdir -p $(BIN_DIR)
	set -e;  \
	$(foreach dir,$(SUBDIRS), cd $(dir) && make all;)
	$(CC) $(FLAGS) -c arduinint.c arduino.c
	mv *.o $(BIN_DIR)/
	$(CC) $(FLAGS) $(BIN_DIR)/*.o -o arduino

test:
	$(foreach dir,$(SUBDIRS), cd $(dir) && make test;)

clean:
	rm -r $(BIN_DIR)

