# To add a new cell, type '# %%'
# To add a new markdown cell, type '# %% [markdown]'
# %%
import os, sys
import numpy as np
import matplotlib as mpl
import matplotlib.cbook as cb
import matplotlib.pyplot as plt


# %%
def read_file(fname):
    data = np.genfromtxt(fname, dtype=int, names=['n', 'abb', 'avl'])
    return data


# %%
notebook_path = os.path.abspath("plot.ipynb")
file_path = os.path.join(os.path.dirname(notebook_path), "out.txt")

data = read_file(file_path)
data.sort(axis=0)

fig = plt.figure(figsize=[10,7])

ax = plt.subplot()

ax.plot(data['n'], data['abb'], 'o-', label="ABB", lineWidth=2)
ax.plot(data['n'], data['avl'], 'o-', label="AVL", lineWidth=2)
ax.legend()

ax.set(xlabel='Número Procurado', ylabel='Quantidade de Comparações', title="ABB vs. AVL")

ax.yaxis.set_major_locator(mpl.ticker.MultipleLocator(2))
ax.yaxis.set_minor_locator(mpl.ticker.MultipleLocator(1))

ax.xaxis.set_major_locator(mpl.ticker.MultipleLocator(5000))
ax.xaxis.set_minor_locator(mpl.ticker.MultipleLocator(2500))

plt.show()

