# Elliptic curve on finite field (GF(p))
import math
import matplotlib.pyplot as plt
from prettytable import PrettyTable

def quadratic_residues(p):
    ul = math.floor(p/2)
    residues = {}
    for i in range(ul + 1):
        residues[(i*i) % p] = i
    return residues

def plot_points(points, a, b):
    x_values = [point[0] for point in points]
    y_values = [point[1] for point in points]
    plt.scatter(x_values, y_values, label="Points", color='blue')
    plt.xlabel('X-axis')
    plt.ylabel('Y-axis')
    plt.title('Points on the Elliptic Curve: y^2 = x^3 + {}x + {}'.format(a, b))
    plt.legend()
    plt.grid(True)
    plt.show()

def main():
    p = int(input("Enter the value of p: "))
    a = int(input("Enter the value of a: "))
    b = int(input("Enter the value of b: "))
    
    print("Equation: y^2 = x^3 + {}x + {}".format(a, b))

    points = set()
    residues = quadratic_residues(p)
    table = PrettyTable(header=False)
    for x in range(p):
        w = (x*x*x + a*x + b) % p
        if w == 0:
            points.add((x, 0))
            table.add_row([f"({x}, {0})",f"({x}, {0})"])
        elif w in residues:
            points.add((x, residues[w]))
            points.add((x, p - residues[w]))
            table.add_row([f"({x}, {residues[w]})",f"({x}, {p-residues[w]})"])
    print(table)

    plot_points(points, a, b)

if __name__ == "__main__":
    main()
