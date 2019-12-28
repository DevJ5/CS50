def main():
    # Ask user to input a CC number
    ccNumber = getInputFromUser()
    if not isValidAmountOfDigits(ccNumber):
        print("INVALID")
    if isValidChecksum(ccNumber):
        print("nice")


def getInputFromUser():
    while True:
        try:
            return int(input("Number: "))
        except Exception as e:
            pass


def isValidAmountOfDigits(ccNumber):
    return ccNumber >= 10 ** 13 and ccNumber < 10 ** 17


def isValidChecksum(ccNumber):
    # 4003600000000014
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


if __name__ == "__main__":
    main()
