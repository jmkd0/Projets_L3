# declare and assign literal
a: int = 1
print_int(a)
# reassign
a = 2
print_int(a)
# declare/assign variable
b: int = a
print_int(b)
# declare/assign expression
c: int =  3 + 4
print_int(c)
# declare/assign nested expressions
d: int =  ((5 + 6) * 7)
print_int(d)

# declare inside if
if True:
    e: int = 8
    print_int(e)

# declare in else
if False:
    print_int(9)
else:
    f: int = 10
    print_int(f)

# declare same variable inside if and else
if True:
    g: int = 11
    print_int(g)
else:
    g: int = 12
    print_int(g)

if False:
    h: int = 13
    print_int(h)
else:
    h: int = 14
    print_int(h)

# declare inside while
i: int = 0
while i < 5:
    j: int = i
    print_int(j)
    i = i + 1
