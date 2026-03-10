#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pensioner.h"

int createDataFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) return 0;

    fprintf(file, "Иванов;Иван;Иванович;M;русский;1950;5;15;+375291234567;220001;Беларусь;Минская;Минский;Минск;Ленина;10;25\n");
    fprintf(file, "Петров;Петр;Петрович;M;русский;1945;3;10;+375292345678;220002;Беларусь;Минская;Минский;Минск;Скорины;15;30\n");
    fprintf(file, "Сидорова;Анна;Ивановна;F;русская;1960;8;20;+375293456789;220003;Беларусь;Минская;Минский;Минск;Пушкина;5;12\n");
    fprintf(file, "Козлова;Мария;Петровна;F;белоруска;1940;12;5;+375294567890;220004;Беларусь;Минская;Минский;Минск;Гагарина;20;7\n");
    fprintf(file, "Новиков;Сергей;Сергеевич;M;белорус;1935;7;18;+375295678901;220005;Беларусь;Минская;Минский;Минск;Купалы;8;14\n");

    fclose(file);
    return 1;
}

int readPensionersFromFile(const char *filename, Pensioner *persons, int maxCount) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    int count = 0;
    char line[512];

    while (count < maxCount && fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        sscanf(line, "%[^;];%[^;];%[^;];%c;%[^;];%d;%d;%d;%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d",
               persons[count].lastName,
               persons[count].firstName,
               persons[count].patronymic,
               &persons[count].gender,
               persons[count].nationality,
               &persons[count].birthDate.year,
               &persons[count].birthDate.month,
               &persons[count].birthDate.day,
               persons[count].phone,
               persons[count].homeAddress.postalCode,
               persons[count].homeAddress.country,
               persons[count].homeAddress.region,
               persons[count].homeAddress.district,
               persons[count].homeAddress.city,
               persons[count].homeAddress.street,
               &persons[count].homeAddress.house,
               &persons[count].homeAddress.apartment);
        count++;
    }

    fclose(file);
    return count;
}

void writePensionersToFile(const char *filename, Pensioner *persons, int count) {
    FILE *file = fopen(filename, "w");
    if (!file) return;

    fprintf(file, "Пенсионеры со стажем более 5 лет:\n");
    fprintf(file, "===================================\n\n");

    for (int i = 0; i < count; i++) {
        fprintf(file, "ФИО: %s %s %s\n", persons[i].lastName, persons[i].firstName, persons[i].patronymic);
        fprintf(file, "Дата рождения: %d-%02d-%02d\n",
                persons[i].birthDate.year,
                persons[i].birthDate.month,
                persons[i].birthDate.day);
        fprintf(file, "Телефон: %s\n", persons[i].phone);
        fprintf(file, "Адрес: %s, %s, ул.%s д.%d кв.%d\n",
                persons[i].homeAddress.city,
                persons[i].homeAddress.street,
                persons[i].homeAddress.street,
                persons[i].homeAddress.house,
                persons[i].homeAddress.apartment);
        fprintf(file, "-----------------------------------\n");
    }

    fclose(file);
}

int calculateAge(Date birthDate) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int currentYear = tm.tm_year + 1900;
    int currentMonth = tm.tm_mon + 1;
    int currentDay = tm.tm_mday;

    int age = currentYear - birthDate.year;
    if (currentMonth < birthDate.month ||
        (currentMonth == birthDate.month && currentDay < birthDate.day)) {
        age--;
    }
    return age;
}

int calculatePensionYears(Date birthDate, int retirementAge) {
    int age = calculateAge(birthDate);
    return (age > retirementAge) ? (age - retirementAge) : 0;
}

void findPensionersWithLongService(Pensioner *persons, int count, int retirementAge, int minYears, Pensioner *result, int *resultCount) {
    *resultCount = 0;
    for (int i = 0; i < count; i++) {
        int years = calculatePensionYears(persons[i].birthDate, retirementAge);
        if (years > minYears) {
            result[*resultCount] = persons[i];
            (*resultCount)++;
        }
    }
}
