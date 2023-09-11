import numpy as np
import matplotlib.pyplot as plt
import pandas as pd


data = pd.read_csv(r"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\exact_points.dat", delimiter=" ")
x = data.values[:,0]
u = data.values[:,1]
plt.plot(x,u,label="Exact solution")


n_steps = np.array([10,100,1000,10000])
for n in n_steps:
    data = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\solution_n={n}.dat", delimiter=" ")
    x = data.values[:,0]
    v = data.values[:,1]
    plt.plot(x,v,label=f"n_steps={n}")

plt.xlabel("x")
plt.ylabel("u(x) or v(x) for numerical")
plt.legend()
plt.savefig("fys3150project1fig2.pdf")
plt.show()
