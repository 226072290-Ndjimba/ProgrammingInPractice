
#include <stdio.h>
#include <string.h>
#include "utilities.h"

void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        /* Discard leftover input. */
    }
}

int readInt(const char *prompt, int *value)
{
    int result;

    printf("%s", prompt);
    result = scanf("%d", value);

    if (result != 1)
    {
        clearInputBuffer();
        printf("Invalid input. Please enter a whole number.\n");
        return 0;
    }

    clearInputBuffer();
    return 1;
}

int readDouble(const char *prompt, double *value)
{
    int result;

    printf("%s", prompt);
    result = scanf("%lf", value);

    if (result != 1)
    {
        clearInputBuffer();
        printf("Invalid input. Please enter a number.\n");
        return 0;
    }

    clearInputBuffer();

    if (*value < 0)
    {
        printf("Amount cannot be negative.\n");
        return 0;
    }

    return 1;
}

int readString(const char *prompt, char *text, int size)
{
    size_t length;

    printf("%s", prompt);

    if (fgets(text, size, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(text);

    if (length > 0 && text[length - 1] == '\n')
    {
        text[length - 1] = '\0';
    }
    else
    {
        clearInputBuffer();
    }

    if (text[0] == '\0')
    {
        printf("Input cannot be empty.\n");
        return 0;
    }

    return 1;
}
