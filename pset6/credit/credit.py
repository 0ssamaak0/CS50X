number = int(input("Number: "))
sum = 0
i = 10
j = 1
k = 1

while i < 10000000000000000:
    double_dig = ((number // i) % 10) * 2
    for j in range(1, 12, 9):
        # print(f"i is {i} and j is {j}")
        sum += ((double_dig // j) % 10)
    i = i * 100
while k < 10000000000000000:
    other_digits = (number // k) % 10
    # print(f"k is{k}")
    sum += other_digits
    k *= 100

print(f"{sum}")

if (sum % 10) == 0:
    if number // 10000000000000 == 34 or number // 10000000000000 == 37:
        print("AMEX")
    elif number // 100000000000000 == 51 or number // 100000000000000 == 52 or number // 100000000000000 == 53 or number // 100000000000000 == 54 or number // 100000000000000 == 55:
        print("MASTERCARD")
    elif number // 1000000000000 == 4 or number // 1000000000000000 == 4:
        print("VISA")
    else:
        print("INVALID")
else:
    print("INVALID")