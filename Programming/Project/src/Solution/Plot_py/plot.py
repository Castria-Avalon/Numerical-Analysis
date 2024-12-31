import numpy as np
import matplotlib.pyplot as plt
import argparse

# Setup argument parser
parser = argparse.ArgumentParser(description="Plot a 2D curve from a CSV file.")
parser.add_argument("csv_file", type=str, help="Path to the CSV file containing the data points (x, y).")

args = parser.parse_args()
csv_file = args.csv_file

# Load data from CSV file
data = np.loadtxt(csv_file, delimiter=',')
x_data = data[:, 0]
y_data = data[:, 1]

# Plot the curve
plt.plot(x_data, y_data, linestyle='-', color='b', label='Curve')

plt.xlabel('x')
plt.ylabel('y')
plt.legend()
plt.title('Plot for 2-dimensional data')
plt.grid(True)

plt.show()
