from cs50 import get_int


def main():
    # Do while loop for getting height
    while True:
        height = get_int("Height: ")
        if height > 0 and height < 9:
            break
    print_bricks(height, height)
    return 0


def print_bricks(height, original_height):
    # Base case for recursion
    if height < 1:
        return
    # Recursively calls the function until height is less than 1
    print_bricks(height - 1, original_height)
    # Prints spaces with no line break
    print(" " * (original_height - height), end="")
    # Prints bricks
    print("#" * height)


main()