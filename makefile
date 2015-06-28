CC ?= gcc
PY = python
CFLAGS = -Wall -c -std=c99
LDFLAGS = -lm
INCLUDE = /usr/include

.PHONY: test
test:
	$(PY) test/test.py

clean:
	-find . -type f -name '*.test' -delete; find . -type f -name '*.o' -delete; find . -type f -name '*.output' -delete

install:
	cp src/* $(INCLUDE)

uninstall:
	-rm -r $(INCLUDE)/hac_*

