# bool conversion
if "":
    print_int(3)

# type declaration and literal
s: str = "ABC 123"
print_str(s)
# escape special chars
print_str("\"\t\n")
# TODO backslash escaping
#print_str("\\\\")
# TODO single quote, multiline

# eq/neq
print_bool("ABC" == "ABC")
print_bool("ABC" == "123")
print_bool("ABC" == "")
print_bool("" == "ABC")
print_bool("" == "")
print_bool("ABC" != "ABC")
print_bool("ABC" != "123")
print_bool("ABC" != "")
print_bool("" != "ABC")
print_bool("" != "")

# not
print_bool(not "")
print_bool(not "ABC")


# length
print_int(str_len("ABC 123"))
print_int(str_len(""))
# concatenation
print_str("ABC" + "123")
print_str("" + "ABC")
print_str("" + "")
print_str("ABC" + " " + "123")
# subscript access
print_str(s[0])
print_str(s[2])
print_str("ABC"[0])
print_str("ABC"[2])
# automatic type conversion
print_str(s[True])
print_str(s[False])
# nested subscript access
print_str("ABC"[0][0])

# TODO subscript assign

# input
#name: str = input("enter your name: ")
#print_str("hi " + name + "!\n")
