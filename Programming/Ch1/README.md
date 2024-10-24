# Programming Homework of Chapter I

### How to compile

**Testing environment**: Ubuntu 22.04 bash  
**Requirements**: Please pre-install LaTeX-related compilation tools (including biblatex components) and the Make compiler.  
**Commands**:  

- `make`: Compile only the `.cpp` files and store the .exe files in the output directory  
- `make run`: Compile and run all programs  
- `make report`: Compile the .tex file to generate a report  
- `make clean`: Remove all generated files

**Note**: The Makefile does not compile the test file `testSciCal.cpp`. If compilation is needed, please execute the relevant compilation commands separately.



### How to check answer

The report barely covers the description of the output, focusing primarily on the design rationale or explaining some issues encountered during the experimental design. All results can be viewed by compiling and running the `.cpp` files. It is recommended to execute `make run`.