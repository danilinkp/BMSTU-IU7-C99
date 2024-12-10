.PHONY: all
all: release unit func

CC := gcc

OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

OBJS := $(OUTPATH)associative_array_impl_2.o
SRCS := $(wildcard *.c)

UNIT_OBJS = $(OUTPATH)check_main.o $(OUTPATH)check_clear.o $(OUTPATH)check_each.o $(OUTPATH)check_find.o $(OUTPATH)check_insert.o $(OUTPATH)check_max.o $(OUTPATH)check_min.o $(OUTPATH)check_remove.o

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion
DEBUGFLAGS := -O0 -g3
BUILDFLAGS := -lm
TESTBUILDFLAGS := -lcheck -lpthread

unit_tests.exe : $(UNIT_OBJS) $(OBJS)
	$(CC) -o $@ $^ -lm -g3 -O0 $(CFLASG) $(TESTBUILDFLAGS)

$(OUTPATH)%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUTPATH)%.d : %.c
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