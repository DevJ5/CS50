def main():
    while True:
        height = input("Height: ")
        if height.isdigit():
            height = int(height)
            if height >= 1 and height <= 8:
                break

    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i, end="")
        print("  ", end="")
        print("#" * i)


if __name__ == "__main__":
    main()
