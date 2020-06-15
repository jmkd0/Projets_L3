# type declaration and literals
b: bool = True
print_bool(b)
print_bool(True)
print_bool(False)

# arithmetics
print_int(False + True)
print_int(False - True)
print_int(False * True)
# TODO: auto convert integer division to float
#print_int(False / True)

# and/or/not
print_bool(False and False)
print_bool(False and True)
print_bool(False or False)
print_bool(False or True)
print_bool(not False)
#print_bool(not True)

# eq/neq
print_bool(False == False)
print_bool(False == True)
print_bool(False != False)
print_bool(False != True)

# lt/gt
print_bool(False > False)
print_bool(False > True)
print_bool(True > False)
print_bool(False < False)
print_bool(False < True)
print_bool(True < False)

# lte/gte
print_bool(False >= False)
print_bool(False >= True)
print_bool(True >= False)
print_bool(False <= False)
print_bool(False <= True)
print_bool(True <= False)
