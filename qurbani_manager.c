// Eid ul-Adha Qurbani & Charity Manager

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX 100
#define MEAT_PER_COW 100
#define MEAT_PER_GOAT 25
#define MEAT_PER_CAMEL 150
#define MEAT_FOR_POOR_PER_FAMILY 5

HANDLE hConsole;

typedef struct {
    char name[50];
    int oxes;
    int goats;
    int camels;
    float meatSum;
    float poorpart;
    float ownpart;
    float relativespart;
} FamilyInfo;

FamilyInfo allFam[MAX];
int howmanyfamilies = 0;

void delay_print(const char *text, int delay_ms) {
    while (*text) {
        putchar(*text++);
        fflush(stdout);
        Sleep(delay_ms);
    }
}

void blinking_prompt(const char *prompt, int times, int delay_ms) {
    for (int i = 0; i < times; i++) {
        printf("\r%s", prompt);
        fflush(stdout);
        Sleep(delay_ms);
        printf("\r%*s", (int)strlen(prompt), " ");
        fflush(stdout);
        Sleep(delay_ms);
    }
    printf("\r%s", prompt);
    fflush(stdout);
}

void getfaminfo() {
    SetConsoleTextAttribute(hConsole, 14);
    printf("\nEnter number of houses to input: ");
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("\nFamily Information #%d\n", i + 1);
        printf("Name: ");
        scanf("%s", allFam[i].name);
        printf("Oxes: ");
        scanf("%d", &allFam[i].oxes);
        printf("Goats: ");
        scanf("%d", &allFam[i].goats);
        printf("Camels: ");
        scanf("%d", &allFam[i].camels);
        howmanyfamilies++;
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void calcmeat() {
    for (int i = 0; i < howmanyfamilies; i++) {
        float total = allFam[i].oxes * MEAT_PER_COW +
                      allFam[i].goats * MEAT_PER_GOAT +
                      allFam[i].camels * MEAT_PER_CAMEL;
        allFam[i].meatSum = total;
        allFam[i].poorpart = total / 3;
        allFam[i].ownpart = total / 3;
        allFam[i].relativespart = total / 3;
    }
    SetConsoleTextAttribute(hConsole, 10);
    delay_print("\nMeat distribution calculated!\n", 30);
    Beep(1000, 200);
    SetConsoleTextAttribute(hConsole, 7);
}

void showall() {
    SetConsoleTextAttribute(hConsole, 11);
    printf("\n%-15s %-5s %-5s %-5s %-10s %-10s\n", "Name", "O", "G", "Cm", "Total(kg)", "Poor(kg)");
    for (int i = 0; i < howmanyfamilies; i++) {
        printf("%-15s %-5d %-5d %-5d %-10.2f %-10.2f\n",
            allFam[i].name, allFam[i].oxes, allFam[i].goats, allFam[i].camels,
            allFam[i].meatSum, allFam[i].poorpart);
    }
    SetConsoleTextAttribute(hConsole, 7);
}

void guesspoorhelped() {
    float totalPoorMeat = 0;
    for (int i = 0; i < howmanyfamilies; i++) {
        totalPoorMeat += allFam[i].poorpart;
    }
    int allFamHelped = totalPoorMeat / MEAT_FOR_POOR_PER_FAMILY;
    SetConsoleTextAttribute(hConsole, 13);
    printf("\nTotal meat for poor: %.2f kg\n", totalPoorMeat);
    printf("Estimated number of poor families helped: %d\n", allFamHelped);
    Beep(900, 200);
    SetConsoleTextAttribute(hConsole, 7);
}

void savetofile(const char *filename) {
    FILE *fp = fopen(filename, "w");
    if (fp==NULL) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("Failed to open file!\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }
    fprintf(fp, "%d\n", howmanyfamilies);
    for (int i = 0; i < howmanyfamilies; i++) {
        fprintf(fp, "%s %d %d %d %.2f\n",
            allFam[i].name, allFam[i].oxes, allFam[i].goats,
            allFam[i].camels, allFam[i].meatSum);
    }
    fclose(fp);
    SetConsoleTextAttribute(hConsole, 10);
    delay_print("Data saved successfully!\n", 30);
    Beep(700, 200);
    SetConsoleTextAttribute(hConsole, 7);
}

void loadfromfile(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp==NULL) {
        SetConsoleTextAttribute(hConsole, 12);
        printf("File not found.\n");
        SetConsoleTextAttribute(hConsole, 7);
        return;
    }
    fscanf(fp, "%d\n", &howmanyfamilies);
    for (int i = 0; i < howmanyfamilies; i++) {
        fscanf(fp, "%s %d %d %d %f\n",
            allFam[i].name, &allFam[i].oxes, &allFam[i].goats,
            &allFam[i].camels, &allFam[i].meatSum);
        allFam[i].poorpart = allFam[i].meatSum / 3;
        allFam[i].ownpart = allFam[i].meatSum / 3;
        allFam[i].relativespart = allFam[i].meatSum / 3;
    }
    fclose(fp);
    SetConsoleTextAttribute(hConsole, 14);
    delay_print("Data loaded successfully!\n", 30);
    Beep(600, 200);
    SetConsoleTextAttribute(hConsole, 7);
}

void findfamily() {
    char target[50];
    printf("Enter house name to search: ");
    scanf("%s", target);
    int found = 0;
    for (int i = 0; i < howmanyfamilies; i++) {
        if (strcmp(allFam[i].name, target) == 0) {
            found = 1;
            printf("\nFound: %s - Cow: %d, Goat: %d, Camel: %d, Total: %.2f kg\n",
                   allFam[i].name, allFam[i].oxes, allFam[i].goats,
                   allFam[i].camels, allFam[i].meatSum);
            break;
        }
    }
    if (!found) {
        printf("Family Information not found.\n");
    }
}

void drawbars() {
    printf("\nMeat Contribution (in kg):\n");
    for (int i = 0; i < howmanyfamilies; i++) {
        printf("%-12s | ", allFam[i].name);
        int bars = allFam[i].meatSum / 5;
        for (int j = 0; j < bars; j++) printf("#");
        printf(" %.2f kg\n", allFam[i].meatSum);
    }
}

void fullsocietyinfo() {
    float meatSum = 0, totalPoor = 0, totalFamily = 0, totalRelatives = 0;
    for (int i = 0; i < howmanyfamilies; i++) {
        meatSum += allFam[i].meatSum;
        totalPoor += allFam[i].poorpart;
        totalFamily += allFam[i].ownpart;
        totalRelatives += allFam[i].relativespart;
    }
    printf("\nCommunity Total Meat: %.2f kg\n", meatSum);
    printf("For Poor: %.2f kg\nFor Own Family: %.2f kg\nFor Relatives: %.2f kg\n",
           totalPoor, totalFamily, totalRelatives);
}

void noqurbanifamily() {
    printf("\nFamilies that gave nothing:\n");
    int found = 0;
    for (int i = 0; i < howmanyfamilies; i++) {
        if (allFam[i].oxes == 0 && allFam[i].goats == 0 && allFam[i].camels == 0) {
            printf(" %s\n", allFam[i].name);
            found = 1;
        }
    }
    if (!found) printf("Everyone contributed.\n");
}

void showbig_givers() {
    for (int i = 0; i < howmanyfamilies - 1; i++) {
        for (int j = i + 1; j < howmanyfamilies; j++) {
            if (allFam[j].meatSum > allFam[i].meatSum) {
                FamilyInfo temp = allFam[i];
                allFam[i] = allFam[j];
                allFam[j] = temp;
            }
        }
    }
    printf("\nSorted by total meat contribution:\n");
    showall();
}


int main() {
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int choice;
    do {
        SetConsoleTextAttribute(hConsole, 11);
        delay_print("\n=== Eid ul-Adha Qurbani & Charity Manager ===\n", 20);
        SetConsoleTextAttribute(hConsole, 9);
        printf("1. Input Family Information Data\n");
        printf("2. Calculate Meat Distribution\n");
        printf("3. Show Summary\n");
        printf("4. Estimate Poor Families helped\n");
        printf("5. Save Data to File\n");
        printf("6. Load Previous Year Data\n");
        printf("7. Search Family Information by Name\n");
        printf("8. Sort by Meat Contribution\n");
        printf("9. Show Meat Bar Graph\n");
        printf("10. Community Summary\n");
        printf("11. Show Non-Contributors\n");
        printf("12. Exit\n");

        SetConsoleTextAttribute(hConsole, 14);
        blinking_prompt("Choose an option: ", 2, 300);
        scanf("%d", &choice);
        SetConsoleTextAttribute(hConsole, 7);
        Beep(800, 150);

        switch (choice) {
            case 1: getfaminfo(); break;
            case 2: calcmeat(); break;
            case 3: showall(); break;
            case 4: guesspoorhelped(); break;
            case 5: savetofile("this_year.txt"); break;
            case 6: loadfromfile("last_year.txt"); break;
            case 7: findfamily(); break;
            case 8: showbig_givers(); break;
            case 9: drawbars(); break;
            case 10: fullsocietyinfo(); break;
            case 11: noqurbanifamily(); break;
            case 12:
                SetConsoleTextAttribute(hConsole, 12);
                delay_print("Exiting...\n", 50);
                Beep(500, 300);
                break;
            default:
                SetConsoleTextAttribute(hConsole, 12);
                delay_print("Invalid option. Try again.\n", 30);
                Beep(400, 200);
                SetConsoleTextAttribute(hConsole, 7);
        }
    } while (choice != 12);

    return 0;
}
