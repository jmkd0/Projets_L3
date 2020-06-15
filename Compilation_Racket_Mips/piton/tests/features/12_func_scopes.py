def i1() -> int:
    print_int(1)
    return 1
def s1() -> str:
    print_str("1")
    return "1"

# call func in enclosing scope
def a():
    i1()
    s1()
a()

# call func returning val in enclosing scope
def b():
    i: int = i1()
    s: str = s1()
    print_int(i)
    print_str(s)
b()

def c():
    def i2() -> int:
        print_int(2)
        return 1
    def s2() -> str:
        print_str("2")
        return "2"
    # call func in enclosing scope, deeper
    def a():
        i2()
        s2()
    a()
    
    # call func var in enclosing scope, deeper
    def b():
        i: int = i2()
        s: str = s2()
        print_int(i)
        print_str(s)
    b()
c()

def i3() -> int:
    print_int(3)
    return 3
def s3() -> str:
    print_str("3")
    return "3"

# call func in nested enclosing scope
def d():
    def e():
        i3()
        s3()
    e()
d()

# call func returning var in nested enclosing scope
def f():
    def g():
        i: int = i3()
        s: str = s3()
        print_int(i)
        print_str(s)
    g()
f()


# call outer scope functions with outer scope vars, from 
# read var in enclosing scope
def g():
    i: int = i1()
    s: str = s1()
    print_int(i)
    print_str(s)

def i():
    def j():
        g()
    j()
i()
