CC = gcc
CFLAGS = -Wall -c -std=c1x
LDFLAGS = -lm
TESTS = hac_vec_foreach.test hac_vec_foldr.test hac_vec_foldl.test hac_vec_filter.test

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

