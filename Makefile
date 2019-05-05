# GENERAL VARIABLES
NAME            := $(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")

# COMMAND VARIABLES
RM              := rm -r
MKDIR           := mkdir -p
DOXYGEN         := doxygen
QMAKE           := qmake-qt5

# UNIT TESTING VARIABLES
UNIT_TEST       := $(if $(filter test, $(MAKECMDGOALS)), 1, 0)
UNIT_TEST_NAME  := test
UNIT_TEST_SRC   := $(UNIT_TEST_NAME).cpp
UNIT_TEST_DEF   := UNIT_TEST

# CROSS COMPILATION SETUP
CROSS           :=

ifndef HOSTPLATFORM
	HOSTPLATFORM := UNKNOWN
	ifeq ($(findstring Windows,$(OS)),Windows)
		HOSTPLATFORM := WINDOWS
	else
		uname := $(strip $(shell uname -s))
		ifeq ($(findstring Linux,$(uname)),Linux)
			HOSTPLATFORM := LINUX
		else ifeq ($(findstring MINGW,$(uname)),MINGW)
			HOSTPLATFORM := WINDOWS
		else ifeq ($(findstring MSYS,$(uname)),MSYS)
			HOSTPLATFORM := WINDOWS
		endif
	endif
endif

ifndef PLATFORM
	PLATFORM := $(HOSTPLATFORM)
endif

# CROSS COMPILATION ADAPTION
ifeq ($(PLATFORM),WINDOWS)
	ifneq ($(HOSTPLATFORM),WINDOWS)
		CROSS   := i686-w64-mingw32- # MinGW
	endif
endif

# DIRECTORIES
BIN_DIR         := bin
BUILD_DIR       := build
OBJ_DIR         := obj

SRC_DIR         := src
INC_DIR         := inc

FILES           := $(filter-out $(BIN_DIR) $(BUILD_DIR), $(wildcard *))


# FLAGS
FLAGS           := -fPIC
WARNFLAGS       := -Wall -Wextra -Wpedantic -Winit-self -Wuninitialized -Wpointer-arith -Wcast-align -Wunreachable-code
INCLUDEFLAGS    := -I${INC_DIR} -I${BUILD_DIR} -I/usr/include/qt5 -I/usr/include/qt5/QtWidgets -I/usr/include/qt5/QtGui -I/usr/include/qt5/QtCore
DEFINES         :=
ifneq ($(UNIT_TEST), 0)
	DEFINES     += -D${UNIT_TEST_DEF}
endif

ifneq ($(target), debug)
	BINFLAGS    := -O3
else
	BINFLAGS    := -ggdb3 -Og
endif

ifneq ($(STATIC), 0)
    STATICFLAGS := -static
endif


# OBJECT FILES
CXX_SRC_FILES   := $(wildcard   $(SRC_DIR)/*.cpp) \
				   $(wildcard   $(SRC_DIR)/*/*.cpp)
CXX_SRC_FILES   := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CXX_SRC_FILES))

CC_SRC_FILES    := $(wildcard   $(SRC_DIR)/*.c) \
				   $(wildcard   $(SRC_DIR)/*/*.c)
CC_SRC_FILES    := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CC_SRC_FILES))

TEST_FILES      := $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/test_%, $(CXX_SRC_FILES)) \
				   $(patsubst $(SRC_DIR)/%.c,  $(BIN_DIR)/test_%, $(CC_SRC_FILES))


# TARGETS

default: compile

all: compile docs test

$(BIN_DIR):
	${MKDIR} $@

$(BUILD_DIR):
	${MKDIR} $@

$(BUILD_DIR)/$(OBJ_DIR):
	${MKDIR} $@

.ONESHELL:
$(BUILD_DIR)/Makefile:
	cd ${BUILD_DIR}
	${CROSS}${QMAKE} ..

compile: | $(BUILD_DIR) $(BUILD_DIR)/Makefile $(BIN_DIR)
	${MAKE} -C $(BUILD_DIR)

clean:
	-${RM} ${NAME}.tar ${BUILD_DIR} ${BIN_DIR}

docs: Doxyfile
	-$(DOXYGEN)

# UNIT TESTING
test: $(TEST_FILES) | $(BUILD_DIR)

$(BIN_DIR)/test_%: $(SRC_DIR)/%.cpp | $(BIN_DIR) $(BUILD_DIR)/$(OBJ_DIR)/$(UNIT_TEST_NAME).o
	${CROSS}${CXX} -std=c++11 ${INCLUDEFLAGS} ${FLAGS} ${WARNFLAGS} -o$@ $< $(BUILD_DIR)/$(OBJ_DIR)/$(UNIT_TEST_NAME).o

$(BIN_DIR)/test_%: $(SRC_DIR)/%.c | $(BIN_DIR) | $(BUILD_DIR)/$(OBJ_DIR)/$(UNIT_TEST_NAME).o
	${CROSS}${CC} -std=c++11 ${INCLUDEFLAGS} ${FLAGS} ${WARNFLAGS} -o$@ $< $(BUILD_DIR)/$(OBJ_DIR)/$(UNIT_TEST_NAME).o


$(BUILD_DIR)/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)/$(OBJ_DIR)
	${CROSS}${CXX} -c -std=c++11 ${INCLUDEFLAGS} ${FLAGS} ${WARNFLAGS} -o$@ $<

$(BUILD_DIR)/$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)/$(OBJ_DIR)
	${CROSS}${CC} -c -std=c++11 ${INCLUDEFLAGS} ${FLAGS} ${WARNFLAGS} -o$@ $<


loc:
	-find ${SRC_DIR} ${INC_DIR} -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l


# TAR
tar:
	tar -cf ${NAME}.tar ${FILES};


.PHONY: default compile clean docs test loc tar