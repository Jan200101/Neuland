# GENERAL VARIABLES
NAME            := $(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")

# COMMAND VARIABLES
RM              := rm -r
MKDIR           := mkdir -p
DOXYGEN         := doxygen
QMAKE           := qmake-qt5

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

FILES           := $(filter-out $(BIN_DIR) $(BUILD_DIR), $(wildcard *))


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

compile: $(BUILD_DIR)/Makefile | $(BUILD_DIR) $(BIN_DIR)
	${MAKE} -C $(BUILD_DIR)

clean:
	-${RM} ${NAME}.tar ${BUILD_DIR} ${BIN_DIR}

docs: Doxyfile
	-$(DOXYGEN)


loc:
	-find ${SRC_DIR} ${INC_DIR} -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l


# TAR
tar:
	tar -cf ${NAME}.tar ${FILES};


.PHONY: default compile clean docs test loc tar