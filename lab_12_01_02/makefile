.PHONY: all
all: run unit

CC := gcc

LIBPATH := ./lib/
SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))
$(shell mkdir -p $(LIBPATH))

OBJS := $(OUTPATH)array.o
SRCS := $(wildcard *.c)

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
BUILDFLAGS := -lm
TESTBUILDFLAGS := -lcheck -lpthread

STATIC_LIB := $(LIBPATH)libarr.a
SHARED_LIB := $(LIBPATH)libarr.so

.PHONY: run
run: $(SHARED_LIB)
	python $(SRCPATH)main.py


unit_tests.exe : $(OBJS) $(OUTPATH)check_main.o $(OUTPATH)check_left_shift.o $(OUTPATH)check_filter_squares.o
	$(CC) -o $@ $^ $(CFLASG) $(TESTBUILDFLAGS) $(BUILDFLAGS)

$(OUTPATH)%.o : */%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUTPATH)%.d : */%.c
	$(CC) -MM $< > $@

include $(SRCS:.c=.d)

$(STATIC_LIB): $(OBJS)
	ar cr $@ $<
	ranlib $@

$(SHARED_LIB): CFLAGS += -fPIC
$(SHARED_LIB): $(OBJS)
	$(CC) -o $@ -shared $^ -lgcov


unit.lastbuildstate :
	rm -rf *.lastbuildstate
	touch unit.lastbuildstate

.PHONY: unit
unit: CFLAGS += $(DEBUGFLAGS)
unit: unit_tests.exe | unit.lastbuildstate
	./unit_tests.exe
	make clean

.PHONY: coverage
coverage:
	cd $(OUTPATH) && gcov ./*.gcno

.PHONY: clean
clean:
	rm -f *.exe *.d out.txt *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno out/*.gcov vgcore.* lib/*.a lib/*.so