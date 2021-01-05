import sys
import csv
arg = sys.argv
if (len(arg) != 3):
    print("Usage: python dna.py data.csv sequence.txt")  # Checks for bad syntax
    exit(1)
with open(arg[1], "r") as f:
    lst = [dict(x) for x in csv.DictReader(f)]  # Converts csv to list of dictionaries 

with open(arg[2], "r") as f:
    dna = list(f.read())  # Converts String in list
dct = {}
for x in lst[0].keys():
    var2 = 0
    for y in range(len(dna)):
        var1 = 0
        # print(dna[y:y + len(x)]) #Debug
        if x == ''.join(dna[y:y + len(x)]):  # Checks if squence starts
            for z in range(y, len(dna), len(x)):  # Counts Sequence repeat in tandum
                if x != ''.join(dna[z:z + len(x)]):   # When Sequence stops
                    break
                var1 += 1
            if var1 > var2:
                var2 = var1
    dct[x] = var2
f = 0
for x in lst:
    var1 = 0
    for y in list(x.keys())[1:len(x)]:
        # print(x[y],dct[y],int(x[y]) == int(dct[y])) #Debug
        if int(x[y]) == int(dct[y]):
            # print(var1) #Debug
            var1 += 1
    # print("a",var1) #Debug
    if var1 == len(list(x.keys())[1:len(x)]):
        f = 1
        print(x['name'])  # Gives the Criminal (Maybe?)
if f == 0:
    print("No match")  # No Match