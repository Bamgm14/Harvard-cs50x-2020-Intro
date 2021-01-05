money = -1
while (money < 0):
    try:
        money = float(input("Change owed: "))
        money *= 100  # Puts Money as divisible by hundred 
    except:
        pass
    # Gets Valid Input
coins = 0
for x in [25, 10, 5, 1]:
    coins += money // x  # Counting Part
    money = money % x
print(int(coins))
