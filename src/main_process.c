#include <stdio.h>
#include "pensioner.h"

#define RETIREMENT_AGE 60
#define MIN_PENSION_YEARS 5

int main() {
    Pensioner pensioners[MAX_PENSIONERS];
    Pensioner result[MAX_PENSIONERS];
    int count, resultCount;

    printf("=== ОБРАБОТКА ДАННЫХ О ПЕНСИОНЕРАХ ===\n");

    count = readPensionersFromFile("data/pensioners.txt", pensioners, MAX_PENSIONERS);
    if (count == 0) {
        printf("Нет данных. Сначала создайте файл: ./program_create\n");
        return 1;
    }

    printf("Прочитано записей: %d\n", count);

    findPensionersWithLongService(pensioners, count, RETIREMENT_AGE, MIN_PENSION_YEARS, result, &resultCount);

    if (resultCount > 0) {
        printf("Найдено пенсионеров со стажем > 5 лет: %d\n", resultCount);
        
        for (int i = 0; i < resultCount; i++) {
            int years = calculatePensionYears(result[i].birthDate, RETIREMENT_AGE);
            printf("%d. %s %s %s - стаж %d лет\n",
                   i + 1,
                   result[i].lastName,
                   result[i].firstName,
                   result[i].patronymic,
                   years);
        }

        writePensionersToFile("data/result.txt", result, resultCount);
        printf("Результаты сохранены в data/result.txt\n");
    } else {
        printf("Пенсионеров со стажем > 5 лет не найдено\n");
    }

    return 0;
}

