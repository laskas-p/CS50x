import csv
import cs50
from sys import argv, exit


if len(argv) != 2:
    # if not correct display message for correct usage and exit program with code (1)
    print("Usage: python import.py file.csv")
    exit(1)

db = cs50.SQL("sqlite:///students.db")

# open cvs file as described in argv[1]
with open(argv[1]) as csv_file:
    # read from the file with delimiter ','
    csv_reader = csv.DictReader(csv_file, delimiter=',')
    for row in csv_reader:
        # split string with "space" so we can have first, middle and last name
        myname = row["name"].split(" ")
        # if there's not a middle name
        if len(myname) == 2:
            # INSERT with (None,) value for NULL middle name
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       myname[0], (None,), myname[1], row["house"], row["birth"])
            # print(f"Name: {myname[0]}")
            # print(f"Surname: {myname[1]}")
        # If there's a middle name
        if len(myname) == 3:
            db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)",
                       myname[0], myname[1], myname[2], row["house"], row["birth"])
            # print(f"Name: {myname[0]}")
            # print(f"Middle: {myname[1]}")
            #print(f"Last: {myname[2]}")
        # print()
