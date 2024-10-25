output_dir = output
report_file = report.tex
cpp_sources = B_and_C.cpp D.cpp E.cpp F.cpp
cpp_executables = $(addprefix $(output_dir)/, $(basename $(cpp_sources)))
python_scripts = BC_plot.py E_plot.py F_plot.py

.PHONY: all compile run figure_clean figure report clean

# Compile all .cpp files and store the .exe files in the output directory
compile: $(cpp_executables)

$(output_dir)/%: %.cpp
	@mkdir -p $(output_dir)
	g++ $< Interpolation.cpp -o $@

# Compile and run all programs
run: compile
	@for exe in $(cpp_executables); do \
		echo "Running $$exe..."; \
		./$$exe; \
	done

# Run the code to obtain all the fitted images and delete all the CSV files
figure_clean: figure
	@rm -f *.csv

# Run the code to obtain all the fitted images
figure: $(python_scripts)
	@echo "Running all Python scripts simultaneously..."
	@python3 BC_plot.py & python3 E_plot.py & python3 F_plot.py & wait


# Generate the graph for problem B and C
figure_B_C: BC_plot.py
	python3 BC_plot.py

# Generate the graph for problem E
figure_E: E_plot.py
	python3 E_plot.py

# Generate the graph for problem F
figure_F: F_plot.py
	python3 F_plot.py

# Compile the .tex file to generate a report
report: report.tex
	@pdflatex report.tex
	@bibtex report.aux
	@pdflatex report.tex
	@pdflatex report.tex
	@rm -f *.aux *.log *.out *.synctex.gz *.toc *.bbl *.run.xml *.blg report-blx.bib

# Remove all generated files
clean:
	@rm -rf $(output_dir) *.aux *.log report.pdf *.csv
