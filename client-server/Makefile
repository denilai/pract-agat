demo: $(patsubst %.c, %.o, $(wildcard *.c))
	gcc $^ -o $@

%.o: %.c
	gcc -c -MD $<

include $(wildcard *.d)
