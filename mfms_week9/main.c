
#include <stdio.h>

#include "employees.h"
#include "budget.h"
#include "reports.h"
#include "utilities.h"

int main(void)
{
    int choice;

    do
    {
        printf("\n");
        printf("============================================\n");
        printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
        printf("============================================\n");
        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Financial Reports\n");
        printf("0. Exit\n");
        printf("============================================\n");

        if (!readInt("Enter your choice: ", &choice))
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                budgetMenu();
                break;

            case 3:
                displayBudgetReport();
                break;

            case 0:
                printf("Thank you for using MFMS. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please select 0 to 3.\n");
        }

    } while (choice != 0);

    return 0;
}
