CC=g++
CFLAGS=-Og --std=c++14 -Wall -Wextra -pedantic -g
LDFLAGS=-lpthread -L${GTEST_BASE}/lib -lgtest
INCLUDES=-I${GTEST_BASE}/include -I../

OBJS = testsuite.o \
			 measurements_test.o \
			 list_test.o \

.DEFAULT: all
all: $(OBJS) testsuite.bin

run: clean testsuite.bin
	./testsuite.bin

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

%.bin: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

.PHONY: clean
clean:
	-rm -f *.o
	-rm -f *.a
	-rm -f *.bin
	-rm -f ../solution/*.o
	-rm -f ../solution/*.a

