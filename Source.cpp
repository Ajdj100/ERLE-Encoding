
#include <stdio.h>

unsigned char* encode(unsigned char*, unsigned char*);
unsigned char* decode(unsigned char*, unsigned char*);

int main(void)
{

    unsigned char inputString[65025] = { 0 };
    unsigned char encodedString[65025] = { 0 };
    unsigned char outputString[65025] = { 0 };

    for (int i = 0; i < 65025; i++)
    {
        inputString[i] = 'z';
    }

    encode(inputString, encodedString);

    decode(encodedString, outputString);

    return 0;
}




unsigned char* encode(unsigned char* inputString, unsigned char* outputString)
{
    char buff = '\0'; // the buffer to hold current char
    int count = 0;

    int i = 0; // counter for index of input string
    int o = 0; // counter for index of output string

    buff = inputString[i];

    do
    {

        if (inputString[i + 1] == buff) // if the char matches the next one, add one to the count
            count++;
        else if (count > 3)  // if the run can be shrunk with encoding, do it
        {
            count++;
            int divisor = 1;

            while (count / divisor > 255) {    //finds a working multiplier value
                divisor++;
            }

            int offset = count % divisor;

            int theCount = count/divisor;
            unsigned char theDivisor = (char)divisor;
            unsigned char theOffset = (char)(count % divisor);

            printf("Regular: %d, %d, %d, %c\n", count/divisor, divisor, count%divisor, buff);
            printf("Charified: %d, %d, %d, %c\n", (unsigned char)theCount, theDivisor, theOffset, buff);

            if (divisor > 1) {               //if encoding an oversized run
                outputString[o++] = '~';    //ERLE Escape Character
                outputString[o++] = (unsigned char)theCount;
                outputString[o++] = (unsigned char)divisor;
                outputString[o++] = (unsigned char)offset;
                outputString[o++] = buff;
            }
            else {                          //if you are encoding a normal run
                outputString[o++] = '`';    //normal escape character
                outputString[o++] = (char)count;
                outputString[o++] = buff;
            }

            count = 0; // reset counter
        }
        else
        { // continue on if none of the above
            outputString[o] = inputString[i];
            o++;
        }

        i++;
        buff = inputString[i];
    } while (inputString[i] != '\0');

    outputString[o] = '\0'; // ends string with null (culls empty memory)

    printf("Encoded string: %s\n", outputString);

    return outputString;
}

unsigned char* decode(unsigned char* inputString, unsigned char* outputString)
{
    int i = 0;
    int o = 0;
    do
    {
        if (inputString[i] == '`')  //regular decoding
        {

            i++; // increment to the number

            int numChar = inputString[i]; // Decode the number of chars
            for (int a = 0; a < numChar; a++)
            {
                outputString[o] = inputString[i + 1];
                o++;
            }
            i++;
        }
        else if (inputString[i] = '~') {    //ERLE decoding
            printf("ERLE Decoding\n");
            i++; //increment past the escape character
            unsigned char initialValue = inputString[i++];
            unsigned char multiplier = inputString[i++];
            unsigned char offset = inputString[i++];
            int totalSize = initialValue * multiplier + offset;

            char buf = inputString[i++];

            printf("%d, %d, %d, %d\n", initialValue, multiplier, offset, totalSize);

            for (int a = 0; a < totalSize; a++) {
                outputString[o] = buf;
                o++;
            }
        }
        else
        {
            outputString[o] = inputString[i]; // otherwise just output normally
            o++;
        }
        i++;
    } while (inputString[i] != '\0');

    return outputString;
}