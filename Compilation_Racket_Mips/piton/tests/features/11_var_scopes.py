i1: int = 1
s1: str = "1"
# read var in enclosing scope
def a():
    print_int(i1)
    print_str(s1)
a()

# assign var in enclosing scope
# not compatible with python
#def b():
#    i1 = 2
#    s1 = "2"
#b()
#print_int(i1)
#print_str(s1)

def c():
    i1: int = 3
    s1: str = "3"
    # read var in enclosing scope, deeper
    def a():
        print_int(i1)
        print_str(s1)
    a()
    
    # assign var in enclosing scope, deeper
    # not compatible with python
    #def b():
    #    i1: int = 4
    #    s1: str = "4"
    #b()
    #print_int(i1)
    #print_str(s1)
c()

i2: int = 5
s2: str = "5"
# read var in nested enclosing scope
def d():
    def e():
        print_int(i2)
        print_str(s2)
    e()
d()

# assign var in nested enclosing scope
# not compatible with python
#def f():
#    def g():
#        i2: int = 6
#        s2: str = "6"
#    g()
#f()
#print_int(i2)
#print_str(s2)


# call outer scope functions with outer scope vars, from 
# read var in enclosing scope
def g():
    print_int(i1)
    print_str(s1)

# assign var in enclosing scope
# not compatible with python
#def h():
#    i1: int = 2
#    s1: str = "2"

def i():
    def j():
        g()
    j()
i()
print_int(i1)
print_str(s1)
