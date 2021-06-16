//Author Adam Johnson
//Program reads in a decimal and outputs a binary LED to raspberry pi. Negative numbers are turned into a 2's complement. 
//

#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>

//My 8 bit pins used to display my LED's. If we wanted to add more, we can add to the array. The ledNum will automatically adjust our mask.
int pinsUsed[] = {23,26,24, 22, 4, 3 , 1, 0};
//Each number is 4 bits in the array. Here size of pinsUsed is 16 bits. This gets divided by the size of an int which is 4.
int ledNum = sizeof(pinsUsed) / sizeof(int);

//Function for repeatable loop in main loop
void displayBinary(int number)
{
    //Shows user selected number
    printf("Selected number is: %d\n", number); 
    //Creating our mask
    int mask = (1 << ledNum) - 1;
    //Applying mask to number
    int numberMask = number & mask;
    //Outputs outcome of mask in LED format
    for (int i = 0; i < ledNum; i++) {  //
        if (numberMask & (1 << i)) {
            digitalWrite(pinsUsed[i], HIGH); //LED turns on if loop is true
                
        } else {
            digitalWrite(pinsUsed[i], LOW); //LED turns off if loop is false
        }
    }
}

int main(void)
{
    int number;
    if(wiringPiSetup() == -1){
		puts("Raspberry Pi setup failed. Check the wiringPi library");
		return 1;
	}
    for (int i = 0; i < 4; i++) {
        pinMode(pinsUsed[i], OUTPUT);
        digitalWrite(pinsUsed[i], LOW);
    }

    while (1==1) {

        printf("Select a number\n");
        scanf("%i", &number);
        displayBinary(number);
    }

    return 0;
}
