prng_state = 42

def prng (sup):
    global prng_state
    prng_state = (prng_state * 1664525 + 1013904223) % 2**32
    retur
    n prng_state % sup

def jeu (max):
    print('Le nombre est entre 0 et ' + str(max))
    n = prng(max)
    guess = -1
    while guess != n:
        guess = int(input('Entrez un nombre: '))
        if guess > n:
            print("Trop grand.")
        elif guess < n:
            print("Trop petit.")
    print("Bravo :).")

jeu(300)
