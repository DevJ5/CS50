from sys import argv

print(argv[0])
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

# Files:
# file = open("somefile.txt", r)
# for line in file:
#   words.add(line.rstrip("\n"))

# List of tuples:
presidents = [
    ("George Washington", 1789),
    ("John Adams", 1797),
    ("Thomas Jefferson", 1801),
    ("James Madison", 1809),
]

for president, year in presidents:
    print(f"{president} ({year})")

# This approach apparantly solves problems:
# if __name__ == "__main__":
#    main()

# -- Creating a Virtual Environment -- #
# python -m venv project_env
# . activate
# pip list
# deactivate (there is a new shell command created when we activated the environment)

with open("registered.csv", "r") as file:
    reader = csv.reader(file)
    students = list(reader)
return render_template("registered.html", students=students)

jsonify(words)  # from flask library
