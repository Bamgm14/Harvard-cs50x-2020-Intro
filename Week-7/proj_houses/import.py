# TODO
import pandas as pd
import sqlite3 as sql
import sys
args = sys.argv
if len(args) != 2:
    print("Usage: python import.py [csv file]")
    exit(1)
table = pd.read_csv(args[1])  # Pandas makes life easier
conn = sql.connect("students.db")  # Connect to DB Server
cur = conn.cursor()
for x in table.iterrows():
    name = x[1][0].split(' ')
    if len(name) == 2:  # Getting special cases of 2 Word Names
        last = name[1]
        middle = None
    else:
        last = name[2]
        middle = name[1]
    first = name[0]
    cur.execute("insert into students (first,middle,last,house,birth) values (?,?,?,?,?);",
                (first, middle, last, x[1][1], int(x[1][2])))
conn.commit()  # Must Commit.. To Save
conn.close()  # Good Practice