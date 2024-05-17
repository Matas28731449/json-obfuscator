main:
	g++ -std=c++11 -O3 -w -o src/main src/main.cpp src/string_encoder.cpp src/json_encoder.cpp
	cd src && clear && ./main ../example.json ../example_obfuscated.json

clean:
	rm -f src/*.o src/main