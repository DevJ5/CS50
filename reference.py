from sys import argv

print(argv[1])
print("Enter a number: ")
x = int(input())
print("Enter a number: ")
y = int(input())
print(f"x + y = {x + y}")

print(f"x / y = {x / y:.2f}")
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
    print("cough ", end="")  # To negate the newline character, default is end="\n"
    if not False:  # Using the not keyword
        a = "   *okay*   "
    print(a.upper().strip())  # Strip is like trim, removes whitespace.


# Can just iterate over a string or a list for that matter.
for i in "abc":
    cough()


def getNames():
    print("Enter a name: ")
    student = {"name": input()}
    student["age"] = input()
    print(f"Name = {student['name']}, age = {student['age']}")


getNames()

# file = open("somefile.txt", r)
# for line in file:
#   words.add(line.rstrip("\n"))

# This approach apparantly solves problems:
# if __name__ == "__main__":
#    main()
