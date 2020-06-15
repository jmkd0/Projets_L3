# basics
if True:
    print_int(1)
else:
    print_int(2)
print_int(3) # trailing line post-dedent


# 2-level
if True:
    print_int(4)
    if False:
        print_int(5)
    else:
        print_int(6)
    print_int(7)
else:
    print_int(8)
    if True:
        print_int(9)
    else:
        print_int(10)
    print_int(11)
print_int(12)

# 2-level dedent
if True:
    print_int(13)
    if True:
        print_int(14)

# empty lines
if True:
    
    print_int(4)
    if False:
        print_int(5)
        
    else:
        print_int(6)
        
    
    print_int(7)
else:
    print_int(8)
    
    
    if True:
        print_int(9)
    else:
        
        print_int(10)
    print_int(11)
    
    
print_int(12)

# empty lines with wrong indent TODO no supported
#if True:
#  
#    print_int(4)
#    if False:
#        print_int(5)
#
#    else:
#        print_int(6)
#              
#   
#    print_int(7)
# 
#print_int(12)



# coherent mix of tabs and spaces with varied width
if True:
	print_int(4)
	if False:
	    print_int(5)
	else:
	    print_int(6)
	print_int(7)
else:
  print_int(8)
  if True:
  	print_int(9)
  else:
  	print_int(10)
  print_int(11)
print_int(12)


# no trailing eof after dedent
if True:
    print_int(4)