import pandas as pd
import matplotlib.pyplot as plt

# 读取第一份CSV文件
data1 = pd.read_csv('AverageWeight1.csv', header=None)
x1 = data1[0]
y1 = data1[1]

# 读取第二份CSV文件
data2 = pd.read_csv('AverageWeight2.csv', header=None)
x2 = data2[0]
y2 = data2[1]

# 绘制曲线
plt.plot(x1, y1, marker='o', label='Sp1')
plt.plot(x2, y2, marker='x', label='Sp2')
plt.title('Average weight curve for two examples')
plt.xlabel('X-axis Label')
plt.ylabel('Y-axis Label')
plt.legend()
plt.grid()
plt.show()
