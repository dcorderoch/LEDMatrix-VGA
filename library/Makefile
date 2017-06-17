EXE := wrapper
# name of source and object directories
# change *.c for *.cpp if you want to use C++
EXT := *.c
SDIR := .
ODIR := obj
# rules for making the object and the executable files
SOURCES := $(notdir $(wildcard $(SDIR)/$(EXT)))
SOURCE := $(patsubst %,$(SDIR)/%,$(SOURCES))
_OBJ := $(SOURCES:.c=.o)
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))
# compiler and compiler flags
# change gcc for g++ if you want to use c++
CC := gcc
# you can take this Makefile as a template
# just change -W and -Wall for -O{N}
# where N is the number for optimization you want
CCFLAGS := -W -Wall `pkg-config --cflags glib-2.0` -O2
LDLIBS := -lglib-2.0

all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CCFLAGS) $(LDLIBS)
$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CCFLAGS)
.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE)
.PHONY : run
run : all
	./$(EXE)
