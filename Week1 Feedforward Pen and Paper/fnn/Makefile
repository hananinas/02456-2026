CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -O2
TARGET := main
SOURCES := main.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: run clean
