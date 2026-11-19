CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g

lojadecarros: main.cpp *.h
	$(CXX) $(CXXFLAGS) main.cpp -o lojadecarros

run: lojadecarros
	./lojadecarros

clean:
	rm -f lojadecarros
