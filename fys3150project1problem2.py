import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_csv(r"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\exact_points.dat", delimiter=" ")
x = data.values[:,0]
u = data.values[:,1]

plt.plot(x,u)
plt.xlabel("x")
plt.ylabel("u(x)")
plt.savefig("fys3150project1fig1.pdf")
plt.show()
