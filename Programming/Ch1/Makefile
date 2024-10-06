CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = B.cpp C.cpp D.cpp E.cpp F.cpp
TARGETS = $(SRC:.cpp=)
OUTPUT_DIR = output

.PHONY: all clean run

all: $(OUTPUT_DIR) $(addprefix $(OUTPUT_DIR)/, $(TARGETS))

$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

$(OUTPUT_DIR)/%: %.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

run: all
	@for target in $(TARGETS); do \
		echo "Running $(OUTPUT_DIR)/$$target:"; \
		./$(OUTPUT_DIR)/$$target; \
	done

clean:
	rm -f $(OUTPUT_DIR)/* *.o
	rmdir $(OUTPUT_DIR)