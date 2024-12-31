# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -I src/include src/Spline.cpp src/plotRW.cpp -ljsoncpp

# Directories
SRC_DIR = src/Solution
PLOT_DIR = $(SRC_DIR)/Plot_py
BIN_DIR = bin

# Ensure directories exist
$(shell mkdir -p $(BIN_DIR) $(RESULTS_DIR))

# Sources
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
EXECS = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%,$(SOURCES))

# Phony targets
.PHONY: all solution report A BCD E Eextra F Sphere clear

# Build all
all: solution report

# Compile all solutions
solution: $(EXECS)

$(BIN_DIR)/%: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $< -o $@

# Compile LaTeX reports
report:
	cd doc && pdflatex design.tex && pdflatex report.tex && bibtex report.aux
	cd doc && pdflatex design.tex && pdflatex report.tex 
	rm -f doc/*.aux doc/*.bbl doc/*.blg doc/*.log doc/*.out  doc/*.xml doc/design-blx.bib doc/report-blx.bib

# Specific targets
A: $(BIN_DIR)/A
	./$(BIN_DIR)/A
	python $(PLOT_DIR)/A.py

BCD: $(BIN_DIR)/B_C_D
	./$(BIN_DIR)/B_C_D
	python $(PLOT_DIR)/plot.py Results_357.csv
	python $(PLOT_DIR)/plot.py Results_358.csv
	python $(PLOT_DIR)/plot.py Results_pp.csv

E: $(BIN_DIR)/E
	./$(BIN_DIR)/E
	python $(PLOT_DIR)/E_even.py
	python $(PLOT_DIR)/E_ccl.py

Eextra: $(BIN_DIR)/E_extra
	./$(BIN_DIR)/E_extra
	python $(PLOT_DIR)/plot.py r2_CCL.csv
	python $(PLOT_DIR)/plot.py r2_even.csv
	python $(PLOT_DIR)/plot_3d.py r3_CCL.csv
	python $(PLOT_DIR)/plot_3d.py r3_even.csv

F: $(BIN_DIR)/F
	./$(BIN_DIR)/F
	python $(PLOT_DIR)/plot.py TruncatedPower_1_0_2.csv
	python $(PLOT_DIR)/plot.py TruncatedPower_2_0_3.csv

Sphere: $(BIN_DIR)/Sphere
	./$(BIN_DIR)/Sphere
	python $(PLOT_DIR)/Sphere.py plot_sphere.csv

# Clean up
clear:
	rm -f  doc/*.pdf   *.csv
	rm -rf $(BIN_DIR)
