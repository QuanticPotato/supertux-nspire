EXE=scanner

all: $(EXE)

$(EXE): main.cpp
	g++ -std=c++11  main.cpp -lboost_system -lboost_filesystem -g
	mv a.out $(EXE)

