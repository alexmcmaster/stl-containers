#!/usr/bin/env python

import sys
import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

d = pd.read_csv(sys.stdin if len(sys.argv) == 1 else sys.argv[1])
d["log duration"] = np.log10(d["duration_ns"])
print(d.describe())

#d.hist(column="log duration", bins=100)
fig, axs = plt.subplots(2, 1)
fig.set_size_inches(12, 9)
axs[0].plot(d["duration_ns"])
axs[0].set_ylabel("ns")
axs[0].set_title("op duration")
if "final cap" in d.columns:
    axs[1].plot(d["final cap"])
    axs[1].set_ylabel("capacity")
    axs[1].set_xlabel("count")
    axs[1].set_title("allocated size")
plt.show()
