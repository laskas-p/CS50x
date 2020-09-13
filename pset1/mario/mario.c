#include <stdio.h>
#include <cs50.h>

//initial call of function
int get_positive_int(void);

int main(void)
{
    //variable declaration
    int i = get_positive_int();
    int k = i;
    int p = i;

    //line loop
    while (k >= 1)
    {
        //first loop until i characters at k line
        for (int j = 1; j <= i; j++)
        {
            if (j < k)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf(" ");
        printf(" ");
        //second loop until i characters at k line
        while (p >= 1)
        {
            if (p >= k)
            {
                printf("#");
            }
            else
            {
                printf("");
            }
            p = p - 1;
        }
        printf("\n");
        p = i;
        k = k - 1;
    }
}

//check for accepting only positive integer
int get_positive_int(void)
{
    int n;
    //check loop for inputing numbers only between 1 to 8
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 || n > 8);
    return n;
}