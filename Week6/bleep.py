from cs50 import get_string
from sys import argv, exit

# TODO
# This text file contains lowercase words, 1 per line terminated with a newline character
# Read from this file into a list structure
# Prompt the user for a message
# Split the string and iterate over each word to see if it is in the banned list
# If the word is in the banned list replace it with all *'s
# Print the word back to the user


def main():
    # Check if the command is run with the correct number of arguments
    if len(argv) != 2:
        print("Usage: python bleep.py dictionary")
        exit(1)
    # Open the file for reading
    try:
        file = open(argv[1], "r")
        bannedWordsList = {}
        for line in file:
            bannedWordsList[line.rstrip()] = True
    except Exception as e:
        exit(1)

    print(bannedWordsList)
    # Ask the user to input a message they would like to censor
    message = input("What message would you like to censor?")
    wordsInMessageList = message.split(" ")
    censoredMessage = ""

    for word in wordsInMessageList:
        # If the word is in the banned words list, censor and append it
        if word.lower() in bannedWordsList:
            stars = len(word) * "*"
            censoredMessage += stars
        # Else just append to word
        else:
            censoredMessage += word
        # Add a space to the end of every word
        censoredMessage += " "
    # Remove the last space and print the censored message to standard output
    print(censoredMessage.rstrip())


if __name__ == "__main__":
    main()
