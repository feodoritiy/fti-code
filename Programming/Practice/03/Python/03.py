a = int(input("a: "))
b = int(input("b: "))

for oper in ["+", "-", "*", "/"]:
    eval(f'print("a{oper}b =", a{oper}b)')
