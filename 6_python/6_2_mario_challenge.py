# Get a valid input from user
while True:
    try:
        h = input("Height: ")
        h = int(h)
        if h <= 0 or h >= 9:
            raise ValueError
        break

    except ValueError:
        print("Please enter a valid integer")

# Print mario structure
for n in range(h):
    print(" " * (h - (n + 1)) + "#" * (n + 1), end="  ")
    print("#" * (n + 1))
