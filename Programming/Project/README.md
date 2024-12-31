### Environment Dependencies

- Please ensure that the `Eigen` library is installed.



### Command

- `make solution`: Compile all the cpp files in the Solution directory (note that each cpp file is an independent program, each containing its own main function).
- `make report`: Compile the tex files to generate a pdf file, while clearing the intermediate files generated during the process.
- `make A`: Run the compiled executable of A.cpp and invoke the A.py plotting script in the Plot_py directory.
- `make BCD`: Run the compiled executable of B_C_D.cpp to generate Results_357.csv, Results_358.csv, Results_pp.csv, and then invoke the plot.py script in Plot_py, which is controlled by command-line arguments for plotting files, such as `python plot.py Results_357.csv`.
- `make E`: Run the compiled executable of E.cpp and invoke the E_even.py and E_ccl.py plotting scripts in Plot_py.
- `make Eextra`: Run the compiled executable of E_extra.cpp and invoke the plot.py script to plot r2_CCL.csv and r2_even.csv, and invoke plot_3d.py to plot r3_CCL.csv and r2_even.csv (plot_3d.py is a command-line argument-controlled program similar to plot.py).
- `make F`: Run the compiled executable of F.cpp and invoke the plot.py script in Plot_py to plot TruncatedPower_1_0_2.csv and TruncatedPower_2_0_3.csv.
- `make Sphere`: Run the compiled executable of Sphere.cpp and invoke the Sphere.py plotting script in Plot_py.
- `make clear`: Clear all csv files and generated executable files, keeping only the source files.



### Suggestions

- The compilation of `test.cpp` is not provided here. If you wish to test how jsoncpp controls parameters, you can compile `test.cpp` on your own to check.
- The answer provided here only shows the final result of the difference. If you want to verify each truncated difference, you can refer to the suggestions in the report and plot the corresponding csv files on your own.