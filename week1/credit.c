#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // take input from user for card number;
    long n;
    // for storing card number length while incrementing through it.
    int i;
    // sum of even place's digits.
    int even = 0;
    // sum of odd place's digits.
    int odd = 0;
    // storing first digit
    int first = 0;
    // storing second digit
    int second = 0;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

    // now we've to extract every two's digits and one' digits separately

    for (i = 0; n > 1; i++)
    {

        // keep adding odd place's digit to itself
        if (i % 2 == 0)
        {
            int lastDig = n % 10;
            odd = odd + lastDig;
        }
        // keep multiplying even place's digits by 2 and then keep adding to every other even
        // place's digit
        else
        {
            int lastDig = n % 10;

            // if lastDig*2 is greater than 10 then we need to split and add it too, so we check if it's greater or equal to 10 which is smallest 2 digit number
            if ((lastDig * 2) / 10 >= 1)
            {
                int firstDig = (lastDig * 2) % 10;
                int secondDig = (lastDig * 2) / 10;
                lastDig = firstDig + secondDig;
                even = lastDig + even;
            }
            // if not, then just multiple lastDig by 2 and add to even
            else
            {
                even = (lastDig * 2) + even;
            }
        }

        // now check for last two digit because all cards have different starting digits
        if(n/10 >= 1){
            // because we're iterating reversly, we've to store first in second and second in first digit variable
            second = n%10;
            first = n/10;
        }

        // keep removing last digit to move to next digit
        n = n / 10;
    }

    // add both and store it to final checksum
    int checksum = odd + even;
    // now divide the checksum by 10, and check for cards starting numbers and length, else it's invalid.
    if(checksum % 10 == 0){
        if((i == 13 || i == 16) && first == 4){
            printf("VISA\n");
        } else if(i == 15 && first == 3 && (second == 4 || second == 7)){
            printf("AMEX\n");
        } else if(i == 16 && first == 5 && second >=1 && second <=5){
            printf("MASTERCARD\n");
        } else{
            printf("INVALID\n");
        }

    } else{
        printf("INVALID\n");
    }
}
