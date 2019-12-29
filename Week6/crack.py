import sys
import crypt
import string
import time


def main(argv):
    # Validate if the program is run with the correct arguments
    if len(argv) != 2:
        print("Usage: python crack.py hash")
        return False

    # Get a DES-based hash from the user (hash is 13 characters long, of which the first 2 characters are salt)
    hash = argv[1]

    # Crack the hash
    start = time.time()
    password = crackHash(hash)
    end = time.time()
    print("Time elapsed: %s" % str(end - start))
    print(password)


def crackHash(hash):
    salt = hash[0:2]
    # Bruteforce, max 5 characters long
    alphabet = string.ascii_lowercase + string.ascii_uppercase
    print(alphabet)
    for letter1 in alphabet:
        password = letter1
        if hash == hashPassword(password, salt):
            return password
        for letter2 in alphabet:
            password = letter1 + letter2
            if hash == hashPassword(password, salt):
                return password
            for letter3 in alphabet:
                password = letter1 + letter2 + letter3
                if hash == hashPassword(password, salt):
                    return password
                for letter4 in alphabet:
                    password = letter1 + letter2 + letter3 + letter4
                    if hash == hashPassword(password, salt):
                        return password
                    for letter5 in alphabet:
                        password = letter1 + letter2 + letter3 + letter4 + letter5
                        if hash == hashPassword(password, salt):
                            return password


def hashPassword(password, salt):
    return crypt.crypt(password, salt)


if __name__ == "__main__":
    main(sys.argv)
