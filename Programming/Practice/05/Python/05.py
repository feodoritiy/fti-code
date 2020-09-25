g = 9.8
x0, v0, t = map(float, input("x0 v0 t: ").split(" "))
res = x0 + v0 * t + (g * t ** 2) / 2
print(f"res: {res}")
