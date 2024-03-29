CC=g++
STD=c++11

TARGET_NAME=bilheteria
BUILD_PATH=./build
SOURCE_PATH=./src
LIB_PATH=./lib
DATA_PATH=./data

SOURCE_EXT := cpp
SOURCES := $(shell find $(SOURCE_PATH) -path '*.$(SOURCE_EXT)' ! -name "main.cpp")

OBJECTS := $(patsubst $(SOURCE_PATH)/%,$(BUILD_PATH)/%,$(SOURCES:.$(SOURCE_EXT)=.o))

all: $(TARGET_NAME)

$(BUILD_PATH)/%.o: $(SOURCE_PATH)/%.cpp $(LIB_PATH)/%.hpp
	mkdir -p $(@D)
	$(CC) -std=$(STD) -c -o $@ $<

$(TARGET_NAME): $(OBJECTS)
	mkdir -p $(BUILD_PATH)
	$(CC) -std=$(STD) -o $(BUILD_PATH)/$(TARGET_NAME) $(SOURCE_PATH)/main.cpp $(OBJECTS)

clean:
	rm -rf $(BUILD_PATH)/*

run:
	$(BUILD_PATH)/$(TARGET_NAME) $(DATA_PATH)/users.csv $(DATA_PATH)/events.csv

mem:
	valgrind --leak-check=yes $(BUILD_PATH)/$(TARGET_NAME) $(DATA_PATH)/users.csv $(DATA_PATH)/events.csv
