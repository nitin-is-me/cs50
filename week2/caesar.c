#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // make sure program runs with just one line arguement
    if (argc != 2)
    {
        printf("Usage: %s key \n", argv[0]);
        return 1;
    }

    // make sure every character in argv[1] is a digit

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (!(argv[1][i] > 48 && argv[1][i] < 57))
        { // using 0 to 9's ascii
            printf("Usage: %s key \n", argv[0]);
            return 1;
        }
    }

    // convert argv[1] from string to int (i literally had no idea, i just came up with this idea
    // and i feel so good)

    int key = 0;

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        int digit = argv[1][i] - 48; // 0 starts from 48 ASCII number, so we minus 48 to align them
                                     // to zero index, we can also do argv[1][i] - '0'
        key = (key * 10) + digit;
    }

    // prompt user for plaintext

    string plaintext = get_string("plaintext: ");
    string ciphertext =
        plaintext; // string should be allocated memory or else it was throwing segfault error

    // for each text in plaintext
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        // rotate the text by keys given by user if it's an alphabetical character
        // converting the plaintext first from ascii to 0 index for applying formula, then back
        // normal to ascii for storing in ciphertext
        if ((plaintext[i] >= 'A' && plaintext[i] <= 'Z'))
        { // i was forgetting to put = in < and > which was failing the test
            plaintext[i] -= 65;
            // we use modulo wrap around in case the number is 26 or more, it'll loop back from 0
            int text = (plaintext[i] + key) % 26;
            ciphertext[i] = text + 65;
        }
        else if ((plaintext[i] >= 'a' && plaintext[i] <= 'z'))
        {
            plaintext[i] -= 97;
            int text = (plaintext[i] + key) % 26;
            ciphertext[i] = text + 97;
        }
        // else put the text as it is
        else
        {
            int text = plaintext[i];
            ciphertext[i] = text;
        }
    }
    printf("ciphertext: %s\n", ciphertext);
}
