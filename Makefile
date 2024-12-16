# misc
DATE=$(shell date +"%Y%m%d%H%M")
NAME=bitmap
ARGS=

# compilers
CC=gcc
CXX=g++
CPP=

# flags
DEBUG=DEBUG
CFLAGS +=-g -pg -D${DEBUG} \
		 -Wall -Werror -Wextra -Wno-unused \
		 -Wfloat-equal \
		 -Wpointer-arith \
		 -Werror=analyzer-null-argument \
		 -fsanitize=address,undefined

CXXFLAGS +=-g -pg -D${DEBUG} -std=c++11 \
		 -Wall -Werror -Wextra -Wno-unused \
		 -Wfloat-equal \
		 -Wpointer-arith \
		 -Werror=analyzer-null-argument \
		 -fsanitize=address,undefined

LDFLAGS= -pg -fsanitize=undefined,address

VALGRINDFLAGS= --leak-check=full \
			   --show-leak-kinds=all \
			   --track-origins=yes \
			   --verbose \
			   --log-file=valgrind.log

# tools
RM=rm -rf
MKDIR=mkdir -p
CP=cp -r
ZIP=zip -r
VALGRIND=valgrind

AR=ar

SRC_DIR=src
OBJ_DIR=build

DIRS=$(OBJ_DIR) $(OBJ_DIR)/lib $(OBJ_DIR)/test $(OBJ_DIR)/bin

C_SRC=$(shell find $(SRC_DIR) -name "*.c")
C_OBJ=$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.c.o, $(C_SRC))

CXX_SRC=$(shell find $(SRC_DIR) -name "*.cpp")
CXX_OBJ=$(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.cpp.o, $(CXX_SRC))

SRC=$(C_SRC) $(CXX_SRC)
OBJ=$(C_OBJ) $(CXX_OBJ)

LIB_OBJ=$(filter build/lib% , $(OBJ))

TESTS=$(filter build/test% , $(OBJ))
BIN=$(patsubst $(OBJ_DIR)/test/%.c.o,   $(OBJ_DIR)/bin/%, \
	$(patsubst $(OBJ_DIR)/test/%.cpp.o, $(OBJ_DIR)/bin/%, $(TESTS)))


.PHONY: all test clean memtest new
all: $(DIRS) $(OBJ) $(OBJ_DIR)/lib/lib${NAME}.a $(BIN)

# make object code of all .c files
$(OBJ_DIR)/%.c.o: $(SRC_DIR)/%.c $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# link test binaries with library and add them to the build/bin folder
$(OBJ_DIR)/bin/%: build/test/%.c.o $(OBJ_DIR)/lib/lib${NAME}.a
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/bin/%: build/test/%.cpp.o $(OBJ_DIR)/lib/lib${NAME}.a
	$(CXX) $(LDFLAGS) -o $@ $^

# create static library
$(OBJ_DIR)/lib/lib${NAME}.a: $(LIB_OBJ)
	$(AR) rcs $@ $(filter $(OBJ_DIR)/lib% , $(OBJ))

# create folders
$(DIRS):
	$(MKDIR) $@

test:
	./build/bin/$(T)

clean:
	-$(RM) $(OBJ_DIR) valgrind.log valgrind.log.core.* gmon.out
	find -name '*.gch' | xargs $(RM)


memtest: $(BIN)
	$(VALGRIND) $(VALGRINDFLAGS) ./build/bin/$(T) $(ARGS)

format:
	clang-format -i --style=file $(SRC) $(HDR)

prof: test
	gprof -p -b $(BIN) $(ARGS)

todo:
	tree -faiQ src | xargs -n 20 grep --colour -sHinE 'TODO|FIXME'

