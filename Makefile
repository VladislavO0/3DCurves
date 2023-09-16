#creating fictitious targets, if there are files with similar names in the directory
SHELL=cmd
.PHONY: all clean

# variables Initialization 
TARGET = Geometric3D
CC = g++

PREF_OBJ = ./obj/
PREF_SRC = ./src/
PREF_INCLUDE = ./include/

#vpath %.cpp  src
#vpath %.h  src

# Getting all the names of the source files in the src directory
SRC = $(wildcard $(PREF_SRC)*.cpp)
 
# A variable for storing all object files based on the source .cpp names
# $(patsubst search_template, replacement_template , words_list)
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

#<target> : <dependency>
#	<command>

# Template rules for linking object files
$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

# Template rules for compiling object files

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp 
	$(CC) -c $< -o $@

# Deleting object files together with a directory	
clean:
	rm -rf $(TARGET).exe $(PREF_OBJ)*.o
	
# Creating a directory for storing object files
mkdir:
	mkdir obj
 
