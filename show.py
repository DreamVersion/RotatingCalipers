from matplotlib import pyplot as plt

random_pts = [(740, 18),
              (677, 719),
              (803, 9),
              (27, 607),
              (520, 154),
              (826, 499),
              (515, 750),
              (422, 748),
              (424, 75),
              (399, 541),
              ]
hull = [(27, 607),
        (424, 75),
        (740, 18),
        (803, 9),
        (826, 499),
        (677, 719),
        (515, 750),
        (422, 748), ]

hull_x = [x[0] for x in hull]
hull_x.append(hull[0][0])
hull_y = [x[1] for x in hull]
hull_y.append(hull[0][1])

obaa = [(591.199, -149.055),
        (1062.39, 202.564),
        (498.187, 958.619),
        (27, 607),
        (591.199, -149.055), ]

obaa_x = [x[0] for x in obaa]
obaa_y = [y[1] for y in obaa]

for pt in random_pts:
    plt.scatter(pt[0], pt[1])
# for pt in obaa:
#     plt.scatter(pt[0], pt[1], marker="*")
# plt.plot(hull_x, hull_y)
plt.plot(obaa_x, obaa_y)
plt.show()
