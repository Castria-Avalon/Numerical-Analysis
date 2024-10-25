# Programming Homework of Chapter II

### How to compile

**Testing environment**: Ubuntu 22.04 bash  
**Requirements**: Please pre-install LaTeX-related compilation tools (including biblatex components) and the Make compiler.  
**Commands**:  

- `make`: Compile only the `.cpp` files and store the .exe files in the output directory  
- `make run`: Compile and run all programs 
- `make figure_clean` ：Run the code to obtain all the fitted images and delete all the CSV files.
- `make figure`: Run the code to obtain all the fitted images.
  - `make figure B_C`: Generate the graph for problem B and C.
  - `make figure E`: Generate the graph for problem E.
  - `make figure F`: Generate the graph for problem F.
- `make report`: Compile the `.tex` file to generate a report  
- `make clean`: Remove all generated files

**Note**: 

Do not delete any CSV files arbitrarily, as it will affect the generation of images. After running `make figure_clean`, all CSV files will be automatically deleted after the images are generated. Please run `make run` to regenerate the CSV files. If file deletion is not required, please run `make figure`.



### How to check answer

The report barely covers the description of the output, focusing primarily on the design rationale or explaining some issues encountered during the experimental design. All results can be viewed by compiling and running the `.cpp` files. It is recommended to execute `make run`.