CXX = clang
CXXFLAGS = -Wall -c -std=c99 -arch i386 -arch x86_64
LDFLAGS = -arch i386 -arch x86_64 -mmacosx-version-min=10.6
SOURCE_DIR = ./src/
OBJECTS_DIR = ./temp/
BUILD_DIR = ./
VM_FILES = $(OBJECTS_DIR)dumbvm.o \
	$(OBJECTS_DIR)dumbdebug.o

ASM_FILES = $(OBJECTS_DIR)dumbasm.o \
	$(OBJECTS_DIR)dumbdebug.o

VM = dumbvm
ASM = dumbasm

all: $(VM) $(ASM)

install: $(VM) $(ASM)
	cp $(VM) ~/Dropbox/bin/$(VM)
	cp $(ASM) ~/Dropbox/bin/$(ASM)

debug: CXXFLAGS += -g -DDEBUG
debug: LDFLAGS += -g -DDEBUG
debug: $(VM) $(ASM)

$(ASM): prep $(ASM_FILES)
	$(CXX) $(LDFLAGS) $(ASM_FILES) -o $(BUILD_DIR)$@

$(VM): prep $(VM_FILES)
	$(CXX) $(LDFLAGS) $(VM_FILES) -o $(BUILD_DIR)$@

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.c
	$(CXX) $(CXXFLAGS) $< -o $@

prep:
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf ./temp
	rm -rf $(BUILD_DIR)$(VM)
	rm -rf $(BUILD_DIR)$(ASM)