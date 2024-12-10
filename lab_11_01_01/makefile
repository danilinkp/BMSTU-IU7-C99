.PHONY: all
all: unit

CC := gcc

SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

OBJS := $(OUTPATH)my_string.o
SRCS := $(wildcard *.c)

UNIT_OBJS = $(OUTPATH)check_main.o $(OUTPATH)check_my_snprintf.o

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
BUILDFLAGS := -lm
TESTBUILDFLAGS := -lcheck -lpthread

unit_tests.exe : $(OBJS) $(UNIT_OBJS)
	$(CC) -o $@ $^ -lm -g3 -O0 $(CFLASG) $(TESTBUILDFLAGS)

$(OUTPATH)%.o : */%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUTPATH)%.d : */%.c
	$(CC) -MM $< > $@

include $(.c=.d)

unit.lastbuildstate :
	rm -rf *.lastbuildstate
	touch unit.lastbuildstate

.PHONY: unit
unit: CFLAGS += $(DEBUGFLAGS)
unit: unit_tests.exe | unit.lastbuildstate
	./unit_tests.exe
	make clean

.PHONY: clean
clean:
	rm -f *.exe *.lastbuildstate *.o out/*.o vgcore.*