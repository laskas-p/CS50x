from cs50 import get_int


def main():
    # defining variables 
    h = get_height()
    k = h
    p = h
    
    # line loop
    while k >= 1:
        
        # first loop until h characters at k line
        for j in range(h):
            if j + 1 < k:
                print(" ", end="")
            else:
                print("#", end="")
        print(" ", end="")
        print(" ", end="")
        
        # second loop until h characters at k line
        while p >= 1:
            if p >= k:
                print("#", end="")
            else:
                print("", end="")
            p = p - 1
        print()
        p = h
        k -= 1        
        
# check for valid integer function


def get_height():
    while True:
        n = get_int("Height: ")
        if n > 0 and n < 9:
            break
    return n


main()