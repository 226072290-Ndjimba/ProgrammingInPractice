
#include <stdio.h>
#include "employees.h"
#include "utilities.h"

static int employeeCount = 0;

static int employeeIDs[MAX_EMPLOYEES];
static char employeeNames[MAX_EMPLOYEES][EMPLOYEE_NAME_LENGTH];
static char employeeDepartments[MAX_EMPLOYEES][EMPLOYEE_DEPT_LENGTH];

void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("Employee storage is full.\n");
        return;
    }

    if (!readInt("Enter employee ID: ", &id))
    {
        return;
    }

    if (id <= 0)
    {
        printf("Employee ID must be positive.\n");
        return;
    }

    for (int i = 0; i < employeeCount; i++)
    {
        if (employeeIDs[i] == id)
        {
            printf("That employee ID already exists.\n");
            return;
        }
    }

    employeeIDs[employeeCount] = id;

    if (!readString("Enter employee name: ",
                    employeeNames[employeeCount],
                    EMPLOYEE_NAME_LENGTH))
    {
        return;
    }

    if (!readString("Enter department: ",
                    employeeDepartments[employeeCount],
                    EMPLOYEE_DEPT_LENGTH))
    {
        return;
    }

    employeeCount++;

    printf("Employee added successfully.\n");
}

void displayEmployees(void)
{
    if (employeeCount == 0)
    {
        printf("No employees have been recorded.\n");
        return;
    }

    printf("\n%-10s %-30s %-20s\n",
           "ID", "Employee Name", "Department");

    printf("--------------------------------------------------------------\n");

    for (int i = 0; i < employeeCount; i++)
    {
        printf("%-10d %-30s %-20s\n",
               employeeIDs[i],
               employeeNames[i],
               employeeDepartments[i]);
    }
}

int getEmployeeCount(void)
{
    return employeeCount;
}

void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n========== EMPLOYEE MANAGEMENT ==========\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("0. Back to Main Menu\n");

        if (!readInt("Enter your choice: ", &choice))
        {
            continue;
        }

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 0:
                printf("Returning to the main menu...\n");
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }

    } while (choice != 0);
}
