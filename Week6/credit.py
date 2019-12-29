def main():
    # Ask user to input a CC number
    ccNumber = getInputFromUser()
    # Validate if it has the number of digits in a CC number
    if not isValidAmountOfDigits(ccNumber):
        print("INVALID")
    # Validate if the checksum according to Luhn is correct
    if not isValidChecksum(ccNumber):
        print("INVALID")
    # Get the number of digits in the CC number
    numberOfDigits = getNumberOfDigits(ccNumber)
    # Get the type of the CC card and print it out
    typeOfCard = getTypeOfCard(ccNumber, numberOfDigits)
    print(typeOfCard)


def getInputFromUser():
    while True:
        try:
            return int(input("Number: "))
        except Exception as e:
            pass


def isValidAmountOfDigits(ccNumber):
    return ccNumber >= 10 ** 13 and ccNumber < 10 ** 17


def isValidChecksum(ccNumber):
    # Example CC: 4003600000000014
    sum = 0
    # Every other digit starting from the second to last digit gets multiplied by two
    isMultiplyByTwo = False
    while True:
        lastDigit = ccNumber % 10
        if isMultiplyByTwo:
            product = lastDigit * 2
            if product < 10:
                sum += product
            else:
                sum += product % 10
                sum += product // 10
        else:
            sum += lastDigit
        # Remove the last digit
        ccNumber = ccNumber // 10
        # If there are no digits left, break out of the while loop
        if ccNumber == 0:
            break
        # Flip the switch
        isMultiplyByTwo = not isMultiplyByTwo

    # Return true if the last digit is a 0
    print(sum)
    return sum % 10 == 0


def getNumberOfDigits(ccNumber):
    totalNumberOfDigits = 0
    while ccNumber / 10 != 0:
        ccNumber //= 10
        totalNumberOfDigits += 1

    return totalNumberOfDigits


def getTypeOfCard(ccNumber, numberOfDigits):
    firstDigit = int(str(ccNumber)[:1])
    firstTwoDigits = int(str(ccNumber)[:2])
    cards = ("AMEX", "MASTERCARD", "VISA")
    masterCardRange = {51, 52, 53, 54, 55}

    # Check for American Express
    if numberOfDigits == 15 and (firstTwoDigits == 34 or firstTwoDigits == 37):
        return cards[0]
    # Check for Mastercard
    elif numberOfDigits == 16 and firstTwoDigits in masterCardRange:
        return cards[1]
    # Check for Visa
    elif (numberOfDigits == 13 or numberOfDigits == 16) and firstDigit == 4:
        return cards[2]
    else:
        return "INVALID"


if __name__ == "__main__":
    main()
