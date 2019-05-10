# GENERAL VARIABLES
NAME            := $(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")
STD             := c++11


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
OBJ_DIR         := $(BUILD_DIR)/obj


OBJ_DIRS        := $(OBJ_DIR) \
                   $(OBJ_DIR)/backend \

SRC_DIR         := src
INC_DIR         := inc

FILES           := $(filter-out $(BUILD_DIR), $(wildcard *))


# FLAGS
CFLAGS          :=
CXXFLAGS        :=
WARNFLAGS       := -Wall -Wextra -pedantic -Winit-self -Wcast-align -Wuninitialized -Wpointer-arith -Wunreachable-code
INCLUDEFLAGS    := -I${INC_DIR}
BINFLAGS        := -ljsoncpp -lncurses
DEFINES         :=

# OBJECT FILES
CXX_SRC_FILES   := $(wildcard   $(SRC_DIR)/*.cpp) \
				   $(wildcard   $(SRC_DIR)/*/*.cpp)
CXX_SRC_FILES   := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CXX_SRC_FILES))

CC_SRC_FILES    := $(wildcard   $(SRC_DIR)/*.c) \
				   $(wildcard   $(SRC_DIR)/*/*.c)
CC_SRC_FILES    := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CC_SRC_FILES))


OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(CXX_SRC_FILES)) \
				   $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(CC_SRC_FILES))


# TARGETS

default: graphical

all: graphical docs

$(BIN_DIR):
	${MKDIR} $@

$(BUILD_DIR):
	${MKDIR} $@

$(OBJ_DIR):
	${MKDIR} ${OBJ_DIRS}

.ONESHELL:
$(BUILD_DIR)/Makefile: $(BUILD_DIR) $(BIN_DIR)
	cd ${BUILD_DIR}
	${CROSS}${QMAKE} ..

graphical: $(BUILD_DIR)/Makefile
	${MAKE} -C $(BUILD_DIR)

cli: $(BIN_DIR)/$(NAME)

clean:
	-${RM} ${NAME}.tar ${BUILD_DIR} ${BIN_DIR}

docs: Doxyfile
	-$(DOXYGEN)


$(BIN_DIR)/$(NAME): $(OBJ_FILES) | $(BIN_DIR) $(OBJ_DIR)
	${CROSS}${CXX} -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} -DNO_QT ${DEFINES} $(BINFLAGS) -o$@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	${CROSS}${CXX} -c  -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} -DNO_QT ${DEFINES} -o$@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	${CROSS}${CC} -c -std=${STD} ${CFLAGS} ${WARNFLAGS} ${STATICFLAGS} ${INCLUDEFLAGS} -DNO_QT ${DEFINES} -o$@ $<


loc:
	-find ${SRC_DIR} ${INC_DIR} -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l


# TAR
tar: $(NAME).tar

$(NAME).tar:
	tar -cf $@ ${FILES};


.PHONY: default graphical cli clean docs loc tar