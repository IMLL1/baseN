#include <stdio.h>
#include <math.h>
#include <string.h>

#define MAXNUM 34

int getBase(int);
int decValue(char);
char B10toBn(int);
void getInput(char[], int);
void printStr(char[]);
int parseToBase10(char[], int);
void parseToBaseN(char[], int, int);
int validInput(char[], int);

int main(void)
{
    int baseFrom;           // the base from which we are converting
    int baseTo;             // the base to convert a number to
    char inputStr[BUFSIZ];  // input string in any base
    int numBase10;          // the input in base 10;
    char outputStr[BUFSIZ]; // output string in convert-to-n base

    baseFrom = getBase(0);
    baseTo = getBase(1);

    getInput(inputStr, baseFrom);
    numBase10 = parseToBase10(inputStr, baseFrom);

    parseToBaseN(outputStr, numBase10, baseTo);

    printf("\n\nBase %d: %s\nBase 10: %d\nBase %d: %s", baseFrom, inputStr, numBase10, baseTo, outputStr);

    return 0;
}

/**
 * Prompts the user for a valid base
 *
 * @param isTo      base from (0) or base to (1)
 * @return int      the inputted base
 **/
int getBase(int isTo)
{
    int base;

    do
    {
        if (isTo)
        {
            printf("Enter base to convert to (between 2 and 34): ");
        }
        else
        {
            printf("Enter base of original number (between 2 and 34): ");
        }
        scanf("%d", &base);
    } while (base < 2 || base > MAXNUM);

    return base;
}

/**
 * Gets the decimal value of a digit (0-9, A-Z). Returns 0 for invalid digits
 *
 * @param digit     the digit (0-9 or A-Z)
 * @return int      the decimal value (will be between 0 and 34)
 **/
int decValue(char digit)
{
    int value = -1; // the value of the inputted digit

    if (digit >= '0' && digit <= '9')
    {
        value = digit - '0';
    }
    else if (digit >= 'A' && digit <= 'Z')
    {
        value = digit - 'A' + 10;
    }

    return value;
}

/**
 * Converts a given decimal digit value to a base-n digit
 *
 * @param value         the value of the digit (0-34)
 * @return char         the digit to output, 0-Z
 **/
char B10toBn(int value)
{
    char digitOut;
    if (value <= 9)
    {
        digitOut = value + '0';
    }
    else
    {
        digitOut = value + 'A';
    }

    return digitOut;
}

/**
 * prompts the user for input number
 *
 * @param userInput     string in which to store the input
 **/
void getInput(char userInput[], int base)
{
    int isValid; // whether the input is valid
    do
    {
        fflush(stdin);
        printf("Enter number (with alphabetical characters being in capitals): ");
        scanf("%s", userInput);

    } while (!validInput(userInput, base));
}

/**
 * Parses a base n number as a string into a base 10 int
 *
 * @param inputStr    the base-n number as a string
 * @param base          the base from which to convert
 * @return int          the converted number
 **/
int parseToBase10(char inputStr[], int base)
{
    int output;   // the converted number
    int numDigs;  // the number of digits in base n
    int digPlace; // the active digit place, loop control varable

    numDigs = strlen(inputStr);
    output = 0;
    for (digPlace = 0; digPlace < numDigs; digPlace++)
    {
        output += pow(base, digPlace) * decValue(inputStr[numDigs - digPlace - 1]);
    }

    return output;
}

/**
 * converts a base 10 int to a base n string
 *
 * @param baseNstr      the string to store the base n output
 * @param base10        the input number in base 10
 * @param base          the base to convert to
 **/
void parseToBaseN(char baseNstr[], int base10, int base)
{
    int highestPlace; // highest digit place
    int currentPlace; // looping LCV
    int activeDigit;  // active digit

    highestPlace = log(base10) / log(base);

    for (currentPlace = highestPlace; currentPlace >= 0; currentPlace--)
    {
        activeDigit = base10 / (int)pow(base, currentPlace);
        base10 -= activeDigit * (int)pow(base, currentPlace);
        baseNstr[highestPlace - currentPlace] = B10toBn(activeDigit);
    }

    baseNstr[highestPlace + 1] = '\0';
}

int validInput(char input[], int base)
{
    int idx;      // looping index
    int numChars; // number of characters in the string
    int isValid;  // whether the string is valid
    char val;     // current value we're looking at

    idx = 0;
    numChars = strlen(input);
    do
    {
        val = decValue(input[idx]);
        isValid = val >= 0 && val < base;
    } while (isValid && ++idx < numChars);

    return isValid;
}