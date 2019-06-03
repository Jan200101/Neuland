# GENERAL VARIABLES
NAME            := $(shell pwd | sed -E "s/.*\/([a-zA-Z0-9_-]*)/\1/")
STD             := c++17

# COMMAND VARIABLES
LS              := ls -l
RM              := rm -r
RMDIR           := rmdir
MKDIR           := mkdir -p
DOXYGEN         := doxygen
QMAKE           := qmake-qt5
PKG-CONFIG      := pkg-config
WINDRES         := windres

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
	OUT_EXT     := .exe
	ifneq ($(HOSTPLATFORM),WINDOWS)
		# MXE prefix
		CROSS   := i686-w64-mingw32.static-
	endif
endif


# GCC VERSION CHECK
GCC_VER         := $(strip $(shell ${CROSS}$(CXX) -dumpversion 2>&1))
override GCC_VER_SPLIT := $(subst ., ,$(GCC_VER))
GCC_MAJOR := $(word 1,$(GCC_VER_SPLIT))
GCC_MINOR := $(word 2,$(GCC_VER_SPLIT))


# DIRECTORIES
BIN_DIR         := bin
BUILD_DIR       := build
OBJ_DIR         := $(BUILD_DIR)/obj


OBJ_DIRS        := $(OBJ_DIR) \
                   $(OBJ_DIR)/frontend \
                   $(OBJ_DIR)/backend \

SRC_DIR         := src
INC_DIR         := inc
RES_DIR         := res

FILES           := $(filter-out $(BUILD_DIR), $(wildcard *))


# FLAGS
FLAGS           := `$(CROSS)$(PKG-CONFIG) --cflags ncurses` \
				   `$(CROSS)$(PKG-CONFIG) --cflags jsoncpp`
CFLAGS          := $(FLAGS)
CXXFLAGS        := $(FLAGS)

WARNFLAGS       := -Wall -Wextra -pedantic -Winit-self -Wcast-align -Wuninitialized -Wpointer-arith -Wunreachable-code

INCLUDEFLAGS    := -I${INC_DIR}

LIBS            := `$(CROSS)$(PKG-CONFIG) --libs ncurses` \
                   `$(CROSS)$(PKG-CONFIG) --libs jsoncpp`
ifneq (9,$(GCC_MAJOR))
    LIBS        += -lstdc++fs
endif

BINFLAGS        := $(LIBS)

DEFINES         := -DNO_QT

# OBJECT FILES
CXX_SRC_FILES   := $(wildcard   $(SRC_DIR)/*.cpp) \
				   $(wildcard   $(SRC_DIR)/*/*.cpp)
CXX_SRC_FILES   := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CXX_SRC_FILES))

CC_SRC_FILES    := $(wildcard   $(SRC_DIR)/*.c) \
				   $(wildcard   $(SRC_DIR)/*/*.c)
CC_SRC_FILES    := $(filter-out $(SRC_DIR)/$(UNIT_TEST_SRC), $(CC_SRC_FILES))


OBJ_FILES       := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o, $(CXX_SRC_FILES)) \
				   $(patsubst $(SRC_DIR)/%.c,  $(OBJ_DIR)/%.o, $(CC_SRC_FILES))

ifeq ($(PLATFORM),WINDOWS)
	RC_FILES     := $(patsubst $(RES_DIR)/%.rc,  $(OBJ_DIR)/%.o, $(wildcard $(RES_DIR)/*.rc))
	OBJ_FILES    += $(RC_FILES)
endif

# TARGETS

default: cli

# graphical and cli targets clash
all: default docs

$(BIN_DIR):
	${MKDIR} $@

$(BUILD_DIR):
	${MKDIR} $@

$(OBJ_DIR):
	${MKDIR} ${OBJ_DIRS}

.ONESHELL:
$(BUILD_DIR)/Makefile: $(BUILD_DIR) $(BIN_DIR) $(RC_FILES)
	cd ${BUILD_DIR}
	${CROSS}${QMAKE} ..

graphical: $(BUILD_DIR)/Makefile
	${MAKE} -C $(BUILD_DIR)
	-@${LS} $(BIN_DIR)/${NAME}$(OUT_EXT)

cli: $(BIN_DIR)/$(NAME)$(OUT_EXT)
	-@${LS} $(BIN_DIR)/${NAME}$(OUT_EXT)


clean:
	-${RM} ${NAME}.tar ${BUILD_DIR} ${BIN_DIR}

docs: Doxyfile
	-${DOXYGEN}


$(BIN_DIR)/$(NAME)$(OUT_EXT): $(OBJ_FILES) | $(BIN_DIR) $(OBJ_DIR)
	${CROSS}${CXX} -o$@ $^ -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${INCLUDEFLAGS} ${DEFINES} $(BINFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	${CROSS}${CXX} -c -o$@ $< -std=${STD} ${CXXFLAGS} ${WARNFLAGS} ${INCLUDEFLAGS} ${DEFINES}

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	${CROSS}${CC} -c -o$@ $< -std=${STD} ${CFLAGS} ${WARNFLAGS} ${INCLUDEFLAGS} ${DEFINES}

$(OBJ_DIR)/%.o: $(RES_DIR)/%.rc | $(OBJ_DIR)
	${CROSS}${WINDRES} -i $< -o $@

loc:
	-find ${SRC_DIR} ${INC_DIR} -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l


install:
	@test -d /opt/${NAME}/bin || mkdir -p /opt/${NAME}/bin
	install -m 755 -p -s bin/${NAME}$${OUT_EXT} /opt/${NAME}/bin
	@echo Installed

uninstall:
	-@$(RM) -rf /opt/Neuland/bin/
	-@$(RMDIR) /opt/Neuland
	@echo Uninstalled

# TAR
tar: $(NAME).tar

$(NAME).tar:
	tar -cf $@ ${FILES};


.PHONY: default graphical cli clean docs loc install uninstall tar
