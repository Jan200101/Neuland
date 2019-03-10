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

first: dependencies buildui

dependencies: qmake

directories:
	@echo $(MKDIR) $(BUILD_DIR)
	-@$(MKDIR) $(MKDIR_FLAGS) $(BUILD_DIR)

.ONESHELL:
qmake: directories
	@echo Building Makefile
	$(PREFIX)$(CD) $(BUILD_DIR)
	$(PREFIX)$(QMAKE) ..


buildui: qmake
	@echo Building UI
	$(PREFIX)$(MAKE) -C $(BUILD_DIR)

install: first
	$(PREFIX)$(MAKE) -C $(BUILD_DIR) install

uninstall: first
	$(PREFIX)$(MAKE) -C $(BUILD_DIR) uninstall

clean: qmake
	$(PREFIX)$(MAKE) -C $(BUILD_DIR) clean

cleandir: remove
remove: rmdirectories

rmdirectories:
	@echo $(RM) $(BUILD_DIR)
	-@$(RM) $(RM_FLAGS) $(BUILD_DIR) 2> /dev/null

loc:
	-find src include -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp' -type f | xargs wc -l

doxy:
	@-doxygen

