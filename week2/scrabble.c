#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
int player1 = 0;
int player2 = 0;

int compute_score(string word);

int main(void){
    // prompt the user for two words
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    //compute score of each word

    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    //print the winner

    if(score1 > score2){
        printf("Player 1 wins!\n");
    } else if(score1<score2){
        printf("Player 2 wins!\n");
    } else{
        printf("Tie!\n");
    }
}

// computer the score of each word
int compute_score(string word){
    // let score 0
    int point = 0;
    // run loop to calculate score of each letter
    for(int i = 0, n = strlen(word); i < n; i++){

        // we'll subtract the ascii number such that it aligns directly with our POINTS array
        // fetch if the letter is uppercase
        if(isupper(word[i])){
            // subtract 65 from index of our input because A starts from 65 and add to the point
            int wordindex = word[i] - 65;
            point = point + POINTS[wordindex];
        } // else fetch if the letter is lowercase
        else if(islower(word[i])){
            // subtract 97 from index of our input because a starts from 97 and add to the point
            int wordindex = word[i] - 97;
            point = point + POINTS[wordindex];
        } // else add 0
        else{
            point = point + 0;
        }


    }
    return point;
}
