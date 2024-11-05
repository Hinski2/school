import numpy as np
import matplotlib.pyplot as plt

# Define the function g(x)
def g(x):
    return np.abs(8 * x * (1 / np.tan(8 * x)))

# Create an array of x values
x_values = np.linspace(-2, 2, 10000)
# Exclude the points where tan(8x) is zero to avoid division by zero
x_values = x_values[np.abs(np.sin(8 * x_values)) > 1e-10]

# Calculate the corresponding y values
y_values = g(x_values)

# Plot the function
plt.figure(figsize=(12, 6))
plt.plot(x_values, y_values, color='blue')
plt.title(r'Graph of $g(x) = \left| 8x \cot(8x) \right|$')
plt.xlabel('x')
plt.ylabel('g(x)')
plt.ylim(0, 10)  # Adjust the y-axis limit for better visibility
plt.grid(True)

# Mark the asymptotes
for n in range(-5, 6):
    asymptote = n * np.pi / 8
    plt.axvline(x=asymptote, color='red', linestyle='--', alpha=0.5)

plt.show()
