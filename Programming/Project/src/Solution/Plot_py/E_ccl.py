import numpy as np
import matplotlib.pyplot as plt

def heart_curve_upper_lower(num_points=1000):
    x_vals = np.linspace(-np.sqrt(3), np.sqrt(3), num_points)  # x 的范围由方程的定义决定
    upper_y = (2 / 3) * (np.sqrt(3 - x_vals ** 2) + np.sqrt(np.abs(x_vals)))  # 上半部分
    lower_y = (2 / 3) * (-np.sqrt(3 - x_vals ** 2) + np.sqrt(np.abs(x_vals)))  # 下半部分
    return x_vals, upper_y, lower_y


# 2. 读取文件数据点函数
def read_data(file_path):
    data = np.loadtxt(file_path, delimiter=',')  # 假设数据是逗号分隔的
    return data[:, 0], data[:, 1]  # 返回 x 和 y 数据


# 3. 绘制曲线
def plot_curves(x_vals, upper_y, lower_y, file_paths):
    plt.figure(figsize=(8, 8))

    # 绘制心形曲线（上半部分和下半部分）
    plt.plot(x_vals, upper_y, 'r-', label='Heart Curve (Upper Part)')
    plt.plot(x_vals, lower_y, 'r-', label='Heart Curve (Lower Part)')

    # 绘制 Bézier 数据点生成的曲线
    for i, file_path in enumerate(file_paths):
        x, y = read_data(file_path)
        plt.plot(x, y, label=f'Plot Curve (File {i + 1})')

    # 图例和样式
    plt.title('Heart Curve and Bézier Approximation')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.legend()
    plt.axis('equal')
    plt.grid(True)
    plt.show()

# 4. 主程序
if __name__ == "__main__":
    # 生成心形曲线数据
    x_vals, upper_y, lower_y = heart_curve_upper_lower()

    # 文件路径列表（替换为实际文件路径）
    file_paths = ["HeartCurve_CCL_10.csv", "HeartCurve_CCL_40.csv", "HeartCurve_CCL_160.csv"]  # 需要用实际文件名替换

    # 绘制对比图
    plot_curves(x_vals, upper_y, lower_y, file_paths)

