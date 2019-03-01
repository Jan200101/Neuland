PROJECT         := Neuland

QMAKE           ?= qmake-qt5

VERBOSE         ?= 0

BUILD_DIR       ?= build

CD              := cd
MKDIR           := mkdir
MKDIR_FLAGS     := -p
RM              := rm
RM_FLAGS        := -r

ifneq ($(VERBOSE), 0)
    PREFIX      := 
else
    PREFIX      := @
endif

default_target: dependencies qmake

dependencies: directories

directories:
	@echo $(MKDIR) $(BUILD_DIR)
	-@$(MKDIR) $(MKDIR_FLAGS) $(BUILD_DIR)

.ONESHELL:
qmake:
	$(PREFIX)$(CD) $(BUILD_DIR)
	$(PREFIX)$(QMAKE) ..
	$(PREFIX)$(MAKE)


clean: rmdirectories

rmdirectories:
	@echo $(RM) $(BUILD_DIR)
	-@$(RM) $(RM_FLAGS) $(BUILD_DIR) 2> /dev/null

loc:
	-find src include -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp'| xargs wc -l

doxy:
	@-doxygen
