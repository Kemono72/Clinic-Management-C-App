/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

// SAFE-GUARD: 
#ifndef CORE_H
#define CORE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void clearInputBuffer(void);
void suspend(void);
int inputInt(void);
int inputIntPositive(void);
int inputIntRange(int lowBound, int uppBound);
char inputCharOption(char str[]);
void inputCString(char* str, int minChar, int maxChar);
void displayFormattedPhone(const char* str);

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

void clearInputBuffer(void);

void suspend(void);

int inputInt(void);

int inputIntPositive(void);

int inputIntRange(int lowerBound, int upperBound);

char inputCharOption(char str[]);

void inputCStringNumbers(char* str, int minChar, int maxChar);

void inputCString(char* str, int minChar, int maxChar);

void displayFormattedPhone(const char* str);
#endif // !CORE_H
