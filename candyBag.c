#include <stdio.h>
#include <string.h>
// Function prototypes
void getCandyCounts(char **candyBagPtrs, int numCandies[]);
char menu();
void displayCandy(char **candyBagPtrs, int numCandies[]);
void displayIndividualCandy(char **candyBagPtrs, int numCandies[]);


int main()
{
    // Initialize an array of strings holding the candy name, and another array to hold the amount of each candy
    char *candyBag[] = {"Snickers", "Hersheys", "Skittles", "Reeses", "Kit Kat bar"};
    int numCandies[5];
    char choice;

    getCandyCounts(candyBag, numCandies);

    while (choice != 'E')
    {
        // Grab the user's choice and use a switch statement to handle the user's different choices by calling different functions
        choice = menu();

        switch(choice)
        {
            case 'A':
                displayCandy(candyBag, numCandies);
                break;
            case 'B':
                displayIndividualCandy(candyBag, numCandies);
                break;
            case 'C':
                break;
            case 'D':
                printf("\nWIP, sorry!");
                break;
        }
    }
    return 0;
}



// User defined functions
void getCandyCounts(char **candyBagPtrs, int *numCandies)
{
    // Use a loop to ask the user what candy they would like to collect, and save the answer in the numCandies array
    for (int i = 0; i < 5; i++)
    {
        printf("\nEnter the quantity of %s you collected: ", candyBagPtrs[i]);
        scanf("\n%d", &numCandies[i]);
    }
}


char menu()
{
    char menuChoice;

    // Display a menu with choices in the program for the user and return the user's choice
    printf("\n\nPlease choose from the following menu:\n");
    printf("\nA: Display total count of all candy\n");
    printf("\nB: Display total count of a specific type of candy\n");
    printf("\nC: Eat some candy\n");
    printf("\nD: (WIP) Read saved candy from a file\n");
    printf("\nE: Quit\n\n");

    scanf("\n%c", &menuChoice);

    // Set menuChoice to uppercase and return it
    if (menuChoice > 96 && menuChoice < 123)
        menuChoice -= 32;

    return menuChoice;
}


void displayCandy(char **candyBagPtrs, int numCandies[])
{
    int i;

    // Use both arrays passed in to display how many of each candy bars the user has
    printf("\nYou received:\n");

    for (i = 0; i < 5; i++)
        printf("\n%d: %d %s", i + 1, numCandies[i], candyBagPtrs[i]);
}


void displayIndividualCandy(char **candyBagPtrs, int numCandies[])
{
    char candyChoice[20];
    int i;
    int isCandyAvail = 0; // Check if the candy that the user typed in is found in the string array

    while (isCandyAvail == 0)
    {
        // First ask the user what candy they would like to see individually
        printf("\nPlease enter the name of the candy: ");
        scanf("\n%[^\n]", candyChoice);

        // Loop through the candyNamesPtr array to find a match
        for (i = 0; i < 5; i++)
        {
            if (strcmp(candyChoice, candyBagPtrs[i]) == 0)
            {
                // If there is a match set isCandyAvail to 1 and display how much of the candy the user has left
                printf("\nYou have %d %s left!", numCandies[i], candyBagPtrs[i]);
                isCandyAvail = 1;
            }
        }

        // After for loop if isCandyAvail is not 1 then assume the user entered a candy not in the bag and let them enter a match in the bag
        if (isCandyAvail == 0)
            printf("\n%s is not in your bag! Please try again!", candyChoice);
    }
}
