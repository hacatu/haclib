CC ?= gcc
PY = python3
CFLAGS = -Wall -c -std=c99
LDFLAGS = -lm
INCLUDE = /usr/include

.PHONY: test
test:
	$(PY) test/test.py

clean:
	-rm *.test && rm *.o

install:
	cp src/* $(INCLUDE)

uninstall:
	-rm -r $(INCLUDE)/hac_*

