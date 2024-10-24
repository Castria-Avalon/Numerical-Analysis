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

    def f_exact1(x):
        return 1 / (1 + x**2)

    x_exact = np.linspace(-5, 5, 1000)  # Fine range for exact function
    y_exact = f_exact1(x_exact)
    plt.plot(x_exact, y_exact, 'k--', label='Exact function')  # Exact function for B

    # Add labels and legend
    plt.title('Interpolated Curves vs Exact Function')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.grid(True)
    plt.show()

def plot_multiple_curves2(filenames, labels):
    plt.figure()

    for filename, label in zip(filenames, labels):
        x_vals, y_vals = load_interpolated_data(filename)
        plt.plot(x_vals, y_vals, label=label)  # Plot each curve with its label
    
    def f_exact2(x):
        return 1 / (1 + 25*x**2)

    x_exact2 = np.linspace(-1, 1, 1000)  # Fine range for exact function
    y_exact2 = f_exact2(x_exact2)
    plt.plot(x_exact2, y_exact2, 'k--', label='Exact function')  # Exact function for C

    # Add labels and legend
    plt.title('Interpolated Curves vs Exact Function')
    plt.xlabel('x')
    plt.ylabel('f(x)')
    plt.legend()
    plt.grid(True)
    plt.show()

filenames = ['NewtonInterpolation_n_2.csv', 'NewtonInterpolation_n_4.csv', 'NewtonInterpolation_n_6.csv', 'NewtonInterpolation_n_8.csv']
labels = ['n=2', 'n=4', 'n=6', 'n=8']
plot_multiple_curves1(filenames, labels)

filenames2 = ['NewtonInterpolation_Chebyshev_n_5.csv', 'NewtonInterpolation_Chebyshev_n_10.csv', 'NewtonInterpolation_Chebyshev_n_15.csv', 'NewtonInterpolation_Chebyshev_n_20.csv']
labels2 = ['n=5', 'n=10', 'n=15', 'n=20']
plot_multiple_curves2(filenames2, labels2)
