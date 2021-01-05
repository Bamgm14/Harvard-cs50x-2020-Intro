# TODO
import sqlite3 as sql
import sys
if len(sys.argv) != 2:
    print("Usage: python roster.py [house]")  # Make sure for correct syntax
    exit(1)
conn = sql.connect("students.db")  # COnnects to SQL Server
cur = conn.cursor()   # Gets Cursor
cur.execute("select first, middle, last, birth from students where house = ? order by last, first",
            (sys.argv[1],))  # SQL Command to retrieve rows
for x in cur.fetchall():
    # print("{0} {1} {2}, born {3}".format(x[0],x[1] or "\b",x[2],x[3])) #Thanks Check50, very cool
    if x[1]:
        print("{0} {1} {2}, born {3}".format(x[0], x[1], x[2], x[3]))  # Looking for checks
    else:
        print("{0} {2}, born {3}".format(x[0], x[1], x[2], x[3]))  # Looking for checks
conn.close()  # Good Practice