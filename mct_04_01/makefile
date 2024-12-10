OUTPATH := ./out/
$(shell mkdir -p $(OUTPATH))

CFLAGS := -std=c99 -Wall -Werror -Wpedantic -Wextra -Wfloat-equal -Wfloat-conversion -I./inc/

app.exe: $(OUTPATH)main.o $(OUTPATH)my_list.o
	gcc -o $@ $^ $(CFLAGS)

$(OUTPATH)main.o: ./src/main.c
	gcc -c $< -o $@ $(CFLAGS)

$(OUTPATH)my_list.o: ./src/my_list.c ./inc/my_list.h
	gcc -c $< -o $@ $(CFLAGS)