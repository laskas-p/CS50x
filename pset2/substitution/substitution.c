#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

//initial call of function to check the keys
int key_check(string my_key);

int main(int argc, string argv[])
{
    //checking if ther are two arguments
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //what to do when the user KEY input is wrong
    if (key_check(argv[1]) == 0)
    {
        printf("Key must contain 26 characters one time only.\n");
        return 1;
    }
    else if (key_check(argv[1]) == 1)
    {
        string c_key = argv[1];
        string plaintext = get_string("plaintext: ");
        int len = strlen(plaintext);
        string my_string[len];
        printf("ciphertext: ");
        for (int n = 0; n < len; n++)
        {
            //check for the characters
            if ((plaintext[n] >= 'a' && plaintext[n] <= 'z') || (plaintext[n] >= 'A' && plaintext[n] <= 'Z'))
            {
                int char_counter = 0;
                int zcounter = 0;
                //printf for lower characters
                for (char z = 'a'; z <= 'z'; z++)
                {
                    if (plaintext[n] == z)
                    {
                        char_counter = zcounter;

                        char c = tolower(c_key[char_counter]);
                        printf("%c", c);

                    }
                    zcounter ++;
                }

                //printf for upper characters
                int z1counter = 0;
                for (char z = 'A'; z <= 'Z'; z++)
                {
                    if (plaintext[n] == z)
                    {
                        int char_counter1 = z1counter;

                        char c1 = toupper(c_key[char_counter1]);
                        printf("%c", c1);

                    }
                    z1counter ++;
                }
            }
            //printf for symbols
            else
            {
                printf("%c", plaintext[n]);
            }
        }


        printf("\n");
        return 0;
    }
}

// check the key
int key_check(string my_key)
{
    int check_key = 0;

    if (strlen(my_key) == 26)
    {
        //printf("ok length\n");
        for (int i = 0; i <= 25; i++)
        {
            //printf("hi\n");
            if ((my_key[i] >= 'a' && my_key[i] <= 'z') || (my_key[i] >= 'A' && my_key[i] <= 'Z'))
            {
                for (int j = 0; j <= i; j++)
                {
                    if (my_key[j - 1] == toupper(my_key[i]) || my_key[j - 1] == tolower(my_key[i]))
                    {
                        return 0;
                    }
                }
                check_key ++;
                //printf("check_key: %i", check_key);
            }
        }

    }
    else
    {
        return 0;
    }
    if (check_key == 26)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
