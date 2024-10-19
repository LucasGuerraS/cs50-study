# Get a valid input from user
while True:
    try:
        value = input("Change Owed: ")
        value = round(float(value), 2)
        if value <= 0:
            raise ValueError
        break

    except ValueError:
        print("Please enter a valid floating value")

count = 0

while value > 0:
    if value >= 0.25:
        value = round(value - 0.25, 2)
        count += 1
    elif value >= 0.10:
        value = round(value - 0.10, 2)
        count += 1
    elif value >= 0.05:
        value = round(value - 0.05, 2)
        count += 1
    elif value >= 0.01:
        value = round(value - 0.01, 2)
        count += 1

print(count)
