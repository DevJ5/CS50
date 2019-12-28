def main():
    # Ask user to input a CC number
    ccNumber = getInputFromUser()


def getInputFromUser():
    while True:
        try:
            return int(input("Number: "))
        except Exception as e:
            pass


def isValidChecksum(ccNumber):
    # 4003600000000014
    # 1234 -> 123 % 10 = 3 -> 2 * 3 -> 12
    # 1 ->
    # 12345
    sum = 0
    while True:
        ccNumber = ccNumber // 10
        temp = (ccNumber % 10) * 2

        if temp < 10:
            sum += temp
        else:
            sum += temp % 10
            sum += temp // 10
        ccNumber = ccNumber // 10
        if ccNumber == 0:
            break


if __name__ == "__main__":
    main()
