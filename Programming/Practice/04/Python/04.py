a = input("a: ")
b = input("b: ")

print(a, b)
temp = a
a = b
b = temp
print(a, b)

print(a, b)
a, b = b, a
print(a, b)