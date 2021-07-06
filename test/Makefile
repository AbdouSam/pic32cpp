CROSS_COMPILE ?=

PROJ_DIR = ../
INC_DIR = -I$(PROJ_DIR)/src
OBJ_DIR = $(PROJ_DIR)/build/test/out
BIN_DIR = $(PROJ_DIR)/build/test
SRC_DIR = $(PROJ_DIR)/src
CFG_FILE = $(PROJ_DIR)/pic32_config.h
TEST_DIR = $(PROJ_DIR)/test

CSRCS = app.c \
        gpio.c \
        sysclk.c \
        delay.c \
        timer.c \
	uart.c \
        interrupt.c \
        debug.c \

CPPSRCS = main.cpp 

TESTCPPSRCS = test_main.cpp\
	      test_gpio.cpp

SRC_C = $(addprefix $(SRC_DIR)/, $(CSRCS))
OBJS  = $(addprefix $(OBJ_DIR)/, $(CSRCS:.c=.o))

SRC_CPP = $(addprefix $(SRC_DIR)/, $(CPPSRCS))
OBJSCPP  = $(addprefix $(OBJ_DIR)/, $(CPPSRCS:.cpp=.o))

TEST_SRC_CPP = $(addprefix $(TEST_DIR)/, $(TESTCPPSRCS))
TEST_OBJSCPP  = $(addprefix $(OBJ_DIR)/, $(TESTCPPSRCS:.cpp=.o))

CFLAGS = $(INC_DIR)
#add to detect memory leaks
CFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorMallocMacros.h

CPPFLAGS = -I$(SRC_FOLDER)
CPPFLAGS += -I$(CPPUTEST_HOME)/include 
CPPFLAGS += -include $(CPPUTEST_HOME)/include/CppUTest/MemoryLeakDetectorNewMacros.h

LDFLAGS = -L$(CPPUTEST_HOME)/lib -lCppUTest -lCppUTestExt
LIBS = -lc -lm

all: $(BIN_DIR)/maintest
	@echo "Run Test"
	./$(BIN_DIR)/maintest

$(BIN_DIR)/maintest: $(OBJS) $(OBJSCPP)
	@echo "LINK $@"
	@$(CROSS_COMPILE)g++ $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  $(SRC_DIR)/$(CFG_FILE) $(shell mkdir -p $(OBJ_DIR))
	@echo "Compile $< to get $@"
	@$(CROSS_COMPILE)g++ -c $(CPPFLAGS) $< -o $@  $(LIBS)

$(OBJSCPP): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp  $(SRC_DIR)/$(CFG_FILE) $(shell mkdir -p $(OBJ_DIR))
	@echo "Compile $< to get $@"
	@$(CROSS_COMPILE)g++ -c $(CPPFLAGS) $< -o $@  $(LIBS)

$(TEST_OBJSCPP): $(OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp  $(SRC_DIR)/$(CFG_FILE) $(shell mkdir -p $(OBJ_DIR))
	@echo "Compile $< to get $@"
	@$(CROSS_COMPILE)g++ -c $(CPPFLAGS) $< -o $@  $(LIBS)

.PHONY: clean all program

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJSCPP)
	@rm -f $(BIN_DIR)/*
	@echo "Cleanup complete."
