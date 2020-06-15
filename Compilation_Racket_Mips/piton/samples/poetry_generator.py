#str_len = len
#print_str = print

def has_space(text: str) -> bool:
    length: int = str_len(text)
    i: int = 0
    while i < length:
        if text[i] == " ":
            return True
        i = i + 1
    return False

def is_vowel(letter: str) -> bool:
    if letter == "a":
        return True
    if letter == "e":
        return True
    if letter == "i":
        return True
    if letter == "i":
        return True
    if letter == "u":
        return True
    if letter == "y":
        return True
    return False

def is_single_digit(text: str) -> bool:
    if text == "0":
        return True
    if text == "1":
        return True
    if text == "2":
        return True
    if text == "3":
        return True
    if text == "4":
        return True
    if text == "5":
        return True
    if text == "6":
        return True
    if text == "7":
        return True
    if text == "8":
        return True
    if text == "9":
        return True
    return False

def letter_to_digit(letter: str) -> int:
    if letter == "0":
        return 0
    if letter == "1":
        return 1
    if letter == "2":
        return 2
    if letter == "3":
        return 3
    if letter == "4":
        return 4
    if letter == "5":
        return 5
    if letter == "6":
        return 6
    if letter == "7":
        return 7
    if letter == "8":
        return 8
    if letter == "9":
        return 9

def get_prefix(word: str, n: int) -> str:
    length: int = str_len(word)
    # safety checks
    if n < 0:
        n = 0
    if n > length:
        n = length
    
    count: int = 0
    prefix: str = ""
    while count < n:
        prefix = prefix + word[count]
        count = count + 1
    return prefix

def get_suffix(word: str, n: int) -> str:
    length: int = str_len(word)
    # safety checks
    if n < 0:
        n = 0
    if n > length:
        n = length
    
    suffix: str = ""
    count: int = 0
    while count < n:
        suffix = suffix + word[length - n + count]
        count = count + 1
    return suffix

def replace_suffix(word: str, old_suffix_length: int, new_suffix: str) -> str:
    return get_prefix(word, str_len(word) - old_suffix_length) + new_suffix

def generate_poetry():
    def seems_singular(word: str) -> bool:
        suffix: str = get_suffix(word, 3)
        if suffix == "ius":
            return True
        
        suffix = get_suffix(word, 1)
        return suffix != "s"
    
    def singularize(plural: str) -> str:
        ## some incomplete special rules:
        # children -> child
        if plural == "children":
            return "child"
        
        # {atoes} -> {ato} (potato)
        suffix: str = get_suffix(plural, 5)
        if suffix == "atoes":
            return replace_suffix(plural, 5, "ato")
        
        # {ives} -> {ife} (life, wife)
        suffix = get_suffix(plural, 4)
        if suffix == "ives":
            return replace_suffix(plural, 4, "ife")
        
        # {men} -> {man} (man, woman)
        suffix = get_suffix(plural, 3)
        if suffix == "men":
            return replace_suffix(plural, 3, "man")
        
        ## general rules
        # penn{ies} -> penn{y} (consonant + ies -> y)
        suffix = get_suffix(plural, 4)
        if not is_vowel(suffix[0]) and get_suffix(suffix, 3) == "ies": 
            return replace_suffix(plural, 3, "y")
        
        # rad{i} -> rad{ius}
        suffix = get_suffix(plural, 1)
        if suffix == "i":
            return replace_suffix(plural, 1, "ius")
        
        # pit{ches} -> pit{ch}
        # wi{shes} -> wi{sh}
        suffix = get_suffix(plural, 4)
        if suffix == "ches":
            return replace_suffix(plural, 4, "ch")
        if suffix == "shes":
            return replace_suffix(plural, 4, "sh")
        
        # bo{xes} -> bo{x}
        suffix = get_suffix(plural, 3)
        if suffix == "xes":
            return replace_suffix(plural, 3, "x")
        
        ## very general rule, wrong with singulars ending with s
        if not seems_singular(plural):
            return replace_suffix(plural, 1, "")
        else:
            return plural
    
    topic: str = input("what do you want your poetry to be about? > ")
    while str_len(topic) == 0 or has_space(topic):
        if str_len(topic) == 0:
            topic = input("please enter a subject > ")
        else:
            topic = input("please enter a simpler subject > ")
        
    how_much: str = input("one a scale of 1 to 9, how poetic do you want to be? > ")
    while not is_single_digit(how_much) or how_much == "0":
        how_much = input("please enter a digit between 1 and 9 > ")
    
    topic = singularize(topic)
    
    if is_vowel(get_prefix(topic, 1)):
        determiner: str = "an" # NB: variable declaration in if/else
    else:
        determiner: str = "a"
    
    def poetize(topic: str, degree: int) -> str:
        def add_more_poetry(poetry: str, topic: str, degree: int) -> str:
            if not degree:
                # poetry degree zero
                return determiner + " " + topic + " is " + determiner + " " + topic # NB: determiner is a free variable
            else:
                return add_more_poetry(poetry, topic, degree - 1) + " is " + determiner + " " + topic # NB: unindenting several levels in one eol
        
        return add_more_poetry("", topic, degree)
    
    poetry: str = poetize(topic, letter_to_digit(how_much))
    print_str(poetry)

generate_poetry()
