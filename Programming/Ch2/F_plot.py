import numpy as np
import matplotlib.pyplot as plt

# Function to load the exported data
def load_interpolated_data(filename):
    data = np.loadtxt(filename, delimiter=',')
    x_vals = data[:, 0] 
    y_vals = data[:, 1] 
    return x_vals, y_vals

# Plotting the data for multiple datasets
def plot_multiple_curves1(filenames, labels):
    plt.figure()

    for filename, label in zip(filenames, labels):
        x_vals, y_vals = load_interpolated_data(filename)
        plt.plot(x_vals, y_vals, label=label)  # Plot each curve with its label

    # Add labels and legend
    plt.title('Bezier Curves')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.grid(True)
    plt.show()

filenames = ['BezierCurve_10.csv', 'BezierCurve_40.csv', 'BezierCurve_160.csv']
labels = ['m=10', 'm=40', 'm=160']
plot_multiple_curves1(filenames, labels)
