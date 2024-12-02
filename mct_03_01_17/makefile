CC := gcc

CFLAGS := -std=c99 -Wall -Werror -Wpedantic
$(shell mkdir -p ./out)
OBJS := out/set.o

app.exe: $(OBJS) out/main.o
	$(CC) -o $@ $(CFLAGS)