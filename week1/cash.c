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
        print_row(i + 1, n);
    }
}

void print_row(int bricks, int inp)
{
    for (int i = inp - bricks; i > 0; i--)
    {
        printf(" ");
    }

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    // we add space instead of new line

    printf("  ");

    for (int i = 0; i < bricks; i++)
    {
        printf("#");
    }

    // now we add new line

    printf("\n");
}
