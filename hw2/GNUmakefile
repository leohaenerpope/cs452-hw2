all: balloc balloc_test

include ../GNUmakefile

CORE_OBJS = $(filter-out main.o balloc_test.o, $(objs))

balloc: $(CORE_OBJS) main.o
	$(ld) -o $@ $^ $(ldflags)

balloc_test: $(CORE_OBJS) balloc_test.o
	$(ld) -o $@ $^ $(ldflags)

.PHONY: all test

test: balloc_test
	./balloc_test