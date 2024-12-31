import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from scipy.optimize import curve_fit
import argparse

# 创建命令行参数解析器
parser = argparse.ArgumentParser(description="Fit and plot a spherical curve and fitted surface from a CSV file.")
parser.add_argument("csv_file", type=str, help="Path to the CSV file containing the data points (x, y, z).")

# 解析命令行参数
args = parser.parse_args()
csv_file = args.csv_file

# 读取csv文件
data = pd.read_csv(csv_file, header=None, names=["x", "y", "z"])

# 提取x, y, z数据
x_data = data["x"]
y_data = data["y"]
z_data = data["z"]

# 拟合函数（此处使用简单的二次多项式拟合，实际上可以根据需求修改函数）
def fit_func(x, y, a, b, c, d, e, f):
    return a * x**2 + b * y**2 + c * x * y + d * x + e * y + f

# 使用curve_fit进行拟合
def fit_surface(x_data, y_data, z_data):
    # 对所有的x, y点拟合z值
    popt, _ = curve_fit(lambda data, a, b, c, d, e, f: fit_func(data[:, 0], data[:, 1], a, b, c, d, e, f),
                        np.column_stack((x_data, y_data)), z_data)
    return popt

params = fit_surface(x_data, y_data, z_data)

# 创建拟合的曲面
x_fit = np.linspace(min(x_data), max(x_data), 100)
y_fit = np.linspace(min(y_data), max(y_data), 100)
x_fit, y_fit = np.meshgrid(x_fit, y_fit)
z_fit = fit_func(x_fit, y_fit, *params)

# 定义球面曲线的参数
R = 1.0  # 球的半径
num_points = 100  # 样条点的数量
t = np.linspace(0, 2 * np.pi, num_points)  # 参数 t

# 球坐标到笛卡尔坐标的转换
theta = t  # 经度随 t 线性变化
phi = (np.pi / 4) * np.sin(t)  # 纬度以正弦变化

# 转换为笛卡尔坐标
x_spline = R * np.cos(phi) * np.cos(theta)
y_spline = R * np.cos(phi) * np.sin(theta)
z_spline = R * np.sin(phi)

# 创建球面
u = np.linspace(0, 2 * np.pi, 100)
v = np.linspace(0, np.pi, 100)
X = R * np.outer(np.cos(u), np.sin(v))
Y = R * np.outer(np.sin(u), np.sin(v))
Z = R * np.outer(np.ones(np.size(u)), np.cos(v))

fig = plt.figure(figsize=(10, 7))
ax = fig.add_subplot(111, projection='3d')

# ax.plot_surface(X, Y, Z, color='b', alpha=0.3, edgecolor='k', label='Original Sphere')

ax.plot_surface(x_fit, y_fit, z_fit, color="blue", alpha=0.5, label='Fitted Surface')

ax.plot(x_spline, y_spline, z_spline, color='r', label='Original Sphere Spline', linewidth=2)

ax.plot(x_data, y_data, z_data, color="green", label="Fitted Curve")

ax.set_xlabel("X")
ax.set_ylabel("Y")
ax.set_zlabel("Z")
ax.set_title("Spherical Curve and Fitted Surface Comparison")
ax.legend()

plt.show()
