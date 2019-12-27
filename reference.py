print("Enter a number: ")
x = int(input())
print("Enter a number: ")
y = int(input())
print(f"x + y = {x + y}")

print(f"x / y = {x / y:.2f}")  # For flooring division.
print(f"x // y = {x // y}")  # For flooring division.

print("Enter y or n: ")
answer = input()
if answer == "y" or answer == "Y":
    print("You answered yes.")
elif answer == "n" or answer == "N":
    print("You answered no.")
else:
    print("That wasn't an answer")


def cough():
    print("cough ", end="")
    if True:
        a = "*okay*"
    print(a)


for i in range(3):
    cough()

# This approach apparantly solves problems:
# if __name__ == "__main__":
#    main()
