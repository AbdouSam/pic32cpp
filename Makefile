CROSS_COMPILE ?= xc32-

MCU = 32MZ2048EFM144
LD_SCRIPT = custom

INC_DIR = -I./src

OBJ_DIR = build/release/out
BIN_DIR = build/release
SRC_DIR = src
TEST_DIR = unittest
LD_DIR  = scripts
LD_FILE = generic_pic32mz.ld
CFG_FILE = pic32_config.h

CSRCS = app.c \
        gpio.c \
        sysclk.c \
        delay.c \
        timer.c \
	uart.c \
        interrupt.c \
        debug.c \

CPPSRCS = main.cpp 

SRC_C = $(addprefix $(SRC_DIR)/, $(CSRCS))
OBJS  = $(addprefix $(OBJ_DIR)/, $(CSRCS:.c=.o))

SRC_CPP = $(addprefix $(SRC_DIR)/, $(CPPSRCS))
OBJSCPP  = $(addprefix $(OBJ_DIR)/, $(CPPSRCS:.cpp=.o))

CFLAGS = -mprocessor=$(MCU)
CFLAGS += $(INC_DIR) -Wfatal-errors -Winline -Wall -Wextra -no-legacy-libc -finline -fno-exceptions -fno-rtti -fno-asynchronous-unwind-tables

MIN_HEAP_SIZE = 0
MIN_STACK_SIZE = 0x400

LDFLAGS = -mprocessor=$(MCU)
LDFLAGS+= -no-legacy-libc

ifeq ($(LD_SCRIPT), custom)
LDFLAGS+= -Wl,--script="$(LD_DIR)/$(LD_FILE)"
endif

LDFLAGS+= -Wl,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map=$(BIN_DIR)/firmware.map
LDFLAGS+= -Wl,--defsym=_min_heap_size=$(MIN_HEAP_SIZE),--defsym=_min_stack_size=$(MIN_STACK_SIZE)
LIBS = -lc -lm



all: $(BIN_DIR)/firmware.hex

$(BIN_DIR)/firmware.hex: $(BIN_DIR)/firmware.elf
	@echo "Create $@"
	@$(CROSS_COMPILE)bin2hex $<

$(BIN_DIR)/firmware.elf: $(OBJS) $(OBJSCPP)
	@echo "LINK $@"
	@$(CROSS_COMPILE)g++ $(LDFLAGS) -o $@ $^ $(LIBS)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.c  $(SRC_DIR)/$(CFG_FILE) $(shell mkdir -p $(OBJ_DIR))
	@echo "Compile $< to get $@"
	@$(CROSS_COMPILE)g++ -c $(CFLAGS) $< -o $@  $(LIBS)

$(OBJSCPP): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp  $(SRC_DIR)/$(CFG_FILE) $(shell mkdir -p $(OBJ_DIR))
	@echo "Compile $< to get $@"
	@$(CROSS_COMPILE)g++ -c $(CFLAGS) $< -o $@  $(LIBS)

.PHONY: clean all program test

clean:
	@rm -f $(OBJS)
	@rm -f $(OBJSCPP)
	@rm -f $(BIN_DIR)/firmware.hex $(BIN_DIR)/firmware.elf $(BIN_DIR)/firmware.map
	@echo "Cleanup complete."

test:
	make -C $(TEST_DIR)

test_clean:
	make -C $(TEST_DIR) clean

# watchout, this routine uncrustify all files in src directory
uncrustify:
	@uncrustify -c uncrustify.cfg --no-backup src/* --suffix

printfiles:
	@echo "src files: $(SRC_C)"
	@echo "obj files:  $(OBJS)"

program: all
	@sleep 1
	@python tools/programmer.py -i udp -a 192.168.1.60 -e
	@sleep 1
	@python tools/programmer.py -i udp -a 192.168.1.60 -u build/release/firmware.hex
	@sleep 1
	@python tools/programmer.py -i udp -a 192.168.1.60 -r
