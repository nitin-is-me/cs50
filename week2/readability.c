#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void){

    // ask the user for sentence input
    string text = get_string("Text: ");

    // count the number of letters, words and sentences
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    // average variables per 100
    float average_letters;
    float average_sentences;

    // just printing the total stuff, will comment it out
    // printf("%i letters\n", letters);
    // printf("%i words\n", words);
    // printf("%i sentences\n", sentences);

    // calculating average letters and sentences per 100 words
    average_letters = (letters/(float)words)*100; //one side has to be float
    average_sentences = (sentences/(float)words)*100;

    // calculate the coleman-liau index
    float index = 0.0588 * average_letters - 0.296 * average_sentences - 15.8;

    // print grade level
    if(round(index) < 1){
        printf("Before Grade 1\n");
    } else if(round(index) >= 16){
        printf("Grade 16+\n");
    } else{
        printf("Grade %i\n", (int)round(index)); // first we roung the index, and then convert it to int
    }
}

// count letters
int count_letters(string text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){ // we're calculating strlen only once so it doesn't run on every loop
        // if text at i index is a alphabet character than increase count otherwise not
        if((text[i] >='a' && text[i] <='z') || (text[i] >='A' && text[i] <='Z')){
            count++;
        }
    }
    return count;
}

// count words
int count_words(string text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){
        // count number of spaces and add 1 to it to count words
        if(text[i] == ' '){
            count++;
        }
    }
    return count + 1;
}

// count sentences
int count_sentences(string text){
    int count = 0;
    for(int i = 0, n = strlen(text); i < n; i++){
        // count number of punctuations "." as sentences end with it
        if(text[i] == '.' || text[i] == '!' || text[i] == '?'){
            count++;
        }
    }
    return count;
}
