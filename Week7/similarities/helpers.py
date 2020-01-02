from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    aList = a.split("\n")
    bList = b.split("\n")
    intersection = [value for value in aList if value in bList]
    return intersection


def sentences(a, b):
    """Return sentences in both a and b"""
    sentencesListA = sent_tokenize(a, language="english")
    sentencesListB = sent_tokenize(b, language="english")
    # intersection = list(set(sentencesListA) & set(sentencesListB))
    intersection = [value for value in sentencesListA if value in sentencesListB]
    return set(intersection)


def substringTokenize(str, n):
    substringList = []
    length = len(str)
    for i in range(length - n + 1):
        substringList.append(str[i : i + n])
    return substringList


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""
    substringListA = substringTokenize(a, n)
    substringListB = substringTokenize(b, n)

    return set(substringListA) & set(substringListB)
