PROJECT         := Neuland

QMAKE           ?= qmake-qt5

VERBOSE         ?= 0

BUILD_DIR       ?= build

CD              := cd
MKDIR           := mkdir -p
RM              := rm -r

ifneq ($(VERBOSE), 0)
    PREFIX      := 
else
    PREFIX      := @
endif

default_target: directories buildapp

directories:
	$(PREFIX)$(MKDIR) $(BUILD_DIR)

.ONESHELL:
buildapp:
	$(PREFIX)$(CD) $(BUILD_DIR)
	$(PREFIX)$(QMAKE) ..
	$(PREFIX)$(MAKE)


clean: rmdirectories

rmdirectories:
	-$(PREFIX)$(RM) $(BUILD_DIR) 2> /dev/null

loc:
	-find src include -name '*.cpp' -o -name '*.c' -o -name '*.h' -o -name '*.hpp'| xargs wc -l

doxy:
	@-doxygen
