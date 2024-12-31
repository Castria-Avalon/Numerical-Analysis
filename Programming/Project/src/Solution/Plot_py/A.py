import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from scipy.optimize import curve_fit

# 文件列表
file_list = [
    "CubicPlot_N6.csv",
    "CubicPlot_N11.csv",
    "CubicPlot_N21.csv",
    "CubicPlot_N41.csv",
    "CubicPlot_N81.csv"
]


def original_func(x):
    return 1 / (1 + 25 * x ** 2)


colors = ["red", "blue", "green", "orange", "purple"]
styles = ["--", "-.", ":", "-", "--"]

plt.figure(figsize=(12, 8))

x_fit = np.linspace(-1.2, 1.2, 1000)
y_original = original_func(x_fit)

plt.plot(x_fit, y_original, color="black", label="Original Function (1/(1+25x^2))", linewidth=2)

for i, file in enumerate(file_list):
    data = pd.read_csv(file, header=None, names=["x", "y"])

    x_data = data["x"]
    y_data = data["y"]

    plt.plot(x_data, y_data, label=f"Data Line (File {i + 1})", linestyle=styles[i], color=colors[i])


plt.xlabel("X")
plt.ylabel("Y")
plt.title("Data Lines and Original Function Comparison")
plt.legend()
plt.grid()

plt.show()