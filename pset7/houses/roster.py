# TODO
from sys import argv, exit
import sqlite3

# Checking the right number of command line arguments
if len(argv) != 2:
    print("Enter a valid number of command line arguments")
    exit(1)


connect = sqlite3.connect("students.db")
curs = connect.cursor()

curs.execute(f"SELECT first, middle, last, birth FROM students WHERE house = '{argv[1]}' ORDER BY last, first")
student_tuple = curs.fetchall()
student_list = []
for student in student_tuple:
    student_list.append([student_item for student_item in student])
# print(student_list)
for student in student_list:
    if student[1] == None:
        print(f"{student[0]} {student[2]}, born {student[3]}")
    else:
        print(f"{student[0]} {student[1]} {student[2]}, born {student[3]}")
connect.commit()
connect.close()