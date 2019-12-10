def calc_moy (notes):
    moy = 0
    n = 0
    while notes != []:
        note = notes[0] # (define note (car notes)) en Racket
        moy += note
        n += 1
        notes = notes[1:] # (set! notes (cdr notes)) en Racket
    moy //= n
    return moy

print("Entrez vos notes, en finissant par -1 :")
notes = []
n = 1
while True:
    note = int(input("Note %d : " % n))
    if note == -1:
        break
    notes.append(note) # (set! notes (cons note notes)) en Racket
    n += 1
print("Votre moyenne est %d" % calc_moy(notes))
