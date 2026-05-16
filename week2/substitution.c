#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{

    // make sure programs runs with one cli argument
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return 1;
    }

    // make sure the argument length is 26
    if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    // make sure the argument only contains alphabetical characters
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // make sure every character in argument is an alphabet
        if (!((argv[1][i] >= 'a' && argv[1][i] <= 'z') || (argv[1][i] >= 'A' && argv[1][i] <= 'Z')))
        {
            printf("Key must only contain alphabets.\n");
            return 1;
        }
    }

    // storing argument in a variable
    string argument = argv[1];

    // checking duplicacy by making sure all a to z letters are there in the argument (this idea came in my mind after a lot of thinking lol)
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // inner loop to iterate through all characters from A-Z
        for (int j = 0; j < 26; j++)
        {
            // "i" will iterate through A-Z/a-z and "j" will iterate through all 26 characters in
            // argument
            if (argv[1][j] == i + 65 || argv[1][j] == i + 97) // we added 65 for checking uppercase and 95 for checking lowercase
            {
                break;
            }
            // if j is at last index and the above conditional still didn't find the i+65 ascii character in argv[1] then exit the program
            else if (j == 25)
            {
                printf("duplicacy not allowed");
                return 1;
            }
        }
    }

    // ask the user for plaintext
    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext; // we've to allocate memory to string

    // substitute the plaintext with key entered by user

    for(int i = 0, n = strlen(plaintext); i < n; i++){

        // if i character is uppercase:
        if(plaintext[i] >= 'A' && plaintext[i] <= 'Z'){
            int index = plaintext[i] - 65; //  subtract 65 ('A' ascii code) to iterate over argument from 0 index
            ciphertext[i] = toupper(argument[index]); // convert the letter to uppercase cuz argument might not have uppercase at same index
        } else if(plaintext[i] >= 'a' && plaintext[i] <= 'z') {
            int index = plaintext[i] - 97; //  subtract 97 ('a' ascii code) to iterate over argument from 0 index
            ciphertext[i] = tolower(argument[index]); // convert the letter to lowercase cuz argument might not have lowercase at same index
        }
        // for non alphabetical character we don't do anything as we've already copied plaintext to ciphertext so they will be there as it is
    }

    printf("ciphertext: %s\n", ciphertext);
}
