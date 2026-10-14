
#include <stdio.h>
#include <string.h>

#include "budget.h"
#include "utilities.h"

static char budgetNames[MAX_DEPARTMENTS][MAX_DEPT_NAME];
static double budgetAllocated[MAX_DEPARTMENTS];
static double budgetSpent[MAX_DEPARTMENTS];
static int budgetCount = 0;

static int findDepartment(const char *name)
{
    for (int i = 0; i < budgetCount; i++)
    {
        if (strcmp(budgetNames[i], name) == 0)
        {
            return i;
        }
    }

    return -1;
}

double calculateRemainingBudget(double allocated, double spent)
{
    return allocated - spent;
}

int isWithinBudget(double allocated, double spent)
{
    return spent <= allocated;
}

void enterDepartmentBudget(void)
{
    char name[MAX_DEPT_NAME];
    double amount;

    if (budgetCount >= MAX_DEPARTMENTS)
    {
        printf("Maximum number of departments reached.\n");
        return;
    }

    if (!readString("Enter department name: ",
                    name, MAX_DEPT_NAME))
    {
        return;
    }

    if (findDepartment(name) != -1)
    {
        printf("This department already exists.\n");
        return;
    }

    if (!readDouble("Enter allocated budget: ", &amount))
    {
        return;
    }

    strcpy(budgetNames[budgetCount], name);
    budgetAllocated[budgetCount] = amount;
    budgetSpent[budgetCount] = 0.0;

    budgetCount++;

    printf("Department budget added successfully.\n");
}

void enterExpenditure(void)
{
    char name[MAX_DEPT_NAME];
    double amount;
    int index;

    if (budgetCount == 0)
    {
        printf("No departments exist. Add a department budget first.\n");
        return;
    }

    if (!readString("Enter department name: ",
                    name, MAX_DEPT_NAME))
    {
        return;
    }

    index = findDepartment(name);

    if (index == -1)
    {
        printf("Department not found.\n");
        return;
    }

    if (!readDouble("Enter expenditure amount: ", &amount))
    {
        return;
    }

    budgetSpent[index] += amount;

    printf("Expenditure recorded successfully.\n");
    printf("Total expenditure: %.2f\n", budgetSpent[index]);
    printf("Remaining budget: %.2f\n",
           calculateRemainingBudget(
               budgetAllocated[index], budgetSpent[index]));
}

void displayBudgetInfo(void)
{
    if (budgetCount == 0)
    {
        printf("No departmental budgets have been recorded.\n");
        return;
    }

    printf("\n%-20s %12s %12s %12s\n",
           "Department", "Allocated", "Spent", "Remaining");

    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < budgetCount; i++)
    {
        printf("%-20s %12.2f %12.2f %12.2f\n",
               budgetNames[i],
               budgetAllocated[i],
               budgetSpent[i],
               calculateRemainingBudget(
                   budgetAllocated[i], budgetSpent[i]));
    }
}

void searchDepartmentBudget(void)
{
    char name[MAX_DEPT_NAME];
    int index;

    if (!readString("Enter department name: ",
                    name, MAX_DEPT_NAME))
    {
        return;
    }

    index = findDepartment(name);

    if (index == -1)
    {
        printf("Department not found.\n");
        return;
    }

    printf("\nDepartment: %s\n", budgetNames[index]);
    printf("Allocated: %.2f\n", budgetAllocated[index]);
    printf("Spent: %.2f\n", budgetSpent[index]);
    printf("Remaining: %.2f\n",
           calculateRemainingBudget(
               budgetAllocated[index], budgetSpent[index]));

    if (isWithinBudget(budgetAllocated[index], budgetSpent[index]))
    {
        printf("Status: Within budget.\n");
    }
    else
    {
        printf("Status: Budget exceeded by %.2f.\n",
               budgetSpent[index] - budgetAllocated[index]);
    }
}

void displayExceededDepartments(void)
{
    int found = 0;

    printf("\nDEPARTMENTS OVER BUDGET\n");
    printf("-----------------------\n");

    for (int i = 0; i < budgetCount; i++)
    {
        if (!isWithinBudget(budgetAllocated[i], budgetSpent[i]))
        {
            printf("%s: exceeded by %.2f\n",
                   budgetNames[i],
                   budgetSpent[i] - budgetAllocated[i]);

            found = 1;
        }
    }

    if (!found)
    {
        printf("No departments have exceeded their budgets.\n");
    }
}

int getDepartmentCount(void)
{
    return budgetCount;
}

double getTotalAllocated(void)
{
    double total = 0.0;

    for (int i = 0; i < budgetCount; i++)
    {
        total += budgetAllocated[i];
    }

    return total;
}

double getTotalExpenditure(void)
{
    double total = 0.0;

    for (int i = 0; i < budgetCount; i++)
    {
        total += budgetSpent[i];
    }

    return total;
}

double getTotalRemaining(void)
{
    return getTotalAllocated() - getTotalExpenditure();
}

int countExceededDepartments(void)
{
    int count = 0;

    for (int i = 0; i < budgetCount; i++)
    {
        if (!isWithinBudget(budgetAllocated[i], budgetSpent[i]))
        {
            count++;
        }
    }

    return count;
}

void budgetMenu(void)
{
    int choice;

    do
    {
        printf("\n========== BUDGET MANAGEMENT ==========\n");
        printf("1. Add Department Budget\n");
        printf("2. Enter Expenditure\n");
        printf("3. Display Budgets\n");
        printf("4. Check Budget Status\n");
        printf("5. Display Exceeded Departments\n");
        printf("0. Back to Main Menu\n");

        if (!readInt("Enter your choice: ", &choice))
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                enterDepartmentBudget();
                break;

            case 2:
                enterExpenditure();
                break;

            case 3:
                displayBudgetInfo();
                break;

            case 4:
                searchDepartmentBudget();
                break;

            case 5:
                displayExceededDepartments();
                break;

            case 0:
                printf("Returning to the main menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
