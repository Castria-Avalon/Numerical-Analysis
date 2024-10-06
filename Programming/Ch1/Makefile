CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRC = B.cpp C.cpp D.cpp E.cpp F.cpp
TARGETS = $(SRC:.cpp=)
OUTPUT_DIR = output

.PHONY: all clean run report

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

report: report.tex
	@pdflatex report.tex
	@bibtex report.aux
	@pdflatex report.tex
	@pdflatex report.tex
	@rm -f *.aux *.log *.out *.synctex.gz *.toc *.bbl *.run.xml *.blg

clean:
	rm -f $(OUTPUT_DIR)/* *.o
	rmdir $(OUTPUT_DIR)