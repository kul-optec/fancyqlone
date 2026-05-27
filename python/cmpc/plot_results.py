
import scipy.io
import numpy as np
import matplotlib.pyplot as plt
N=1024
nx = 4
nu = 2
data = scipy.io.loadmat(f"python/cmpc/results/data_{N}.mat")
print(data.keys())
ocp = data["ocp"]
print(ocp.shape )
print(data["sol_x"])
X=data["sol_x"].reshape(N, nx+nu)
print(X)
U = X[:, :nu]
X = X[:, nu:]

plt.figure(figsize=(12, 6))
plt.subplot(3, 1, 1)
plt.plot(X[:, 0], label="Position trajectory")
plt.plot(X[:, 2], label="Contingent Position trajectory")
plt.legend()
plt.xlabel("Time")
plt.ylabel("Position")
plt.subplot(3, 1, 2)
plt.plot(X[:, 1], label="Velocity trajectory")
plt.plot(X[:, 3], label="Contingent Velocity trajectory")
plt.legend()
plt.xlabel("Time")
plt.ylabel("Velocity")
plt.subplot(3, 1, 3)
plt.plot(U[:, 0], label="Control input")
plt.plot(U[:, 1], label="Contingency input")
plt.title("OCP Solution")
plt.grid(True)
plt.savefig("python/cmpc/results/solution_plot.png")
