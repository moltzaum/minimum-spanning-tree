#!/usr/bin/env python

import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
G.add_edges_from([
    (3, 5),
    (2, 4),
    (1, 3),
    (5, 6),
    (4, 5),
])

G100 = nx.Graph()
G100.add_edges_from([
    (84, 88),
    (80, 81),
    (64, 65),
    (54, 71),
    (53, 82),
    (39, 91),
    (33, 79),
    (31, 68),
    (30, 91),
    (28, 40),
    (22, 49),
    (22, 24),
    (20, 61),
    (16, 67),
    (15, 90),
    (15, 57),
    (12, 87),
    (10, 56),
    (9, 90),
    (87, 94),
    (81, 86),
    (69, 72),
    (62, 74),
    (49, 74),
    (47, 85),
    (38, 40),
    (36, 46),
    (30, 60),
    (26, 71),
    (21, 78),
    (19, 85),
    (9, 43),
    (2, 49),
    (62, 76),
    (57, 67),
    (52, 81),
    (51, 89),
    (51, 55),
    (48, 97),
    (45, 98),
    (38, 85),
    (38, 68),
    (36, 73),
    (32, 67),
    (27, 66),
    (22, 82),
    (19, 84),
    (6, 33),
    (3, 63),
    (93, 98),
    (74, 89),
    (63, 73),
    (61, 70),
    (58, 98),
    (58, 94),
    (49, 56),
    (43, 70),
    (41, 84),
    (39, 73),
    (26, 68),
    (25, 66),
    (20, 64),
    (19, 44),
    (17, 75),
    (16, 52),
    (15, 84),
    (11, 94),
    (10, 64),
    (6, 82),
    (6, 45),
    (83, 89),
    (71, 99),
    (27, 44),
    (15, 29),
    (10, 21),
    (5, 53),
    (4, 61),
    (3, 16),
    (1, 89),
    (84, 96),
    (71, 72),
    (51, 97),
    (50, 88),
    (42, 50),
    (35, 66),
    (14, 46),
    (13, 47),
    (58, 92),
    (17, 78),
    (66, 77),
    (26, 34),
    (59, 98),
    (18, 66),
    (7, 100),
    (7, 65),
    (81, 95),
    (37, 86),
    (23, 87),
    (8, 45),
])

plt.figure()
nx.draw_networkx(G100, node_size = 100, font_size = 6)
plt.show()

