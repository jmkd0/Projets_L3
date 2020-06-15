# call with variable arg
a: int = 1
print_int(a)
# call with literal arg
print_int(1)
# call with expression arg
print_int(2 + 0)
# call with nested expressions arg
print_int(((2 + 0) * 2))
# call with call in arg
print_int(str_len("ABC"))

# TODO call with multiple args
