# Compiler to use
CC := g++

# Directory containing all source files
SRCDIR := src

# Directory containing all object files
BUILDDIR := build

# Executable file
TARGET := bin/runner

# Source file extention
SRCEXT := cpp

# All source files
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))

# All source directories to create the same directory structure in the build folder
SOURCEDIRS := $(shell cd $(SRCDIR) && find . -type d)

# All object files
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

# Compile flags
CFLAGS := -g -Wall

# Libraries to use
# -lSDL2       -> base
# -lSDL2_image -> image processing
# -lSDL2_ttf   -> ttf font support
# -lSDL2_mixer -> audio support
LIB := -lSDL2 -lSDL2_image -lSDL2_ttf

# Include directories
INC := -I include


all: directories $(TARGET)

# Creating directories
directories: $(SOURCEDIRS)

$(SOURCEDIRS):
	@mkdir -p $(BUILDDIR)/$@
	@echo "Creating dir: $@"

# Linking process
$(TARGET): $(OBJECTS)
	@echo " Linking..."
	@echo " $(CC) $^ -o $(TARGET) $(LIB)"; $(CC) $^ -o $(TARGET) $(LIB)

# Build process
$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@echo " Cleaning...";
	@echo " $(RM) -r $(BUILDDIR) $(TARGET)"; $(RM) -r $(BUILDDIR) $(TARGET)

# Tests
tester:
	$(CC) $(CFLAGS) test/tester.cpp $(INC) $(LIB) -o bin/tester

# Spikes
ticket:
	$(CC) $(CFLAGS) spikes/ticket.cpp $(INC) $(LIB) -o bin/ticket

.PHONY: clean
.PHONY: directories
