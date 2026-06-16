#include <stdio.h>
#include <stdlib.h>
#define MONTHS 12
char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

typedef struct
{
    float sales[MONTHS];
} branch;

// Asks the user to fill in the sales data for every branch and month
// Validates input and rejects negatives and non-numeric characters
void entrydata(int n, branch ar[])
{
    printf("Enter sales data:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MONTHS; j++)
        {
            int result;
            do
            {
                result = scanf("%f", &ar[i].sales[j]);
                if (result != 1) // this checks if user has entered something that's not a number
                {
                    printf("Invalid input, enter a number:\n");
                    while (getchar() != '\n') // this clears the buffer
                        ;
                }
                else if (ar[i].sales[j] < 0) // this checks if user entered a negative sale
                    printf("Can't enter negative sale, try again:\n");
            } while (result != 1 || ar[i].sales[j] < 0);

            printf("Branch %d %s sale is $%.2f\n", i + 1, months[j], ar[i].sales[j]);
        }
    }
    // print a summary of each branch's total after all data is entered
    printf("\nBranch Totals:\n");
    for (int i = 0; i < n; i++)
    {
        float total = 0; // reset for each branch
        for (int j = 0; j < MONTHS; j++)
            total += ar[i].sales[j]; // sum the 12 months
        printf("Branch %d: $%.2f\n", i + 1, total);
    }
}

// Loops through the entire sales table and adds everything up
// Returns the total revenue of the company across all branches and months
float totalsales(int n, branch ar[])
{
    float sum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MONTHS; j++)
        {
            sum += ar[i].sales[j];
        }
    }
    return sum;
}

