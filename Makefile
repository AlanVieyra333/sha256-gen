PROJ = sha256
MAIN = main.c
OBJS = lib/sha256.o lib/utils.o
APPS = sha256-breakdown.a reverse_func.a
CFLAGS = -std=c99 -O3
LFLAGS = -Ilib
CC = gcc

MESSAGE = 50aa1d9bfd848b6560edcdb0a95ee3fa0ff36b8cb6cdc6a5ee0dfdc41087dc56
HASH = 4852c8159c4fcde8444ec454acc21381680c990f2fc611e8a713513b494e6bc5
# MESSAGE = 12b35aa4961f37e7c081919ea94d159bde10f0f0c49f1e441812234bce3ed5b8
# HASH = b53e3fef44fefc3defc68716e2d8675e3fb0e0882357ff92a0432637baca03db


all: $(PROJ) $(APPS)

$(PROJ): $(MAIN) $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c -Wall -o $@ $<

$(APPS): %.a: %.c $(OBJS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $@ $^

model: data.csv hash_round_predict.py
	python hash_round_predict.py

model2: data.csv hash_predict.py
	python hash_predict.py

data.csv: $(PROJ) gen_in_msg.a gen_data.sh
	./gen_data.sh

test: $(PROJ)
	./$(PROJ) $(MESSAGE)

clean:
	rm -rf $(PROJ) *.a *.o **/*.o

.PHONY: all model test clean