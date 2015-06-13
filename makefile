CC = gcc
CFLAGS = -Wall -c -std=c11
LDFLAGS = -lm
TESTS =\
hac_vec_foreach.test hac_vec_foldr.test hac_vec_foldl.test hac_vec_filter.test hac_vec_sort.test\
hac_seq_foreach.test hac_seq_foldr.test hac_seq_foldl.test hac_seq_filter.test hac_seq_reverse.test

release: CFLAGS += -O2
release: LDFLAGS += -O2
release: all

debug: CFLAGS += g
debug: LDFLAGS += -g
debug: all

all: $(TESTS)

%.test: %_test.o
	$(CC) $(LDFLAGS) -o $@ $<

%.o: %.c
	$(CC) $(CFLAGS) -o $@ $<

test:
	./test.sh $(TESTS)

clean:
	-rm *.test && rm *.o

