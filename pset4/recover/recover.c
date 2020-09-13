#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }


    //open the file from user input
    FILE *card_ptr = fopen(argv[1], "r");


    unsigned char buffer[512];
    bool init_image = true;
    int file_counter = 0;
    FILE *new_jpg;
    //read 512 bytes
    while (fread(buffer, 1, 512, card_ptr) != 0x00)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            //for the initial image
            if (init_image)
            {
                // open the file
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter++);
                new_jpg = fopen(filename, "w");
                
                // write to new_jpg
                fwrite(buffer, 1, 512, new_jpg);
                init_image = false;

            }
            else
            {

                // for the next images, close previous file
                fclose(new_jpg);
                // open the file
                char filename[8];
                sprintf(filename, "%03i.jpg", file_counter++);
                new_jpg = fopen(filename, "w");

                // write to new_jpg
                fwrite(buffer, 1, 512, new_jpg);
            }

        }
        else
        {
            //for every not starting bits, towards completing the file
            if (!init_image)
            {
                fwrite(buffer, 1, 512, new_jpg);
            }
        }
    }
    //close files
    fclose(new_jpg);
    fclose(card_ptr);
}
