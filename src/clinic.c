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
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"
#include <string.h> 

void sort(struct Appointment appointment[], int max) {
    int i, j;
    struct Appointment tem;

    for (i = 0; i < max; i++) {
        appointment[i].time.minute = (appointment[i].date.year * 12 * 30 * 24 * 60) + (appointment[i].date.month * 30 * 24 * 60) + (appointment[i].date.day * 24 * 60) + (appointment[i].time.hour * 60) + appointment[i].time.minute;
    }

    for (i = max - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (appointment[j].time.minute > appointment[j + 1].time.minute) {
                tem = appointment[j];
                appointment[j] = appointment[j + 1];
                appointment[j + 1] = tem;
            }
        }
    }
   
    for (i = 0; i < max; i++) {
        appointment[i].time.minute = appointment[i].time.minute % 60; // yo chai adjust gareko
    }
}



//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int allRec)
{
    printf("Clinic Appointments for the Date: ");

    if (allRec)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
            "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
            "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient, const struct Appointment* appointment, int dateField)
{
    if (dateField)
    {
        printf("%04d-%02d-%02d ", appointment->date.year, appointment->date.month,
            appointment->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appointment->time.hour, appointment->time.minute,
        patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
            "==============================\n"
            "1) VIEW   ALL Appointments\n"
            "2) VIEW   Appointments by DATE\n"
            "3) ADD    Appointment\n"
            "4) REMOVE Appointment\n"
            "------------------------------\n"
            "0) Previous menu\n"
            "------------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


void displayAllPatients(const struct Patient patient[], int maxPatient, int fmt) {
    int i, validRec = 0;

    if (fmt == FMT_TABLE) {
        displayPatientTableHeader();
    }

    for (i = 0; i < maxPatient; i++) {
        if (patient[i].patientNumber != 0) {
            displayPatientData(&patient[i], fmt);
            validRec = 1;
        }
    }

    if (!validRec) {
        printf("*** No records found ***\n\n");
    }

    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int maxPatient) {
    int option;

    do {
        printf("Search Options\n");
        printf("==========================\n");
        printf("1) By patient number\n");
        printf("2) By phone number\n");
        printf("..........................\n");
        printf("0) Previous menu\n");
        printf("..........................\n");
        printf("Selection: ");
        scanf("%d", &option);
        printf("\n");

        if (option == 1) {
            searchPatientByPatientNumber(patient, maxPatient);
            clearInputBuffer();
            suspend();
        }
        else if (option == 2) {
            searchPatientByPhoneNumber(patient, maxPatient);
            clearInputBuffer();
            suspend();
        }
    } while (option != 0);
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max) {
    int num, patIndex, match;
    int i = 0;

    // Checking for first empty space
    do {
        match = 0;
        if (patient[i].patientNumber == 0)
        {
            match = 1;
            patIndex = i;
        }
        i++;
    } while (i < max && match == 0);

    if (match == 0)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        // Assigning the value
        num = nextPatientNumber(patient, max);
        patient[patIndex].patientNumber = num;
        inputPatient(&patient[patIndex]);
        printf("*** New patient record added ***\n\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max) {
    int patientNum, i;
    printf("Enter the patient number: ");
    scanf("%d", &patientNum);
    printf("\n");

    if (findPatientIndexByPatientNum(patientNum, patient, max) != -1) {
        i = findPatientIndexByPatientNum(patientNum, patient, max);
        menuPatientEdit(patient + i);
    }
    else {
        printf("ERROR: Patient record not found!\n");
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max) {
    int patientNum, i;
    char op, ch;
    printf("Enter the patient number: ");
    scanf("%d", &patientNum);
    printf("\n");

    i = findPatientIndexByPatientNum(patientNum, patient, max);
    if (findPatientIndexByPatientNum(patientNum, patient, max) != -1) {
        i = findPatientIndexByPatientNum(patientNum, patient, max);
        printf("Name  : %s\n", patient[i].name);
        printf("Number: %05d\n", patient[i].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[i].phone.number);
        printf(" (%s)", patient[i].phone.description);
        printf("\n\n");

        printf("Are you sure you want to remove this patient record? (y/n): ");

        int flag = 1;

        do {
            scanf(" %c%c", &op, &ch);

            if ((op == 'n' || op == 'N') && (ch == '\n')) {
                printf("Operation aborted.\n\n");
                flag = 0;
                clearInputBuffer();
            }
            else if ((op == 'y' || op == 'Y') && (ch == '\n')) {
                patient[i].patientNumber = 0;
                printf("Patient record has been removed!\n\n");
                flag = 0;
            }
            else {
                clearInputBuffer();
                printf("ERROR: Character must be one of [yn]: ");
            }
        } while (flag);
    }
    else {
        printf("ERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
}

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

void viewAllAppointments(struct ClinicData* data) {
    int i, j;

    sort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(NULL, 1);
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {
                    displayScheduleData(&data->patients[j], &data->appointments[i], 1);
                }
            }
        }
    }

    printf("\n");
}

// View appointment schedule for the user input date
// Todo:
void viewAppointmentSchedule(struct ClinicData* data) {
    int i, j;
    int end = 31;
    struct Date date;

    printf("Year        : ");
    date.year = inputIntPositive();

    printf("Month (1-12): ");
    date.month = inputIntRange(1, 12);

    printf("Day (1-");
    if (date.month == 4 || date.month == 9 || date.month == 11) {
        end = 30;
    }
    if (date.month == 2) {
        end = 28;
    }
    if (date.year % 4 == 0 && date.month == 2) {
        end = 29;
    }

    printf("%d)  : ", end);
    date.day = inputIntRange(1, end);
    printf("\n");

    sort(data->appointments, data->maxAppointments);

    displayScheduleTableHeader(&date, 0);
    for (i = 0; i < data->maxAppointments; i++) {
        for (j = 0; j < data->maxPatient; j++) {
            if (data->appointments[i].patientNumber && data->patients[j].patientNumber) {
                if (data->appointments[i].patientNumber == data->patients[j].patientNumber) {
                    if (data->appointments[i].date.year == date.year && data->appointments[i].date.month == date.month && data->appointments[i].date.day == date.day) {
                        displayScheduleData(&data->patients[j], &data->appointments[i], 0);
                    }
                }
            }
        }
    }

    printf("\n");

}
// Function to add an appointment to the appointment array
void addAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* pt, int maxPatients) {
    struct Date date;
    struct Time time;

    int endDay = 31; 
    int patientNum, i, slotTaken = 1;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    i = findPatientIndexByPatientNum(patientNum, pt, maxPatients);

    if (i >= 0) { 
        while (slotTaken) { // find avail slot
            printf("Year        : ");
            date.year = inputIntPositive();

            printf("Month (1-12): ");
            date.month = inputIntRange(1, 12);

            printf("Day (1-");
            if (date.month == 4 || date.month == 9 || date.month == 11) {
                endDay = 30;
            }
            if (date.month == 2) {
                endDay = 28;
            }
            if (date.year % 4 == 0 && date.month == 2) {
                endDay = 29;
            }
            printf("%d)  : ", endDay);
            date.day = inputIntRange(1, endDay);

            printf("Hour (0-23)  : ");
            time.hour = inputIntRange(0, 23);

            printf("Minute (0-59): ");
            time.minute = inputIntRange(0, 59);

            if (timeSlotAvailable(date, time, appointment, maxAppointments)) {
                printf("\nERROR: Appointment timeslot is not available!\n\n");
            }
            else {
                while ((time.hour < START_HOUR || time.hour > END_HOUR) || (time.hour == END_HOUR && time.minute > 0) || (time.minute % MINUTE_INTERVAL != 0)) {
                    printf("ERROR: Time must be between %02d:00 and %02d:00 in %02d minute intervals.\n\n", START_HOUR, END_HOUR, MINUTE_INTERVAL);
                    printf("Hour (0-23)  : ");
                    time.hour = inputIntRange(0, 23);
                    printf("Minute (0-59): ");
                    time.minute = inputIntRange(0, 59);
                }
                slotTaken = 0;
            }
        }

        i = nextSlotAvailable(appointment, maxAppointments);
        appointment[i].date = date;
        appointment[i].time = time;
        appointment[i].patientNumber = patientNum;
        printf("\n*** Appointment scheduled! ***\n\n");
    }
    else {
        printf("\nERROR: Patient record not found!\n\n");
    }
    return;
}

// Function to remove an appointment from the appointment array
// Todo:
void removeAppointment(struct Appointment* appointment, int maxAppointments, struct Patient* pt, int maxPatients) {
    struct Date date;
    int i, patientNum, endDay = 0, apptIndex;

    printf("Patient Number: ");
    patientNum = inputIntPositive();
    i = findPatientIndexByPatientNum(patientNum, pt, maxPatients);

    if (i >= 0) { 
        printf("Year        : ");
        date.year = inputIntPositive();

        printf("Month (1-12): ");
        date.month = inputIntRange(1, 12);

        printf("Day (1-");
        if (date.month == 4 || date.month == 9 || date.month == 11) {
            endDay = 30;
        }
        if (date.month == 2) {
            endDay = 28;
        }
        if (date.year % 4 == 0 && date.month == 2) {
            endDay = 29;
        }
        printf("%d)  : ", endDay);
        date.day = inputIntRange(1, endDay);

        apptIndex = validAppointment(patientNum, date, appointment, maxAppointments);

        if (apptIndex >= 0) { 
            printf("\n");

            displayPatientData(&pt[i], FMT_FORM);
            printf("Are you sure you want to remove this appointment (y,n): ");

            if (inputCharOption("yn") == 'y') {
                appointment[apptIndex].patientNumber = 0; 
                printf("\nAppointment record has been removed!\n\n"); 
            }
            else {
                printf("ERROR: No appointment for this date!\n\n");
            }
        }
    }
    else {
        // If the patient was not found
        printf("ERROR: Patient record not found!\n\n");
    }
}


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
// (Copy your code from MS#2)
void searchPatientByPatientNumber(const struct Patient patient[], int max) {
    int patNum, i;
    printf("Search by patient number: ");
    scanf("%d", &patNum);
    printf("\n");

    // Checking if patient number exists
    if (findPatientIndexByPatientNum(patNum, patient, max) != -1) {
        i = findPatientIndexByPatientNum(patNum, patient, max);
        printf("Name  : %s\n", patient[i].name);
        printf("Number: %05d\n", patient[i].patientNumber);
        printf("Phone : ");
        displayFormattedPhone(patient[i].phone.number);
        printf(" (%s)", patient[i].phone.description);
        printf("\n\n");
    }

    else {
        printf("*** No records found ***\n\n");
    }
}

// Search and display patient records by phone number (tabular)
// (Copy your code from MS#2)
void searchPatientByPhoneNumber(const struct Patient patient[], int max) {
    int i, match = 0;
    char phoneNum[PHONE_LEN + 1];
    clearInputBuffer();
    printf("Search by phone number: ");
    fgets(phoneNum, sizeof(phoneNum), stdin);
    printf("\n");

    displayPatientTableHeader();

    for (i = 0; i < max + 1; i++) {
        if (strcmp(patient[i].phone.number, phoneNum) == 0) {
            printf("%05d %-15s ", patient[i].patientNumber, patient[i].name);
            displayFormattedPhone(patient[i].phone.number);
            printf(" (%s)\n", patient[i].phone.description);
            match++;
        }
    }
    printf("\n");

    if (match == 0) {
        printf("*** No records found ***\n\n");
    }
}

// Get the next highest patient number
// (Copy your code from MS#2)
int nextPatientNumber(const struct Patient patient[], int max) {
    int nextNum, maxNum = patient[0].patientNumber, i;

    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber > maxNum) {
            maxNum = patient[i].patientNumber;
        }
    }

    nextNum = maxNum + 1;
    return nextNum;
}

// Find the patient array index by patient number (returns -1 if not found)
// (Copy your code from MS#2)
int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max) {
    int i;
    for (i = 0; i < max; i++) {
        if (patient[i].patientNumber == patientNumber) {
            return i;
        }
    }
    return -1;
}

// Checks to see whether a time slot is available
int timeSlotAvailable(struct Date date, struct Time time, struct Appointment* appointment, int maxAppointments) {
    int i, slotAvailable = 0;

    for (i = 0; i < maxAppointments; i++) {
        if (date.year == appointment[i].date.year && date.month == appointment[i].date.month && date.day == appointment[i].date.day && time.hour == appointment[i].time.hour && time.minute == appointment[i].time.minute) {
            slotAvailable = 1;
        }
    }

    return slotAvailable;
}

// Checks to see which is the next slot that is available and return the index
int nextSlotAvailable(struct Appointment* appointment, int maxAppointments) {
    int i = 0, available = 0;
    while (available == 0 && i < maxAppointments) {
        if (appointment[i].patientNumber < 1) {
            available = 1;
        }
        i++;
    }
    return i;
}

// Checks to see if an appointment is valid
int validAppointment(int patientNumber, struct Date date, struct Appointment* appointment, int maxAppointments) {
    int i = 0, valid = 0;

    while (valid == 0 && i < maxAppointments)
    {
        if ((appointment[i].patientNumber == patientNumber) && (appointment[i].date.day == date.day) && (appointment[i].date.month == date.month) && (appointment[i].date.year == date.year)) {
            valid = 1;
        }
        i++;
    }
    return i - 1;
}

// Get user input for a new patient record
void inputPatient(struct Patient* patient) {
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

// Get user input for phone contact information
// (Copy your code from MS#2)
void inputPhoneData(struct Phone* phone) {
    int op;
    char inputNum[PHONE_LEN + 1];
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    op = inputIntRange(1, 4);
    putchar('\n');

    switch (op)
    {
    case 1:
        strncpy(phone->description, "CELL", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringNumbers(inputNum, 10, 10);
        strcpy(phone->number, inputNum);
        putchar('\n');

        break;

    case 2:
        strncpy(phone->description, "HOME", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringNumbers(inputNum, 10, 10);
        strcpy(phone->number, inputNum);
        putchar('\n');

        break;

    case 3:
        strncpy(phone->description, "WORK", PHONE_DESC_LEN);
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCStringNumbers(inputNum, 10, 10);
        strcpy(phone->number, inputNum);
        putchar('\n');

        break;

    case 4:
        strncpy(phone->description, "TBD", PHONE_DESC_LEN);
        *phone->number = '\0';
        break;
    }
}



//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

int importPatients(const char* datafile, struct Patient patients[], int max) {
    int i = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL) {
        i = 0;
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[i].patientNumber,
            patients[i].name,
            patients[i].phone.description,
            patients[i].phone.number) != EOF)
        {
            i++;
            if (i >= max)
                break;
        }


        fclose(fp);
    }

    else {
        printf("ERROR: File could not be read\n");
    }

    return i;
}

// Import appointment data from file into an Appointment array (returns # of records read)
// ToDo:
int importAppointments(const char* datafile, struct Appointment appointment[], int max) {

    int i, count = 0;

    FILE* fp;
    fp = fopen(datafile, "r");

    if (fp != NULL) {

        for (i = 0; i < max && !feof(fp); i++) {
            fscanf(fp, "%d,%d,%d,%d,%d,%d", &appointment[i].patientNumber, &appointment[i].date.year, &appointment[i].date.month, &appointment[i].date.day, &appointment[i].time.hour, &appointment[i].time.minute);

            if (!feof(fp)) {
                count++;
            }
        }

        fclose(fp);
    }

    else {
        printf("ERROR: File could not be read\n");
    }

    return count;
}
