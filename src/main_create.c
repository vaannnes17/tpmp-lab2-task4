#include <stdio.h>
#include "pensioner.h"

int main() {
    printf("=== СОЗДАНИЕ ФАЙЛА С ДАННЫМИ О ПЕНСИОНЕРАХ ===\n");
    
    if (createDataFile("data/pensioners.txt")) {
        printf("Файл data/pensioners.txt создан успешно\n");
    } else {
        printf("Ошибка при создании файла\n");
    }
    
    return 0;
}
