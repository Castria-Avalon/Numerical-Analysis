import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit
import argparse

parser = argparse.ArgumentParser(description="Fit and plot a spherical curve and fitted surface from a CSV file.")
parser.add_argument("csv_file", type=str, help="Path to the CSV file containing the data points (x, y, z).")

args = parser.parse_args()
csv_file = args.csv_file

data = pd.read_csv(csv_file, header=None, names=["x", "y", "z"])

x_data = data["x"]
y_data = data["y"]
z_data = data["z"]

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def fit_func(x, y, a, b, c, d, e, f):
    return a * x**2 + b * y**2 + c * x * y + d * x + e * y + f

def fit_surface(x_data, y_data, z_data):
    popt, _ = curve_fit(lambda data, a, b, c, d, e, f: fit_func(data[:, 0], data[:, 1], a, b, c, d, e, f),
                        np.column_stack((x_data, y_data)), z_data)
    return popt

params = fit_surface(x_data, y_data, z_data)

x_fit = np.linspace(min(x_data), max(x_data), 100)
y_fit = np.linspace(min(y_data), max(y_data), 100)
x_fit, y_fit = np.meshgrid(x_fit, y_fit)
z_fit = fit_func(x_fit, y_fit, *params)

ax.plot_surface(x_fit, y_fit, z_fit, color="blue", alpha=0.5)

ax.plot(x_data, y_data, z_data, color="green", label="Fitted Curve")

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.legend()

plt.show()


