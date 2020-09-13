from cs50 import get_int


def main():
    
    # initialising variables
    cnum = get_int("Number: ")
    
    # obtaining number length
    clen = int(len(str(cnum)))
    cmod = 10
    cmod2 = 1
    pt = 0
    t = 0
    t1 = 0
    ccheck = ccheck2 = 0
    tmod = cmod3 = mydigit = cca = checksum = cardverprev = cardver = 0
    isvisa = False
    # print(f"{clen}")

    for i in range(1, clen+1):
        t = cnum % cmod
        cmod = cmod * 10
        t1 = t - pt
        tmod = t1 / cmod2
        cmod2 = cmod2 * 10
        pt = t
        # this is to add the numbers starting with the number’s second-to-last digit
        if i % 2 == 0:
            mydigit = int(tmod) * 2
            if mydigit < 10:
                ccheck = ccheck + mydigit
            else:
                cmod3 = 10
                # this is to brake a number >= to to 2 digits and add them
                for j in range(2):
                    if (mydigit % cmod3) < 10:
                        cca = int(mydigit) % cmod3
                        ccheck = ccheck + int(cca)
                        # print(f"{cca} {ccheck} {cmod3}")
                        cmod3 = cmod3 * 10
                    else:
                        cca = mydigit % cmod3
                        ccheck = int(ccheck) + (int(cca) / 10)
                        # print(f"{cca} {ccheck} {cmod3}")
                        cmod3 = cmod3 * 10

        # this is to add the remaining numbers
        else:
            ccheck2 = ccheck2 + int(tmod)
        # this is th final number from the addition of the digits
        # print(f"{tmod} {ccheck} {ccheck2}")
        checksum = int(ccheck) + ccheck2

        if (i == clen - 1):
            cardverprev = tmod
        elif i == clen:
            cardver = tmod * 10 + cardverprev
            if tmod == 4:
                isvisa = True

    # check if card is invalid or the type of the card
    if ((clen == 13 or clen == 16) and isvisa and (checksum % 10) == 0):
        print("VISA")
    elif clen == 15 and (cardver == 34 or cardver == 37) and (checksum % 10) == 0:
        print("AMEX")
    elif clen == 16 and (cardver == 51 or cardver == 52 or cardver == 53 or cardver == 54 or cardver == 55) and (checksum % 10) == 0:
        print("MASTERCARD")
    else:
        print("INVALID")


main()