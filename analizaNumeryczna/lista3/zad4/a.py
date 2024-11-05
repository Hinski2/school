import numpy as np
import matplotlib.pyplot as plt

# Definicja funkcji g(x)
def g(x):
    return np.abs(5 * x / (x - 2024))

# Zakres wartości x
x1 = np.linspace(-5000, 2023.9, 1000)  # Przed asymptotą pionową
x2 = np.linspace(2024.1, 5000, 1000)   # Po asymptocie pionowej

# Obliczenie wartości funkcji
y1 = g(x1)
y2 = g(x2)

# Tworzenie wykresu
plt.figure(figsize=(10, 6))
plt.plot(x1, y1, label='g(x) dla x < 2024')
plt.plot(x2, y2, label='g(x) dla x > 2024')
plt.axvline(x=2024, color='red', linestyle='--', label='Asymptota pionowa x=2024')
plt.axhline(y=5, color='green', linestyle='--', label='Asymptota pozioma y=5')
plt.xlabel('x')
plt.ylabel('g(x)')
plt.title('Wykres funkcji g(x) = |5x / (x - 2024)|')
plt.legend()
plt.grid(True)
plt.ylim(0, 50)  # Ustawienie zakresu wartości na osi y
plt.show()