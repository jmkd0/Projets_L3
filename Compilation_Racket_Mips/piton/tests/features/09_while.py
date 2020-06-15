# while
i: int = 0
while i < 5:
    print_int(i)
    i = i + 1

# while False
while False:
    print_int(5)

# inline while
i = 6
while i < 9: i = i + 1
print_int(i)

# auto bool conversion
i = 1
while i:
    print_int(15)
    i = i - 1
