CXX = clang
CXXFLAGS = -Wall -c -std=c99 -arch i386 -arch x86_64
LDFLAGS = -arch i386 -arch x86_64 -mmacosx-version-min=10.6
SOURCE_DIR = ./src/
OBJECTS_DIR = ./temp/
BUILD_DIR = ./
FILES = $(OBJECTS_DIR)nanoasm.o \
	$(OBJECTS_DIR)nanovm.o \
	$(OBJECTS_DIR)nanodebug.o
EXE = nanovm

all: $(EXE)

debug: CXXFLAGS += -g
debug: LDFLAGS += -g
debug: $(EXE)
	$(BUILD_DIR)$(EXE)

$(EXE): prep $(FILES)
	$(CXX) $(LDFLAGS) $(FILES) -o $(BUILD_DIR)$@

$(OBJECTS_DIR)%.o: $(SOURCE_DIR)%.c
	$(CXX) $(CXXFLAGS) $< -o $@

prep:
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -rf ./temp
	rm -rf $(EXE)