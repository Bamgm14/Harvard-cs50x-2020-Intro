def luhr(card):  # Luhr Algo
    number = 0
    l = len(card)
    oddoreven = l % 2
    if l < 13:
        return False
    for x in range(l):
        var = int(card[x])
        if x % 2 == oddoreven:
            var *= 2
            if var > 9:
                var -= 9
        number += var
    return number % 10 == 0
    
        
card = -1
while (card < 0):
    try:
        card = int(input("Number: "))
    except:
        pass
card = str(card)
f = 0
if (luhr(card)):
    if int(card[0:2]) in [51, 52, 53, 54, 55]:  # List of Mastercard numbers
        print("MASTERCARD")
        f = 1
    if int(card[0:2]) in [34, 37]:  # List of American Express number
        print("AMEX")
        f = 1
    if int(card[0]) == 4:  # Visa is just visa
        print("VISA")
        f = 1
if f == 0:
    print("INVALID")