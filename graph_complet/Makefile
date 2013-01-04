CXX=g++
BIN=graph_complet

SRC=$(wildcard src/*.cpp)
OBJ=$(SRC:src/%.c=build/%.o)
DEPS=$(SRC:src/%.c=build/%.d)

all: $(OBJ)
	$(CXX) -o $(BIN) $^

build/%.o: src/%.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

build/%.d: src/%.cpp
	$(CC) $(CFLAGS) -MM -MD -o $@ $<

clean:
	rm -f build/*.o
	rm -f build/*.d
	rm -f resultats/*.*

mrproper: clean
	rm -f $(BIN)

.PHONY: clean mrproper

zip:
	tar -zcvf $(BIN).tar.gz $(SRC) $^

run:
	./$(BIN) 10 1 20 monGraph.txt 

    
