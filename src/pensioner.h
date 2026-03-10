#ifndef PENSIONER_H
#define PENSIONER_H

#define MAX_STRING 100
#define MAX_PENSIONERS 50

typedef struct {
    int year;
    int month;
    int day;
} Date;

typedef struct {
    char postalCode[20];
    char country[MAX_STRING];
    char region[MAX_STRING];
    char district[MAX_STRING];
    char city[MAX_STRING];
    char street[MAX_STRING];
    int house;
    int apartment;
} Address;

typedef struct {
    char lastName[MAX_STRING];
    char firstName[MAX_STRING];
    char patronymic[MAX_STRING];
    char gender;
    char nationality[MAX_STRING];
    Date birthDate;
    char phone[20];
    Address homeAddress;
} Pensioner;

int createDataFile(const char *filename);
int readPensionersFromFile(const char *filename, Pensioner *persons, int maxCount);
void writePensionersToFile(const char *filename, Pensioner *persons, int count);
int calculateAge(Date birthDate);
int calculatePensionYears(Date birthDate, int retirementAge);
void findPensionersWithLongService(Pensioner *persons, int count, int retirementAge, int minYears, Pensioner *result, int *resultCount);

#endif
