# COMMAND VARIABLES
RM              := rm -r
MKDIR           := mkdir -p
DOXYGEN         := doxygen
QMAKE           := qmake-qt5

# CROSS COMPLIATION
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

# TARGETS

default: compile

all: compile docs

$(BIN_DIR):
	${MKDIR} $@

$(BUILD_DIR):
	${MKDIR} $@

.ONESHELL:
$(BUILD_DIR)/Makefile:
	cd ${BUILD_DIR}
	${CROSS}${QMAKE} ..

compile: | $(BUILD_DIR) $(BUILD_DIR)/Makefile $(BIN_DIR)
	${MAKE} -C $(BUILD_DIR)

clean:
	-${RM} ${BUILD_DIR} ${BIN_DIR}

docs: Doxyfile
	-$(DOXYGEN)

.PHONY: default compile clean docs