import os, sys
import numpy as np
import matplotlib as mpl
import matplotlib.cbook as cb
import matplotlib.pyplot as plt

def read_file(fname):
    data = np.genfromtxt(fname, dtype=int, names=['n', 'abb_r', 'abb_l', 'avl_r', 'avl_l'])
    return data

notebook_path = os.path.abspath("plot.py")
file_path = os.path.join(os.path.dirname(notebook_path), "out.txt")

data = read_file(file_path)
data.sort(axis=0)

fig1 = plt.figure(figsize=[10,7])
ax = fig1.add_subplot()
ax.plot(data['n'], data['abb_r'], 'o-', label="ABB (Random)", lineWidth=1)
ax.plot(data['n'], data['avl_r'], 'o-', label="AVL (Random)", lineWidth=1)
ax.legend()
ax.set(xlabel='Número Procurado', ylabel='Quantidade de Comparações', title="ABB vs. AVL: Entrada Aleatória")
ax.yaxis.set_major_locator(mpl.ticker.MultipleLocator(2))
ax.yaxis.set_minor_locator(mpl.ticker.MultipleLocator(1))
ax.xaxis.set_major_locator(mpl.ticker.MultipleLocator(5000))
ax.xaxis.set_minor_locator(mpl.ticker.MultipleLocator(1000))

fig2 = plt.figure(figsize=[10,7])
ax2 = fig2.add_subplot()
ax2.plot(data['n'], data['abb_r'], 'o-', label="ABB (Random)", lineWidth=1)
ax2.plot(data['n'], data['avl_l'], 'o-', label="AVL (Linear)", lineWidth=1)
ax2.plot(data['n'], data['avl_r'], 'o-', label="AVL (Random)", lineWidth=1)
ax2.legend()
ax2.set(xlabel='Número Procurado', ylabel='Quantidade de Comparações', title="ABB vs. AVL")
ax2.yaxis.set_major_locator(mpl.ticker.MultipleLocator(2))
ax2.yaxis.set_minor_locator(mpl.ticker.MultipleLocator(1))
ax2.xaxis.set_major_locator(mpl.ticker.MultipleLocator(5000))
ax2.xaxis.set_minor_locator(mpl.ticker.MultipleLocator(1000))

fig3 = plt.figure(figsize=[10,7])
ax3 = fig3.add_subplot()
ax3.plot(data['n'], data['abb_l'], 'o-', label="ABB (Linear)", lineWidth=1)
ax3.plot(data['n'], data['avl_l'], 'o-', label="AVL (Linear)", lineWidth=1)
ax3.legend()
ax3.set(xlabel='Número Procurado', ylabel='Quantidade de Comparações', title="ABB vs AVL: Entrada Linear")
ax3.yaxis.set_major_locator(mpl.ticker.MultipleLocator(5000))
ax3.yaxis.set_minor_locator(mpl.ticker.MultipleLocator(1000))
ax3.xaxis.set_major_locator(mpl.ticker.MultipleLocator(5000))
ax3.xaxis.set_minor_locator(mpl.ticker.MultipleLocator(1000))

plt.show()