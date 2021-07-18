CC = g++
src = $(wildcard *.cpp)
obj = $(src:.c=.o)

FLAGS = -Wall -Og -g

Life: $(obj)
	$(CC) -o $@ $^ $(FLAGS)

clean:
	rm -f $(obj) Life
