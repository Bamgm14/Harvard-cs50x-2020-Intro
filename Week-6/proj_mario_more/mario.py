height = 0
while (height > 8 or height <= 0):
    try:
        height = int(input("Height: "))
    except:
        pass
    # Looking for valid input
for x in range(height):
    print(" "*(height - 1 - x) + "#"*(x + 1) + "  " + "#"*(x + 1))  # MARIO But twice
