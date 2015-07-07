CC ?= gcc
PY = python
CFLAGS = -Wall -c -std=c99
LDFLAGS = -lm
INCLUDE = /usr/include

.PHONY: test
test:
	$(PY) test/test.py

clean:
	-find . -type f -name '*.test' -delete
	-find . -type f -name '*.o' -delete
	-find . -type f -name '*.output' -delete

install:
	cp -r src/* $(INCLUDE)

uninstall:
	-rm -r $(INCLUDE)/hac{_*,lib.h}

.PHONY: undefs
undefs:
	$(PY) undefs/undefs.py src hac_obj > undefs/obj.undefs
	$(PY) undefs/undefs.py src hac_util > undefs/util.undefs
	$(PY) undefs/undefs.py src hac_pair > undefs/pair.undefs
	$(PY) undefs/undefs.py src hac_vec > undefs/vec.undefs
	$(PY) undefs/undefs.py src hac_seq > undefs/seq.undefs
	$(PY) undefs/undefs.py src hac_avl > undefs/avl.undefs
	$(PY) undefs/undefs.py src hac_it > undefs/it.undefs

