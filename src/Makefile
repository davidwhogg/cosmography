#
# WARNING: make clean will destroy *.out
#
CFLAGS= -O

MAKEPLOTS = makeplots.o cosmography.o schechter.o
makeplots: $(MAKEPLOTS)
	cc $(MAKEPLOTS) -o makeplots -lm

clean:
	rm -f *.o core makeplots *.out
