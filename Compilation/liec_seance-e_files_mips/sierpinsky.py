x = 1
while x < 2147483648: # = 2**31
    n = x
    while n > 0:
        if n & 1:
            print('#',end='') # end='' empêche l'ajout auto du \n
        else:
            print(' ',end='')
        n >>= 1
    print('')
    x ^= x << 1