// Calculates and prints the percentage share of each branch in the total company sales
void branchpercentage(int n, branch ar[])
{
    float sum = totalsales(n, ar); // get the total company sales
    if (sum <= 0)
    {
        printf("No sales data entered yet, cannot calculate percentages.\n");
        return;
    }
    float sum2;
    for (int i = 0; i < n; i++)
    {
        sum2 = 0; // reset before each branch
        for (int j = 0; j < MONTHS; j++)
        {
            sum2 += ar[i].sales[j]; // sum up the branch's 12 months
        }
        float raw = sum2;          // save raw total before converting to percentage
        sum2 = (sum2 / sum) * 100; // calculate the percentage
        printf("Branch %d: $%.2f (%.2f%%)\n", i + 1, raw, sum2);
    }
}
// Finds and prints the month with the highest total sales across all branches
void peakmonth(int n, branch ar[])
{
    float max = -1.0;
    float monthsum = 0;
    int peakindex = 0;
    for (int i = 0; i < MONTHS; i++)
    {
        monthsum = 0; // reset before each month

        for (int j = 0; j < n; j++)
        {
            monthsum += ar[j].sales[i]; // sum all branches for this month
        }
        if (max < monthsum) // check if this month beats the current max
        {
            max = monthsum;
            peakindex = i; // save which month it was
        }
    }
    printf("The month with the highest total sales is %s: $%.2f sales\n", months[peakindex], max);
}
// Sorts and displays branches in descending order of sales for a user-chosen month
void branchsort(int n, branch ar[])
{
    int chosenmonth;
    float tempSales;
    int tempIndex;
    float *sales = malloc(n * sizeof(float));
    int *indices = malloc(n * sizeof(int));
    if (!sales || !indices)
    {
        free(sales);
        free(indices);
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Select which month you want: 1-12\n");
    do
    {
        scanf("%d", &chosenmonth);
        if (chosenmonth < 1 || chosenmonth > 12)
            printf("Invalid, please choose from 1-12:\n");
    } while (chosenmonth < 1 || chosenmonth > 12);
    chosenmonth--; // shift to 0-11 for array indexing

    for (int i = 0; i < n; i++)
        indices[i] = i; // fill indices with 0, 1, 2... to track branch positions

    for (int i = 0; i < n; i++)
        sales[i] = ar[i].sales[chosenmonth]; // grab each branch's sales for the chosen month

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (sales[j] < sales[j + 1]) // if left is smaller than right, swap
            {
                // swap sales
                tempSales = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = tempSales;
                // swap indices together so we don't lose track of which branch is which
                tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }

    for (int i = 0; i < n; i++)
        printf("Branch %d: $%.2f\n", indices[i] + 1, sales[i]); // print sorted results

    free(sales);   // release dynamically allocated memory
    free(indices); // release dynamically allocated memory
}
// Sorts and displays months in descending order of sales for a user-chosen branch
void monthsort(int n, branch ar[])
{
    int chosenbranch;
    float tempSales;
    int tempIndex;
    float *sales = malloc(MONTHS * sizeof(float));
    int *indices = malloc(MONTHS * sizeof(int));
    if (!sales || !indices)
    {
        free(sales);
        free(indices);
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Select which branch you want: 1-%d\n", n);
    do
    {
        scanf("%d", &chosenbranch);
        if (chosenbranch < 1 || chosenbranch > n)
            printf("Invalid, please choose from 1-%d:\n", n);
    } while (chosenbranch < 1 || chosenbranch > n);
    chosenbranch--; // shift to 0-indexed for array access

    for (int i = 0; i < MONTHS; i++)
        indices[i] = i; // fill indices with 0-11 to track month positions

    for (int i = 0; i < MONTHS; i++)
        sales[i] = ar[chosenbranch].sales[i]; // grab the chosen branch's 12 months of sales

    for (int i = 0; i < MONTHS - 1; i++)
    {
        for (int j = 0; j < MONTHS - 1 - i; j++)
        {
            if (sales[j] < sales[j + 1]) // if left is smaller than right, swap
            {
                // swap sales
                tempSales = sales[j];
                sales[j] = sales[j + 1];
                sales[j + 1] = tempSales;
                // swap indices together so we don't lose track of which month is which
                tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }

    for (int i = 0; i < MONTHS; i++)
        printf("%s: $%.2f\n", months[indices[i]], sales[i]); // print sorted results

    free(sales);   // release dynamically allocated memory
    free(indices); // release dynamically allocated memory
}
// Menu that lets the user choose a functionality and loops until they choose to exit
void menu(int n, branch ar[])
{
    int dataentered = 0;
    int choice;
    char cont;

    do
    {
        printf("1- Enter sales data\n");
        printf("2- Display total sales\n");
        printf("3- Display percentage share per branch\n");
        printf("4- Display peak sales month\n");
        printf("5- Sort branches by month\n");
        printf("6- Sort months by branch\n");
        printf("7- Exit\n");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input, please enter a number.\n");
            while (getchar() != '\n')
                ; // clears the buffer
            continue;
        }
        switch (choice)
        {
        case 1:
            entrydata(n, ar);
            dataentered = 1;
            break;
        case 2:
            if (dataentered == 0)
                printf("Please enter sales data first (option 1).\n");
            else
                printf("Total sales: $%.2f\n", totalsales(n, ar));
            break;

        case 3:
            if (dataentered == 0)
                printf("Please enter sales data first (option 1).\n");
            else
                branchpercentage(n, ar);
            break;

        case 4:
            if (dataentered == 0)
                printf("Please enter sales data first (option 1).\n");
            else
                peakmonth(n, ar);
            break;

        case 5:
            if (dataentered == 0)
                printf("Please enter sales data first (option 1).\n");
            else
                branchsort(n, ar);
            break;

        case 6:
            if (dataentered == 0)
                printf("Please enter sales data first (option 1).\n");
            else
                monthsort(n, ar);
            break;

        case 7:
            printf("Terminating program\n");
            return;
        default:
            printf("Invalid option, please choose 1-7\n");
            break;
        }
        printf("\nDo you want to continue? y/n\n");
        scanf(" %c", &cont);

    } while (cont == 'y' || cont == 'Y');
}
int main()
{
    int n;
    printf("=== Retail Sales System 2019 ===\n\n");
    do
    {
        printf("Enter The amount of branches:\n");
        scanf("%d", &n);
        if (n <= 0)
            printf("Invalid, number of branches must be greater than 0:\n");
    } while (n <= 0);
    branch *ar = malloc(n * sizeof(branch));
    if (ar == NULL)
    {
        printf("Memory allocation failed, terminating program.\n");
        return 1;
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < MONTHS; j++)
        {
            ar[i].sales[j] = 0.0; // initialize all sales to 0 to prevent garbage memory
        }
    }
    menu(n, ar);
    free(ar);
    return 0;
}