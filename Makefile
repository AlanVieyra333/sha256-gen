PROJ = find-sha
MAIN = main.c
OBJS = lib/sha256.o lib/utils.o
CFLAGS = -std=c99 -O3
LFLAGS = -Ilib
CC = gcc

HASH = 4852c8159c4fcde8444ec454acc21381680c990f2fc611e8a713513b494e6bc5

$(PROJ): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -Wall -o $@ $<

run: $(PROJ)
	./$(PROJ) $(HASH)

clean:
	rm -rf $(PROJ) *.o **/*.o