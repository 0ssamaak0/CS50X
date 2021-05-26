print("Text: ", end="")
txt = input()


def main():
    L = count_letters(txt) / count_words(txt) * 100
    S = count_sentences(txt) / count_words(txt) * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    if index < 1:
        print("Before Grade 1")
    elif (index > 16):
        print("Grade 16+")
    else:
        print(f"Grade {int(round(index,0))}")


def count_letters(instr):
    sum = 0
    for i in (instr):
        if i in [" ", "?", "!", ".", "\'", ",", "-", "_", "\"", ":"]:
            sum = sum
        else:
            sum += 1
    return sum


def count_words(instr):
    sum = 1
    for i in (instr):
        if i == " ":
            sum += 1
    return sum


def count_sentences(instr):
    sum = 0
    for i in (instr):
        if i == "." or i == "!" or i == "?":
            sum += 1
    return sum


print(f"{count_letters(txt)} letter(s)")
print(f"{count_words(txt)} word(s)")
print(f"{count_sentences(txt)} sentence(s)")
main()
