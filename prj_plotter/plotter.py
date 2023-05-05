import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

from prj_quadtree import Quadtree

def prj(ax, x, y, box, vmin, vmax, log=True, capacity=64, max_level=10, cmap=plt.cm.magma):

    t = Quadtree(box[0],box[1],box[2],box[3],capacity,max_level)

    t.insert_many(x,y)

    ps = t.plot_density()
    values = [p.value for p in ps]
    for p in ps:
        if log:
            v = np.clip(p.value, 10**vmin, 10**vmax)
            v = np.log10(v)
        else:
            v = np.clip(p.value, vmin, vmax)
            v = p.value
        v = (v - vmin) / (vmax - vmin)
        patch = mpl.patches.Rectangle((p.x,p.y), p.width, p.height, fc=cmap(v), ec=cmap(v))
        ax.add_patch(patch)