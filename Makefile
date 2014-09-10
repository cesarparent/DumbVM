CXX = clang
CXXFLAGS = -Wall -c -std=c99 -arch i386 -arch x86_64
LDFLAGS = -arch i386 -arch x86_64 -mmacosx-version-min=10.6
SOURCE_DIR = ./src/
OBJECTS_DIR = ./temp/
BUILD_DIR = ./
FILES = $(OBJECTS_DIR)dumbasm.o \
	$(OBJECTS_DIR)dumbvm.o \
	$(OBJECTS_DIR)dumbdebug.o
EXE = dumbvm

all: $(EXE)

debug: CXXFLAGS += -g -DDEBUG
debug: LDFLAGS += -g -DDEBUG
debug: $(EXE)

assembler: CXXFLAGS += -DASM
assembler: LDFLAGS += -DASM
assembler: prep $(OBJECTS_DIR)dumbasm.o
	$(CXX) $(LDFLAGS) $(OBJECTS_DIR)dumbasm.o -o $(BUILD_DIR)$@

$(EXE): prep $(FILES)
	$(CXX) $(LDFLAGS) $(FILES) -o $(BUILD_DIR)$@

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.c
	$(CXX) $(CXXFLAGS) $< -o $@

prep:
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf ./temp
	rm -rf $(BUILD_DIR)$(EXE)
	rm -rf $(BUILD_DIR)assembler