
all: code

code: code.cpp
	g++-13 -O3 code.cpp -o code

clean:
	rm -f code
