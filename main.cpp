#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENTRIES 100


struct DiaryEntry {
    char date[20];
    char content[500];
};

void addEntry(struct DiaryEntry *diary, int *entryCount) {
    if (*entryCount < MAX_ENTRIES) {
        printf("Enter date (DD/MM/YYYY): ");
        scanf("%s", diary[*entryCount].date);

        printf("Enter diary content (max 500 characters):\n");
        scanf(" %[^\n]", diary[*entryCount].content);

        (*entryCount)++;

        printf("Entry added successfully!\n");
    } else {
        printf("Diary is full. Cannot add more entries.\n");
    }
}


void viewEntries(struct DiaryEntry *diary, int entryCount) {
    if (entryCount == 0) {
        printf("No entries found.\n");
    } else {
        printf("Diary Entries:\n");
        for (int i = 0; i < entryCount; i++) {
            printf("Date: %s\n", diary[i].date);
            printf("Content: %s\n", diary[i].content);
            printf("--------------------\n");
        }
    }
}


void saveEntriesToFile(struct DiaryEntry *diary, int entryCount, const char *filename) {
    FILE *file = fopen(filename, "w");

    if (file != NULL) {
        for (int i = 0; i < entryCount; i++) {
            fprintf(file, "%s,%s\n", diary[i].date, diary[i].content);
        }

        fclose(file);

        printf("Diary entries saved to %s\n", filename);
    } else {
        printf("Error opening file for writing.\n");
    }
}


int loadEntriesFromFile(struct DiaryEntry *diary, int *entryCount, const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file != NULL) {
        while (fscanf(file, "%19[^,],%499[^\n]\n", diary[*entryCount].date, diary[*entryCount].content) == 2) {
            (*entryCount)++;
            if (*entryCount >= MAX_ENTRIES) {
                printf("Diary is full. Some entries might not be loaded.\n");
                break;
            }
        }

        fclose(file);

        printf("Diary entries loaded from %s\n", filename);

        return 1; 
    } else {
        printf("Error opening file for reading. Creating a new diary.\n");
        return 0; 
    }
}

void deleteEntry(struct DiaryEntry *diary, int *entryCount) {
    char targetDate[20];
    int foundIndex = -1;

    if (*entryCount == 0) {
        printf("No entries to delete.\n");
        return;
    }

    printf("Enter the date of the entry to delete (DD/MM/YYYY): ");
    scanf("%s", targetDate);

    
    for (int i = 0; i < *entryCount; i++) {
        if (strcmp(diary[i].date, targetDate) == 0) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        
        for (int i = foundIndex; i < *entryCount - 1; i++) {
            diary[i] = diary[i + 1];
        }

        (*entryCount)--;
        printf("Entry deleted successfully!\n");
    } else {
        printf("Entry with date %s not found.\n", targetDate);
    }
}

int main() {
    int option;
    int entryCount = 0;
    struct DiaryEntry diary[MAX_ENTRIES];
    const char *filename = "diary_entries.txt";

    
    int loadSuccess = loadEntriesFromFile(diary, &entryCount, filename);

    do {
        printf("Diary Management System\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Save Entries\n");
        printf("4. Delete Entry\n");
        printf("5. Exit\n");
        printf("Select option: ");
        scanf("%d", &option);

        

        switch (option) {
            case 1:
                addEntry(diary, &entryCount);
                break;
            case 2:
                viewEntries(diary, entryCount);
                break;
            case 3:
                saveEntriesToFile(diary, entryCount, filename);
                break;
            case 4:
                deleteEntry(diary, &entryCount);
                break;
            case 5:
                printf("Exiting Diary Management System. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }

    } while (option != 5);


    if (loadSuccess) {
        saveEntriesToFile(diary, entryCount, filename);
    }

    return 0;
}




