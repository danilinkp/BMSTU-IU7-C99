.PHONY: all
all: release unit func

CC := gcc

SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/
FUNCPATH := ./func_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

OBJS := $(OUTPATH)linked_list.o $(OUTPATH)book.o $(OUTPATH)books.o
SRCS := $(wildcard *.c)

CFLAGS := -std=gnu99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
BUILDFLAGS := -lm
TESTBUILDFLAGS := -lcheck -lpthread

app.exe : $(OUTPATH)main.o $(OBJS)
	echo $(SRCS)
	$(CC) -o $@ $^ $(CFLAGS) $(BUILDFLAGS)

unit_tests.exe : $(OBJS) $(OUTPATH)check_main.o $(OUTPATH)check_find.o $(OUTPATH)check_pop_back.o $(OUTPATH)check_pop_front.o $(OUTPATH)check_reverse.o $(OUTPATH)check_sort.o
	$(CC) -o $@ $^ -lm -g3 -O0 $(CFLASG) $(TESTBUILDFLAGS)

$(OUTPATH)%.o : */%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUTPATH)%.d : */%.c
	$(CC) -MM $< > $@

include $(SRCS:.c=.d)

release.lastbuildstate :
	rm -rf *.lastbuildstate
	touch release.lastbuildstate

debug.lastbuildstate :
	rm -rf *.lastbuildstate
	touch debug.lastbuildstate

unit.lastbuildstate :
	rm -rf *.lastbuildstate
	touch unit.lastbuildstate

.PHONY: debug
debug: CFLAGS += $(DEBUGFLAGS) --coverage
debug: BUILDFLAGS += --coverage
debug: app.exe | debug.lastbuildstate

.PHONY: release
release: CFLASGS += -O3
release: app.exe | release.lastbuildstate

.PHONY: func
func: debug
	$(FUNCPATH)scripts/func_tests.sh
	make coverage
	#make clean

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
	rm -f *.exe *.d out.txt out/out.txt *.lastbuildstate *.o out/*.o out/*.gcda out/*.gcno out/*.gcov vgcore.*