para = ""
while (para == ""):
    try:
        para = input("Text: ")
    except:
        pass
para = list(para)
sentences = para.count(".") + para.count("?") + para.count("!")  # Number of punctuation is number of sentences
words = para.count(" ") + 1  # Counts white spaces as number of whitespace + 1 is number of words
letters = len([x for x in para if x.isalpha()])  # Grabs Alpha Characters
lvl = round(0.0588 * (letters*100/words) - 0.296 * (sentences*100/words) - 15.8)  # Calculate The Index
if lvl < 1:
    print("Before Grade 1")
elif lvl >= 16:
    print("Grade 16+")
else:
    print(f"Grade {lvl}")