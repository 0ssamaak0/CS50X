n = -5
while n < 1 or n > 8:
    e = 1
    while e == 1:
        try:
            print("Height: ", end="")
            n = int(input())
        except:
            print("", end="")
        else:
            e = 0

n += 1
i = 1
while i < n:
    j = n - i
    while j > 1:
        print(" ", end="")
        j -= 1
    k = 0
    while k < i:
        print("#", end="")
        k += 1
    print("  ", end="")
    l = 0
    while l < i:
        print("#", end="")
        l += 1
    print()
    i += 1

# THANKS FOR ALL CS50 STAFF!
# :)
