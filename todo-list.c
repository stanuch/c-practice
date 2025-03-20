#include <stdio.h>
#include <stdlib.h> // potrzebne do czyszczenia konsoli - system("clear")
#include <string.h> // potrzebne do uzycia funkcji strlen()

typedef struct
{
    char opis[50];
} Task;

Task zadania[50];

int zliczenia = 0;
int *pZliczenia = &zliczenia;

void addTask(Task zadania[], int *pZliczenia)
{
    if (*pZliczenia >= 50)
    {
        printf("\nLista zadań jest pełna.\n");
        return;
    }

    printf("Wprowadź zadanie: ");
    fgets(zadania[*pZliczenia].opis, 50, stdin);

    while (strlen(zadania[*pZliczenia].opis) < 2)
    {
        printf("\nNie wprowadzono zadnego tekstu.\nSprobuj ponownie.\n\n");
        printf("Wprowadź zadanie: ");
        fgets(zadania[*pZliczenia].opis, 50, stdin);
    }

    (*pZliczenia)++;

    printf("\nZadanie dodane.\n\n");
}

void showTasks()
{
    if (*pZliczenia == 0)
    {
        printf("Brak zadań do wyświetlenia.\n");
        return;
    }

    printf("Moja lista zadań:\n");

    for (int i = 0; i < *pZliczenia; i++)
    {
        printf("%d. %s", i + 1, zadania[i].opis);
    }
}

void finishTask(Task tasks[], int *pZliczenia)
{
    int numer_zadania;

    if (*pZliczenia == 0)
    {
        printf("Nie masz zadnych zadań do zakończenia.\n");

        printf("\nNaciśnij ENTER aby kontynuować...");
        while (getchar() != '\n')
            ;
        system("clear");
        return;
    }

    showTasks();
    printf("\nWprowadź numer zadania ktore chcesz zakończyć: ");
    scanf("%d", &numer_zadania);

    if (numer_zadania < 1 || numer_zadania > *pZliczenia)
    {
        printf("Nieprawidłowy numer zadania.\n");
        return;
    }

    for (int i = numer_zadania - 1; i < *pZliczenia - 1; i++)
    {
        tasks[i] = tasks[i + 1];
    }
    (*pZliczenia)--;
}

void exportTasks(Task zadania[], int zliczenia)
{
    FILE *file = fopen("lista_zadan.txt", "w");

    for (int i = 0; i < zliczenia; i++)
    {
        fprintf(file, "%d. %s", i + 1, zadania[i].opis);
    }

    fclose(file);
    printf("\nZadania zapisane do pliku tekstowego.\n\n");
}

int main()
{
    int choice;
    zliczenia = 0;
    system("clear");

    while (1)
    {
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~ To-Do List by Aleksander Stanuch ~~~~~~~~~~~~~~\n");
        printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("1. Dodaj zadanie\n");
        printf("2. Ukończ zadanie\n");
        printf("3. Wyświetl wszystkie zadania\n");
        printf("4. Zapisz zadania do pliku tekstowego\n");
        printf("5. Wyjście\n");
        printf("\nWybierz opcję: ");
        scanf("%d", &choice);

        while (getchar() != '\n')
            ;

        if (choice == 1)
        {
            addTask(zadania, pZliczenia);
            printf("Naciśnij ENTER aby kontynuować...");
            while (getchar() != '\n')
                ;
            system("clear");
        }
        else if (choice == 2)
        {
            system("clear");
            finishTask(zadania, pZliczenia);
            system("clear");
        }
        else if (choice == 3)
        {
            system("clear");
            showTasks();
            printf("\nNaciśnij ENTER aby kontynuować...");
            while (getchar() != '\n')
                ;
            system("clear");
        }
        else if (choice == 4)
        {
            exportTasks(zadania, zliczenia);
            printf("Naciśnij ENTER aby kontynuować...");
            while (getchar() != '\n')
                ;
            system("clear");
        }
        else if (choice == 5)
        {
            break;
        }
        else
        {
            printf("Nieprawidłowa opcja. Naciśnij ENTER aby wrocić do menu.\n\n");
            while (getchar() != '\n')
                ;
            system("clear");
        }
    }
}