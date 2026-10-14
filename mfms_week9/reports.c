
#include <stdio.h>

#include "reports.h"
#include "employees.h"
#include "budget.h"

void displayBudgetReport(void)
{
    printf("\n");
    printf("============================================\n");
    printf("       MUNICIPAL FINANCIAL REPORT\n");
    printf("============================================\n");

    printf("Total employees: %d\n", getEmployeeCount());
    printf("Total departments: %d\n", getDepartmentCount());

    printf("--------------------------------------------\n");
    printf("Total allocated budget: %.2f\n", getTotalAllocated());
    printf("Total expenditure:      %.2f\n", getTotalExpenditure());
    printf("Total remaining budget: %.2f\n", getTotalRemaining());

    printf("--------------------------------------------\n");
    printf("Departments over budget: %d\n",
           countExceededDepartments());

    printf("============================================\n");
}
