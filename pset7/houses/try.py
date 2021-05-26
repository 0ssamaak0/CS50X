# TODO
import csv
from cs50 import SQL
from sys import argv, exit

curs = SQL("sqlite:///students.db")

if len(argv) != 2:
    print("Enter a valid number of command line arguments")
    exit(1)



# Opening the csv file & creating the container list
students = open(argv[1], "r")
students_dict = csv.DictReader(students)
student_list = []


# Getting the values of the names each in its place, moving data to student_list
for student in students_dict:
    full_names = student["name"].split(" ")
    student["first"] = full_names[0]
    if len(full_names) == 2:
        student["middle"] = ""
        student["last"] = full_names[1]
    elif len(full_names) == 3:
        student["middle"] = full_names[1]
        student["last"] = full_names[2]
    else:
        print("NO MORE THAN 3 NAMES! THE PROGRAM HAS BEEN CRASHED")
        exit(1)
    
    student.pop("name")
    first = student["first"]
    middle = student["middle"]
    last = student["last"]
    house = student["house"]
    birth = student["birth"]
    # print(f"{first} {middle} {birth}")
    # order_list = ["first", "middle", "last", "house", "birth"]
    # student = tuple(student[x] for x in order_list)
    # student_list.append(student)
    curs.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?, ?, ?, ?, ?)", first, middle, last, house, birth)
    curs.execute("UPDATE students SET middle = NULL WHERE middle ='' ")
# print(student_list)

# connecting python with the db  & starting inserting data

# curs.execute("CREATE TABLE students (first TEXT, middle TEXT, last TEXT, house TEXT, birth INTEGER)")