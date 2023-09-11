import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

n_steps = np.array([10,100,1000,10000])
for n in n_steps:
    data = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\abs_err_n={n}.dat", delimiter=" ")
    x = data.values[:,0]
    abs_err = data.values[:,1]
    plt.plot(x,abs_err,label=f"n_steps={n}")

plt.xlabel("x")
plt.ylabel("log10(abs_err)")
plt.legend()
plt.savefig("fys3150project1fig3.pdf")
plt.show()

for n in n_steps:
    data = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\rel_err_n={n}.dat", delimiter=" ")
    x = data.values[:,0]
    rel_err = data.values[:,1]
    plt.plot(x,rel_err,label=f"n_steps={n}")

plt.xlabel("x")
plt.ylabel("log10(rel_err)")
plt.legend()
plt.savefig("fys3150project1fig4.pdf")
plt.show()

#max(rel_error):
data = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\max_rel_err.dat", delimiter=" ")
n_steps = data.values[:,0]
max_rel_err = data.values[:,1]
plt.plot(np.log10(n_steps),np.log10(max_rel_err))
plt.xlabel("log10(n_steps)")
plt.ylabel("log10(max(rel_err))")
plt.savefig("fys3150project1fig5.pdf")
plt.show()

for i in range(len(n_steps)):
    print(f"n_steps={n_steps[i]:.1e}, max(rel_error)={max_rel_err[i]}")
