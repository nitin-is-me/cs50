while(True):
    try:
        height = int(input("Height: "))
        if(height>0 and height<9):
            break
    except ValueError:
        pass

def printSpace(space):
    for _ in range(space):
        print(" ", end="")


def printStars(stars):
    for _ in range(stars):
        print("#", end="")


for i in range(height):
    printSpace(height-i-1)
    printStars(i+1)
    printSpace(2)
    printStars(i+1)
    print()
