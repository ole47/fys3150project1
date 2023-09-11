import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

data_general = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\times_general.dat", delimiter=" ")
n_steps_general = data_general.values[:,0]
times_general = data_general.values[:,1]
plt.plot(np.log10(n_steps_general),np.log10(times_general),label="General algorithm")

data_special = pd.read_csv(fr"\\wsl.localhost\Ubuntu\home\ole\Fys3150Project1\times_special.dat", delimiter=" ")
n_steps_special = data_special.values[:,0]
times_special = data_special.values[:,1]
plt.plot(np.log10(n_steps_special),np.log10(times_special),label="Special algorithm")

plt.xlabel("log10(n_steps)")
plt.ylabel("log10(t)")
plt.legend()
plt.savefig("fys3150project1fig7.pdf")
plt.show()
