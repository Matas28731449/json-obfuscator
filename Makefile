compile:
	g++ -std=c++11 -o main src/main.cpp src/string_encoder.cpp src/json_encoder.cpp

run: compile
	./main $(ARGS)

clean:
	rm -f *.o main