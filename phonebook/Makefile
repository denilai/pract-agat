iEdit: $(patsubst %.c,%.o,$(wildcard *.c))
	gcc $^ -o $@ 

%.o: %.cpp
	gcc -c -MD $<

include $(wildcard *.d) 
