"""
MIT License
Copyright (c) Bill Chen 2023
All rights reserved.
"""

import pytest

from prj_quadtree import Quadtree


@pytest.mark.parametrize(
    "idx", "expect", [
    (0, 64),
    (1, 0),
    (7, 4),
    (9, 0),
    ])
def test_partTypeNum(idx, expect):
    x = np.array([0.1,0.2,0.6])
    y = np.array([0.1,0.2,0.1])

    t = Quadtree(0,0,1,1,1,10)

    t.insert_many(x,y)

    ps = t.plot_density()

    assert int(ps[idx].value) == expect