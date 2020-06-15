# operator precedence

print_int(3 + 2 * 5)
print_int(3 - 2 * 5)
print_int(3 * 2 + 5)
print_int(3 * 2 - 5)

print_bool(not True or False)
print_bool(not True and False or True)

# TODO: auto convert int division to float
#print_int(3 + 2 / 5)
#print_int(3 - 2 / 5)
#print_int(3 / 2 + 5)
#print_int(3 / 2 - 5)
print_bool(-6 + 2 * 3 == 4 - 4)
print_bool(-6 + 2 * 3 != 4 - 4)
print_bool(-6 + 2 * 3 > 4 - 4)
print_bool(-6 + 2 * 3 < 4 - 4)
print_bool(-6 + 2 * 3 >= 4 - 4)
print_bool(-6 + 2 * 3 <= 4 - 4)

# parenthised operations
print_int((3 + 2) * 5)
