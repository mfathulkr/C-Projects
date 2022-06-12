#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id; // film id
    char name[20]; // film name
    char format[5]; // format of film = 3d or 2d
    char showDate[20]; //show date of film
    char showTime[20]; // show time
    int price; // ticket price
    int capacity; // remain capacity of the saloon
}filmData;

void showRecords(FILE *filePtr);

int updateCapacity(FILE *filePtr, unsigned int id, int newCapacity);
int addFilm(FILE *filePtr, unsigned int id, char name[20], char format[5], char showDate[20], char showTime[20], int price, int capacity);
int deleteFilm(FILE *filePtr, unsigned int id);
int showLowPriced2DFilms(FILE *filePtr, int maxPrice);

int main()
{
    unsigned int id;
    int newCapacity;
    int status;

    char name[20];
    char format[5];
    char showDate[20];
    char showTime[20];
    int price;
    int capacity;

    int count;
    int maxPrice;

    FILE *filePtr;
    filePtr = fopen("films.bin","rb+");
    if (filePtr == NULL)
    {
        printf("Could not open films.bin");
        return;
    }

    showRecords(filePtr);

    int choice;

    printf("\nWhich operation do you choose?\n");
    printf("1 : Update Capacity\n");
    printf("2 : Add Film\n");
    printf("3 : Delete Film\n");
    printf("4 : Show Low-priced 2D Films\n");
    printf("> ");
    scanf("%d",&choice);

    switch (choice)
    {
    case 1:
        printf("\nFilm id: ");
        scanf("%d",&id);
        printf("New capacity: ");
        scanf("%d",&newCapacity);
        status = updateCapacity(filePtr, id, newCapacity);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No film with id %d\n", id);
        break;
    case 2:
        printf("\nFilm id: ");
        scanf("%d",&id);
        printf("Name: ");
        scanf("%s",name);
        printf("Format: ");
        scanf("%s",format);
        printf("Show date: ");
        scanf("%s",showDate);
        printf("Show time: ");
        scanf("%s",showTime);
        printf("Price: ");
        scanf("%d",&price);
        printf("Capacity: ");
        scanf("%d",&capacity);
        status = addFilm(filePtr, id, name, format, showDate, showTime, price, capacity);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("There is already a film with id %d\n", id);
        break;
    case 3:
        printf("\nFilm id: ");
        scanf("%d",&id);
        status = deleteFilm(filePtr, id);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No film with id %d\n", id);
        break;
    case 4:
        printf("\nMax price: ");
        scanf("%d",&maxPrice);
        count = showLowPriced2DFilms(filePtr, maxPrice);
        if (count == 0)
            printf("No 2D film with a price <= %d\n", maxPrice);
        else
            printf("There are %d 2D films with a price <= %d\n", count, maxPrice);
        break;
    }

    fclose(filePtr);
    return 0;
}

void showRecords(FILE *filePtr)
{
    fseek(filePtr, 0, SEEK_SET);

    printf("\n%-3s %-20s %-10s %-12s %-12s %-10s %s\n",
                   "ID",
                   "Name",
                   "Format",
                   "Show Date",
                   "Show Time",
                   "Price",
                   "Capacity");

    while (!feof(filePtr))
    {
        filmData film;
        int result = fread(&film, sizeof(filmData), 1, filePtr);
        if (result != 0 && film.id != 0)
        {
            printf("%-3d %-20s %-10s %-12s %-12s %-10d %d\n",
                   film.id,
                   film.name,
                   film.format,
                   film.showDate,
                   film.showTime,
                   film.price,
                   film.capacity);
        }
    }
}

int updateCapacity(FILE *filePtr, unsigned int id, int newCapacity)
{
    filmData f1;
    fseek(filePtr, 0, SEEK_SET);
    while (fread(&f1, sizeof(filmData), 1, filePtr))
    {
        if (f1.id == id)
        {
            f1.capacity = newCapacity;
            fseek(filePtr, -sizeof(filmData), SEEK_CUR);
            fwrite(&f1, sizeof(filmData), 1, filePtr);  
            return 1;
        }
    }
    return 0;
}

int addFilm(FILE *filePtr, unsigned int id, char name[20], char format[5], char showDate[20], char showTime[20], int price, int capacity)
{
    filmData f, f1;
    fseek(filePtr, 0, SEEK_SET);
    f.id = id;
    strcpy(f.name, name);
    strcpy(f.format, format);
    strcpy(f.showDate, showDate);
    strcpy(f.showTime, showTime);
    f.capacity = capacity;
    f.price = price;
    while (fread(&f1, sizeof(filmData), 1, filePtr))
    {
        if (f1.id == id)
            return 0;
    }

    fwrite(&f, sizeof(filmData), 1, filePtr);
    return 1;
}

int deleteFilm(FILE *filePtr, unsigned int id)
{
    filmData f1;
    fseek(filePtr, 0, SEEK_SET);
    while (fread(&f1, sizeof(filmData), 1, filePtr))
    {
        if (f1.id == id)
        {
            fseek(filePtr, -sizeof(filmData), SEEK_CUR);
            filmData f;
            f.id = 0;
            strcpy(f.name, "");
            strcpy(f.format, "");
            strcpy(f.showDate, "");
            strcpy(f.showTime, "showTime");
            f.capacity = 0;
            f.price = 0;
            fwrite(&f, sizeof(filmData), 1, filePtr);
            return 1;
        }
    }
    return 0;
}

int showLowPriced2DFilms(FILE *filePtr, int maxPrice)
{
    filmData f;
    int c = -1;
        printf("\n%-3s %-20s %-10s %-12s %-12s %-10s %s\n",
                   "ID",
                   "Name",
                   "Format",
                   "Show Date",
                   "Show Time",
                   "Price",
                   "Capacity");
    fseek(filePtr, 0, SEEK_SET);
    while (fread(&f, sizeof(filmData), 1, filePtr))
    {
        if (f.price <= maxPrice)
        {
            c++;
            printf("%-3d %-20s %-10s %-12s %-12s %-10d %d\n",
                   f.id,
                   f.name,
                   f.format,
                   f.showDate,
                   f.showTime,
                   f.price,
                   f.capacity);
        }
    }
    return c;
}
