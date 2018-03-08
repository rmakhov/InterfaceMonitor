CC = g++

OUT_DIR = out
SRC_DIR = src
LIB_DIR = lib
TEST_DIR = test

TARGET_NAME = InterfaceMonitor
TARGET = $(OUT_DIR)/$(TARGET_NAME)d
TARGET_OBJ = $(SRC_DIR)/$(TARGET_NAME).o $(SRC_DIR)/SignalHandler.o
TARGET_SRC = $(SRC_DIR)/$(TARGET_NAME).cpp $(SRC_DIR)/SignalHandler.cpp

LIB_NAME = InterfaceManager
LIB = $(LIB_DIR)/lib$(LIB_NAME).a
LIB_OBJ = $(SRC_DIR)/$(LIB_NAME).o
LIB_SRC = $(SRC_DIR)/$(LIB_NAME).cpp

TEST_NAME = $(LIB_NAME)Test
TEST = $(TEST_DIR)/$(TEST_NAME)Test
TEST_OBJ = $(SRC_DIR)/$(TEST_NAME).o
TEST_SRC = $(SRC_DIR)/$(TEST_NAME).cpp

LDFLAGS = -L$(LIB_DIR) -l$(LIB_NAME) -lpthread
LDFLAGS_TEST = -L$(LIB_DIR) -l$(LIB_NAME) -lboost_unit_test_framework

.PHONY: clean

all: $(LIB) $(TARGET) cleanobj

$(LIB): $(LIB_OBJ)
	ar -cvq $(LIB) $(LIB_OBJ)

$(TARGET): $(LIB) $(TARGET_OBJ)
	$(CC) $(TARGET_OBJ) $(LDFLAGS) -o $@

test: $(LIB) $(TEST_OBJ)
	$(CC) $(TEST_OBJ) $(LDFLAGS_TEST) -o$(TEST)
	@$(TEST) 2>/dev/null ; \
	if [ $$? -eq 0 ] ; then echo "TEST: PASSED" ; else echo "TEST: FAILED" ; fi

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) -c -o $@ $^

cleanobj:
	rm -f $(SRC_DIR)/*.o

clean: cleanobj
	rm -f $(LIB) $(TARGET) $(TEST)
