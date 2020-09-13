#include <stdio.h>
#include <cs50.h>

int main(void)
{
//ask for name
    string name = get_string("what's your name?\n");
//print name
    printf("hello, %s\n", name);
}