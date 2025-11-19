srcdir = src
includedir = include

heat-bin = heat
heat-obj = variables.o io.o linalg.o right_hand_side.o conjugate_gradient.o fgh.o matmul_A.o distribution.o heat.o

order-bin = order
order-obj = variables.o io.o linalg.o right_hand_side.o conjugate_gradient.o fgh.o matmul_A.o order.o

# test-bin = test
# test-obj = distribution.o test.o

objects = $(sort $(heat-obj) $(order-obj))
binaries = $(heat-bin) $(order-bin)

libflags = -lm
optflags = -O3
warning-flags = -Wall -Wextra -Wpedantic
std-flags = -std=c17
cflags = $(libflags) $(optflags) $(warning-flags) $(std-flags)

cc = mpicc

default: $(binaries)

$(heat-bin): $(heat-obj)
	$(cc) $(cflags) -o $(heat-bin) $(heat-obj)

$(order-bin): $(order-obj)
	$(cc) $(cflags) -o $(order-bin) $(order-obj)

$(test-bin): $(test-obj)
	$(cc) $(cflags) -o $(test-bin) $(test-obj)

$(objects):%.o: $(srcdir)/%.c
	$(cc) -I $(includedir) $(cflags) -c -o $@ $<

.PHONY: output clean clean_output clean_all

output: cas1_output cas2_output order_output

cas1_output:
	./heat input/cas1.in output/cas1.out
cas2_output:
	./heat input/cas2.in output/cas2.out
order_output:
	./order input/order.in output/order.out
clean:
	rm $(binaries) $(objects)

clean_output: 
	rm output/*

clean_all: clean clean_output

test:
	$(cc) -I $(includedir) -o test_dist $(srcdir)/test.c $(srcdir)/distribution.c
