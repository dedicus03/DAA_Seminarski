CXX = g++
CXXFLAGS = -Wall -Wextra -Wno-missing-field-initializers -std=c++17

izvrsni: main.o fft.o complex.o
	$(CXX) -o $@ $^

main.o: src/main.cpp src/fft.hpp src/complex.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

fft.o: src/fft.cpp src/fft.hpp src/complex.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

complex.o: src/complex.cpp src/complex.hpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f fft.o complex.o izvrsni main.o kompresovana.png