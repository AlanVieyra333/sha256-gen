PROJ = sha256-breakdown.a
MAIN = sha256-breakdown.c
OBJS = lib/sha256.o lib/utils.o
CFLAGS = -std=c99 -O3
LFLAGS = -Ilib
CC = gcc

MESSAGE = 50aa1d9bfd848b6560edcdb0a95ee3fa0ff36b8cb6cdc6a5ee0dfdc41087dc56
HASH = 4852c8159c4fcde8444ec454acc21381680c990f2fc611e8a713513b494e6bc5

$(PROJ): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -Wall -o $@ $<

run: $(PROJ)
	./$(PROJ) $(MESSAGE)

clean:
	rm -rf $(PROJ) *.o **/*.o