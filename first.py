def main():
    header()

    task1()
    task2()
    task3()
    task4()
    task5()


def task1():
    description("Посчитать 2+2*2")

    n = 2 + 2 * 2
    print(f'"Результат выражения 2+2*2 = {n}"')


def task2():
    description("Разница между присваиванием в int и в double")

    a = int(3)
    b = int(3.14)
    af = float(3)
    bf = float(3.14)

    print(a, b, af, bf, sep="\n")


def task3():
    description("Операции над числами")

    a = int(input("a: "))
    b = int(input("b: "))

    for oper in ["+", "-", "*", "/"]:
        eval(f'print("a{oper}b =", a{oper}b)')


def task4():
    description("Свап переменных с темпом и без")

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


def task5():
    description("Падение объекта")

    g = 9.8
    x0, v0, t = map(float, input("x0 v0 t: ").split(" "))
    res = x0 + v0 * t + (g * t ** 2) / 2
    print(f"res: {res}")


def header():
    print("Nikonov Fedor, PI-201(2)")


_description_counter = 0


def description(message):
    global _description_counter
    _description_counter += 1
    print(f"\nЗадача №{_description_counter} {message}")


main()
