# Compiler options
CC = g++
OPTCFLAGS= -Ofast -march=native 
CFLAGS= -Wall -Werror -std=c++11 -I $(LIBPATH) $(OPTCFLAGS)
LDFLAGS= -pthread -static-libstdc++
LIBPATH = ../utils/src

# Directory organisation
BASEDIR = .
SRC = $(BASEDIR)/src
BUILD = $(BASEDIR)/build
BIN = $(BASEDIR)/bin

# Program name
TARGET = bowtie_to_reads

# Objects names
OBJECTS = $(BUILD)/bowtie_to_reads.o $(BUILD)/utils.o $(BUILD)/bowtie_parser.o

# Rules

all: init $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN)/$(TARGET) $^ 
	cp $(BIN)/$(TARGET) ../../binaries/$(TARGET)

$(BUILD)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

$(BUILD)/utils.o: $(LIBPATH)/utils.cpp
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	rm -rf $(BUILD)/*.o
	rm -rf $(BIN)/$(TARGET)

init: 
	mkdir -p $(BUILD) $(BIN)

rebuild: clean $(TARGET)
