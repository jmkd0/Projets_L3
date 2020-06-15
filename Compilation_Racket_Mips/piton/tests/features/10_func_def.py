# no args, no return
def a():
    print_int(1)
a()

# single arg, no return
def b(a: int):
    print_int(a)
b(2)

# multiple args, no return
def c(a: int, b: int):
    print_int(a)
    print_int(b)
c(3, 4)

# no args, return
def d() -> int:
    return 4
print_int(d())

# single arg, return
def e(a: int) -> int:
    print_int(5)
    print_int(a)
    return 1
print_int(e(6))

# multiple args, return
def f(a: int, b: int) -> int:
    print_int(7)
    print_int(a)
    print_int(b)
    return 1
print_int(f(8, 9))

# more than 4 args
def fbis(a: int, b: int, c: int, d: int, e: int) -> int:
    return a + b + c + d + e
print_int(fbis(1, 2, 3, 4, 5))

# nested calls
def g(a: int):
    print_int(a)

def h(a: int):
    g(a)
h(10)

# recursivity
def i(a: int):
    print_int(a)
    if a > 0:
        i(a - 1)
i(11)

# nested definitions
def j(a: int) -> int:
    def k(a: int) -> int:
        return a
    print_int(k(a))
j(12)

# recursivity for nested functions
def k():
    def i(a: int):
        print_int(a)
        if a > 0:
            i(a - 1)
    i(11)
k()

# returns
# return without value
def l():
    print_int(13)
    return
    # no typecheck after return
    print_bool("ABC")
l()

# return inside if
def m():
    if (True):
        print_int(14)
        return
    else:
        print_int(15)
    print_int(16)
m()

# return inside while
def n():
    while (True):
        return
        print_int(17)
n()

# no semantics check after return
def o():
    print_int(18)
    return
    a: int = "ABC" + True
o()
