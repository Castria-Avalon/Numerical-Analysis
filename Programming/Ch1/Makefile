CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = B.cpp C.cpp D.cpp E.cpp F.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)