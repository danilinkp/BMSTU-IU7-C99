CC := gcc

LIBPATH := ./lib/
SRCPATH := ./src/
INCPATH := ./inc/
UNITPATH := ./unit_tests/
FUNCPATH := ./func_tests/
OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))
$(shell mkdir -p $(LIBPATH))

OBJS := $(OUTPATH)dynamic_array.o
SRCS := $(wildcard *.c)

CFLAGS := -std=c99 -Wall -Werror -Wextra -Wfloat-equal -Wfloat-conversion -I$(INCPATH)
DEBUGFLAGS := -O0 -g3
BUILDFLAGS := -lm
TESTBUILDFLAGS := -lcheck -lpthread

STATIC_LIB := $(LIBPATH)libarr.a
SHARED_LIB := $(LIBPATH)libarr.so

app_static.exe : $(OUTPATH)main.o $(STATIC_LIB)
	$(CC) -o $@ $< $(CFLAGS) $(STATIC_LIB) $(BUILDFLAGS)

app_shared.exe : $(OUTPATH)main.o $(SHARED_LIB)
	$(CC) -o $@ $< $(CFLAGS) -L$(LIBPATH) -larr $(BUILDFLAGS) -lgcov

app_dlfcn.exe : $(OUTPATH)main_dlfcn.o $(SHARED_LIB)
	$(CC) -o $@ $< $(CFLAGS) -ldl $(BUILDFLAGS) -lgcov

unit_tests.exe : $(OBJS) $(OUTPATH)check_key.o $(OUTPATH)check_mysort.o $(OUTPATH)check_main.o
	$(CC) -o $@ $^ $(CFLASG) $(TESTBUILDFLAGS)

$(OUTPATH)%.o : */%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OUTPATH)%.d : */%.c
	$(CC) -MM $< > $@

include $(SRCS:.c=.d)

$(STATIC_LIB): $(OBJS)
	ar cr $@ $^
	ranlib $@

$(SHARED_LIB): CFLAGS += -fPIC
$(SHARED_LIB): $(OBJS)
	$(CC) -o $@ -shared $^ -lgcov

release_static.lastbuildstate :
	rm -rf *.lastbuildstate
	touch release_static.lastbuildstate

debug_static.lastbuildstate :
	rm -rf *.lastbuildstate
	touch debug.lastbuildstate

release_shared.lastbuildstate :
	rm -rf *.lastbuildstate
	touch release_shared.lastbuildstate

debug_shared.lastbuildstate :
	rm -rf *.lastbuildstate
	touch debug_shared.lastbuildstate

release_dlfcn.lastbuildstate :
	rm -rf *.lastbuildstate
	touch release_dlfcn.lastbuildstate

debug_dlfcn.lastbuildstate :
	rm -rf *.lastbuildstate
	touch debug_dlfcn.lastbuildstate

unit.lastbuildstate :
	rm -rf *.lastbuildstate
	touch unit.lastbuildstate

.PHONY: debug_static
debug_static: CFLAGS += $(DEBUGFLAGS) --coverage
debug_static: app_static.exe | debug_static.lastbuildstate

.PHONY: debug_shared
debug_shared: CFLAGS += $(DEBUGFLAGS) --coverage
debug_shared: app_shared.exe | debug_shared.lastbuildstate

.PHONY: debug_dlfcn
debug_dlfcn: CFLAGS += $(DEBUGFLAGS) --coverage
debug_dlfcn: app_dlfcn.exe | debug_dlfcn.lastbuildstate

.PHONY: release_static
release: CFLAGS += -O3
release: app_static.exe | release_static.lastbuildstate

.PHONY: release_shared
release: CFLAGS += -O3
release: app_shared.exe | release_shared.lastbuildstate

.PHONY: release_dlfcn
release: CFLAGS += -O3
release: app_dlfcn.exe | release_dlfcn.lastbuildstate

.PHONY: func
func: debug_static
	$(FUNCPATH)scripts/func_tests.sh
	make coverage
	make clean

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