#include <stdio.h>
#include <string.h>
// Function prototypes
void getCandyCounts(char **candyBagPtrs, int numCandies[]);
char menu();
void displayCandy(char **candyBagPtrs, int numCandies[]);
void displayIndividualCandy(char **candyBagPtrs, int numCandies[]);
void getCandyToEat(char **candyBagPtrs, int numCandies[], int *candyChoicePtr, int *eatAmount);
void downloadFile(int numCandies[]);


int main()
{
    // Initialize an array of strings holding the candy name, and another array to hold the amount of each candy
    char *candyBag[] = {"Snickers", "Hersheys", "Skittles", "Reeses", "Kit Kat bar"};
    int numCandies[5], candyChoice, eatAmount;
    char choice;

    // Grab the amount of candy the user has in each bag
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
                getCandyToEat(candyBag, numCandies, &candyChoice, &eatAmount);

                // Update the amount of candy after it has been eaten in the numCandies array
                numCandies[candyChoice - 1] -= eatAmount;
                break;
            case 'D':
                downloadFile(numCandies);
                break;
            case 'E':
                printf("\nClosing candy bag program.");
                break;
            default:
                printf("\nInvalid input, please select a valid letter.");
                break;
        }
    }
    return 0;
}



// User defined functions
void getCandyCounts(char **candyBagPtrs, int *numCandies)
{
    int choice, i;
    FILE *candyBagFile;
    char fileName[50];

    // Ask the user if they have a file that they would like to load into the program or manually enter that data by choosing from a menu
    printf("\nWelcome to the candy bag program, how would you like to load your data?");
    printf("\n1 - Manually enter the amount of each candy");
    printf("\n2 - Load data for the candy bag from a text file\n");
    scanf("\n%d", &choice);

    // Validate menu entry
    while (choice < 1 || choice > 2)
    {
        printf("\nInvalid input, please select a valid option (1-2) from the menu");

        printf("\n1 - Manually enter the amount of each candy");
        printf("\n2 - Load data for the candy bag from a text file\n");
        scanf("\n%d", &choice);
    }

    switch(choice)
    {
        case 1:
            // Use a loop to ask the user what candy they would like to collect, and save the answer in the numCandies array
            for (int i = 0; i < 5; i++)
            {
                printf("\nEnter the quantity of %s you collected: ", candyBagPtrs[i]);
                scanf("\n%d", &numCandies[i]);
            }
            break;
        case 2:
            // Ask the user for the file name and see if there is a match
            printf("\nPlease enter the name of your txt file (include .txt at the end) ");
            scanf("\n%s", fileName);

            while ((candyBagFile = fopen(fileName, "r")) == NULL)
            // If the user enters an invalid (null) file name let them enter a valid one
            {
                printf("\nError! %s could not be found.", fileName);

                printf("\nPlease enter the name of your txt file (include .txt at the end) ");
                scanf("\n%s", fileName);
            }

            // File found, begin reading each line in the text file and assign it to the numCandies arrau
            for (i = 0; i < 5; i++)
                fscanf(candyBagFile, "\n%d", &numCandies[i]);

            break;
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
    printf("\nD: Save the candy bag into a text file\n");
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
    char candyChoice[50];
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


void getCandyToEat(char **candyBagPtrs, int numCandies[], int *candyChoicePtr, int *eatAmountPtr)
{
    int i, candyChoice, eatAmount;

    // Display menu to let the user choose (1-5) which candy they want to eat
    for (i = 0; i < 5; i++)
        printf("\n%d:   %s", i + 1, candyBagPtrs[i]);

    printf("\nWhich candy would you like to eat (1-5): ");
    scanf("\n%d", &candyChoice);

    // Make sure candyChoice is (1-5)
    while (candyChoice < 1 || candyChoice > 5)
    {
        printf("\nInvalid entry, please enter between 1-5");

        printf("\nWhich candy would you like to eat (1-5): ");
        scanf("\n%d", &candyChoice);
    }

    // Ask how much of that candy they would like to eat and validate that data
    printf("\nHow many would you like to eat? ");
    scanf("\n%d", &eatAmount);

    while (eatAmount > numCandies[candyChoice - 1] || eatAmount < 0)
    {
        if (eatAmount <= 0)
            printf("\nYou can not eat a negative amount of %s! Please enter a valid amount", candyBagPtrs[candyChoice - 1]);
        else
            printf("\nThere is not enough %s! Please enter a valid amount", candyBagPtrs[candyChoice - 1]);

        printf("\nHow many would you like to eat? ");
        scanf("\n%d", &eatAmount);
    }

    // assign the candy choice and amount of candy the user wants to eat after validation
    *candyChoicePtr = candyChoice;
    *eatAmountPtr = eatAmount;
}


void downloadFile(int numCandies[])
{
    FILE *candyBagFile;
    char fileName[50];
    int i;

    // Ask the user what would they like to name the file before they download it
    printf("\nWhat would you like to name your file? (make sure the name ends in .txt) ");
    scanf("\n%s", fileName);

    // Download the file name if it does not already exist, otherwise it will overwrite
    candyBagFile = fopen(fileName, "w");

    // Start writing the candy name in one line, and its amount in the line after, and repeat
    for (i = 0; i < 5; i++)
        fprintf(candyBagFile, "%d\n", numCandies[i]);       // Amount in bag per candy written in file

    // Close the file
    fclose(candyBagFile);

    printf("\nFile successfully downloaded.");
}
