import cs50
from sys import argv, exit


if len(argv) != 2:
    # if not correct display message for correct usage and exit program with code (1)
    print("Usage: python roster.py house")
    exit(1)

# call database as SQL function
db = cs50.SQL("sqlite:///students.db")


# SELECT from the table where house = command line argument
myline = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last, first", argv[1])

# print values per row[key] per line
for row in myline:
    # if there's a middle name
    if row["middle"] == None:
        print(row["first"] + " " + row["last"] + ", born " + str(row["birth"]))
    else:
        print(row["first"] + " " + row["middle"] + " " + row["last"] + ", born " + str(row["birth"]))
