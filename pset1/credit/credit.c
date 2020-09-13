#include <stdio.h>
#include <cs50.h>

//initial call of the function
int num_length(long cnl);


int main(void)
{
    //initialising variables
    long cnum = get_long("Number: ");
    //calling function to obtqain number length
    int clen = num_length(cnum);
    long cmod = 10;
    long cmod2 = 1;
    long long pt = 0;
    long long t, t1;
    int ccheck, ccheck2 = 0;
    int i, tmod, j, cmod3, mydigit, cca, checksum, cardverprev, cardver;
    bool isvisa = false;

    for (i = 1; i <= clen; i++)
    {
        t = cnum % cmod;
        cmod = cmod * 10;
        t1 = t - pt;
        tmod = t1 / cmod2;
        cmod2 = cmod2 * 10;
        pt = t;
        
    
        //this is to add the numbers starting with the number’s second-to-last digit
        if (i % 2 == 0)
        {
            mydigit = tmod * 2;
            if (mydigit < 10)
            {
                ccheck = ccheck + mydigit;
            }
            else
            {
                cmod3 = 10;
                //this is to brake a number >= to to 2 digits and add them
                for (j = 0; j <= 1; j++)
                {
                    if ((mydigit % cmod3) < 10)
                    {
                        cca = mydigit % cmod3;
                        ccheck = ccheck + cca;

                        printf("cca:%i, ccheck:%i,cmod3:%i\n",cca, ccheck,cmod3);
                        cmod3 = cmod3 * 10;

                    }
                    else
                    {
                        cca = mydigit % cmod3;
                        ccheck = ccheck + (cca / 10);

                        printf("cca:%i, ccheck:%i,cmod3:%i\n",cca, ccheck,cmod3);
                        cmod3 = cmod3 * 10;
                    }



                }
            }
        }
        //this is to add the remaining numbers
        else
        {
            ccheck2 = ccheck2 + tmod;
        }
        printf("Digit=%i, Checksum:%i, Ccheck2:%i\n",tmod,ccheck, ccheck2);
        //this is th final number from the addition of the digits
        checksum = ccheck + ccheck2;

        if (i == clen - 1)
        {
            cardverprev = tmod;
        }
        else if (i == clen)
        {
            cardver = tmod * 10 + cardverprev;
            if (tmod == 4)
            {
                isvisa = true;
            }
        }
        //printf("cardver:%i", cardver);


    }
    //check if card is invalid or the type of the card
    if ((clen == 13 || clen == 16) && isvisa && (checksum % 10) == 0)
    {
        printf("VISA\n");
    }
    else if (clen == 15 && (cardver == 34 || cardver == 37) && (checksum % 10) == 0)
    {
        printf("AMEX\n");
    }
    else if (clen == 16 && (cardver == 51 || cardver == 52 || cardver == 53 || cardver == 54 || cardver == 55) && (checksum % 10) == 0)
    {
        printf("MASTERCARD\n");
    }
    else
    {
        printf("INVALID\n");
    }

}



//function to return the length of the number given by the user
int num_length(long cnl)
{
    int l;
    for (l = 0; cnl != 0; l++)
    {
        cnl = cnl / 10;
    }
    //printf("Length: %i\n", l);
    return l;
}