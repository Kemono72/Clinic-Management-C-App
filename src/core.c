/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  : Kemono Onomek
Student ID#: 146433230
Email      : arjoshi5@myseneca,ca
Section    : ZBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <ctype.h>
#include <string.h>

void clearInputBuffer(void)
{
	while (getchar() != '\n')
	{

	}
}

void suspend(void)
{
	printf("<ENTER> to continue...");
	clearInputBuffer();
	putchar('\n');
}

int inputInt(void)
{
	int num;
	char endline;

	do
	{
		scanf("%d%c", &num, &endline);

		if (endline != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
	} while (endline != '\n');

	return num;
}

int inputIntPositive(void)
{
	int posNum;
	char endline = ' ';

	do
	{
		scanf("%d%c", &posNum, &endline);

		if (endline != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a number: ");
		}

		if (posNum <= 0)
		{
			printf("ERROR! Value must be > 0: ");
		}
	} while (posNum <= 0);

	return posNum;
}

int inputIntRange(int lowBound, int uppBound)
{
	char endline = ' ';
	int num;

	do
	{
		scanf("%d%c", &num, &endline);

		if (endline != '\n')
		{
			clearInputBuffer();
			printf("Error! Input a whole number: ");
		}
		else if (!(num <= uppBound && num >= lowBound))
		{
			printf("ERROR! Value must be between 1 and 28 inclusive: ");
		}
	} while (!(num <= uppBound && num >= lowBound));

	return num;
}

char inputCharOption(char str[])
{
	int i, found = 0;
	char input;

	do
	{
		scanf(" %c", &input);

		for (i = 0; str[i] != '\0'; i++)
		{
			if (input == str[i])
			{
				found = 1;
				break;
			}
		}

		if (found == 0)
		{
			printf("ERROR: Character must be one of [%s]: ", str);
		}
	} while (found == 0);

	clearInputBuffer();
	return input;
}

void inputCString(char* str, int minChar, int maxChar) {
	int flag = 1;
	char char1 = 'a';

	while (flag) {
		int len = 0;
		while (char1 != '\n' && len <= maxChar) {
			char1 = getchar();
			str[len] = char1;
			len++;
		};

		if (char1 == '\n' && len <= (maxChar + 1)) {
			len--;
			str[len] = '\0';
		}
		else {
			str[maxChar] = '\0';
			clearInputBuffer();
		}

		if (minChar == maxChar && len != minChar) {
			printf("ERROR: String length must be exactly %d chars: ", minChar);
			char1 = 'a';
		}
		else if (len < minChar || len > maxChar) {
			if (len > maxChar) {
				printf("ERROR: String length must be no more than %d chars: ", maxChar);
				char1 = 'a';
			}
			else if (len < minChar) {
				printf("ERROR: String length must be between %d and %d chars: ", minChar, maxChar);
				char1 = 'a';
			}
		}
		else {
			flag = 0;
		}
	}
}


void inputCStringNumbers(char* str, int minChar, int maxChar)
{
	int flag = 1;
	char ch = 'a';

	while (flag)
	{
		int len = 0;
		while (ch != '\n' && len <= maxChar)
		{
			ch = getchar();
			str[len] = ch;
			len++;
		};

		if (ch == '\n' && len <= (maxChar + 1))
		{
			len--;
			str[len] = '\0';
		}
		else
		{
			str[maxChar] = '\0';
			clearInputBuffer();
		}

		if (minChar == maxChar && len != minChar)
		{
			printf("Invalid 10-digit number! Number: ");
			ch = 'a';
		}
		else
		{
			flag = 0;
		}
	}
}


void displayFormattedPhone(const char* str)
{
	int i = 0, phoneDigit = 0;

	while (str != NULL && str[phoneDigit] && isdigit(str[phoneDigit]))
	{
		phoneDigit++;
	}
	if (phoneDigit == 10)
	{
		printf("(");
		for (i = 0; i < 3; i++)
		{
			printf("%c", str[i]);
		}
		printf(")");
		for (; i < 6; i++)
		{
			printf("%c", str[i]);
		}
		printf("-");
		for (; i < 10; i++)
		{
			printf("%c", str[i]);
		}
	}
	else
	{
		printf("(___)___-____");
	}
}
