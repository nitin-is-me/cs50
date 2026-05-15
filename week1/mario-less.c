#include <cs50.h>
#include <stdio.h>

void print_row(int bricks, int inp);

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1);

    for (int i = 0; i < n; i++)
    {
        //passing i + 1 because we can't print 0 bricks
        print_row(i + 1, n);
    }
}

void print_row(int bricks, int inp)
{

    // we subtract bricks for total number of height to print spaces
    for(int i = inp - bricks; i > 0; i--){
        printf(" ");
    }

    //print the bricks

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }
    printf("\n");
}
