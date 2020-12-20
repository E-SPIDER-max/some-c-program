/*
made by pranaya raj neupane
class 12 
section A
kathmandu Nepal
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "helper.c"

DATA d1;
FILE *box, *temp;
void addrecord();
void listrecord();
void searchrecord();
void deleterecord();
void payment();
void modifyrecord();
void function()
{
    int ans;
    printf("Choose\n");
    scanf("%d", &ans);
    switch (ans)
    {
    case 1:
        addrecord();
        break;
    case 2:
        listrecord();
        break;
    case 6:
        searchrecord();
        break;
    case 3:
        deleterecord();
        break;
    case 4:
        payment();
        break;
    case 5:
        modifyrecord();
        break;
    case 0:
        exit(0);
        break;
    default:
        main();
        break;
    }
}
int main()
{
    clear();
    header();
    title();
    function();
    return 0;
}

void addrecord()
{
    char ans1;
    int ans2;
    clear();
    header();
    printf("\n[1]-Add-New record\n[2]-Add-Amount\n ");
    scanf("%d",&ans2);
    if(ans2==2)
    {
        update();
        main();
    }
    printf("Adding record\n\n");
    printf("Full-Name: ");
    scanf("%s %s", d1.name, d1.cast);
    printf("Phone-Number: ");
    scanf("%li", &d1.ph_no);
    printf("Amount: ");
    scanf("%f", &d1.amount);

    box = fopen("DETAIL", "ab+");
    fwrite(&d1, sizeof(d1), 1, box);
    fclose(box);
    clear();
    getchar(); //buffer
    printf("Add more recoed[y/n]: ");
    scanf("%c", &ans1);
    if (ans1 == 'y')
    {
        addrecord();
    }
    else
    {
        main();
    }
}
void listrecord()
{
    clear();
    header();
    printf("Phone-Number\t\t\tFull-NAME\t\t\t\tAmount\n");
    printf("----------------------------------------------------------------------------------------\n");
    box = fopen("DETAIL", "rb+");
    if (box == NULL)
    {
        printf("Error in opeaning file\n");
        exit(1);
    }
    while (fread(&d1, sizeof(d1), 1, box) == 1)
    {
        printf("%li\t\t\t%s %s\t\t\t\tRs.%.2f\n", d1.ph_no, d1.name, d1.cast, d1.amount);
    }
    printf("----------------------------------------------------------------------------------------\n");
    getchar(); //buffer
    getchar(); //hold
    clear();
    main();
}

void searchrecord()
{
    char name1[10];
    int data = 0;
    clear();
    header();
    printf("Enter Name: ");
    scanf("%s", name1);
    box = fopen("DETAIL", "rb");
    clear();
    printf("Phone-Number\t\t\tFull-NAME\t\t\t\tAmount\n");
    printf("----------------------------------------------------------------------------------------\n");
    while (fread(&d1, sizeof(d1), 1, box))
    {
        if ((strcmp(name1, d1.name)) == 0)
        {
            printf("%li\t\t\t%s %s\t\t\t\tRs.%.2f\n", d1.ph_no, d1.name, d1.cast, d1.amount);
            data++;
        }
    }
    printf("----------------------------------------------------------------------------------------\n");
    if (data == 0)
    {
        clear();
        printf("Record dosen't found\n");
    }
    fclose(box);
    getchar(); //buffer
    getchar(); //hold
    main();
}

void deleterecord()
{
    char name1[10], caste1[10];
    int data = 0;
    clear();
    header();
    printf("Enter Name: ");
    scanf("%s %s", name1, caste1);
    box = fopen("DETAIL", "rb");
    temp = fopen("temp", "wb");
    while (fread(&d1, sizeof(d1), 1, box))
    {
        if (strcmp(name1, d1.name) == 0 && (strcmp(caste1, d1.cast)) == 0)
        {
            data = 1;
            if (d1.amount == 0)
            {
                data = -1;
            }
            else
            {
                printf("\n\nAmount Not cleared");
                fwrite(&d1, sizeof(d1), 1, temp);
            }
        }
        else
        {
            fwrite(&d1, sizeof(d1), 1, temp);
        }
    }
    if (data == 0)
    {
        clear();
        printf("Record dosen't found\n");
    }
    if (data == -1)
    {
        clear();
        printf("REcord Deleted successfully");
    }
    fclose(box);
    fclose(temp);
    remove("DETAIL");
    rename("temp", "DETAIL");
    getchar(); //buffer
    getchar(); //hold
    main();
}

void payment()
{
    char name1[10], caste1[10];
    int data = 0;
    float amt;
    clear();
    header();
    printf("Enter Name: ");
    scanf("%s %s", name1, caste1);
    box = fopen("DETAIL", "rb");
    temp = fopen("temp", "wb");
    while (fread(&d1, sizeof(d1), 1, box))
    {
        if (strcmp(name1, d1.name) == 0 && (strcmp(caste1, d1.cast)) == 0)
        {
            data =1;
            if (d1.amount != 0)
            {
                float money, final_money;
                clear();
                printf("\nAmount = Rs%.2f\n", d1.amount);
                printf("\nPayment: ");
                scanf("%f", &money);
                final_money = d1.amount - money;
                amt = final_money;

                d1.amount = final_money;
                fwrite(&d1, sizeof(d1), 1, temp);
                data = -1;
            }
            else
            {
                printf("\nAmount is cleared\n");
                fwrite(&d1, sizeof(d1), 1, temp);
            }
        }
        else
        {
            fwrite(&d1, sizeof(d1), 1, temp);
        }
    }
    if (data == 0)
    {
        clear();
        printf("Record dosen't found\n");
    }
    if (data == -1)
    {
        clear();
        printf("\nAmount Paid Rs%.2f\n",amt);
    }
    fclose(box);
    fclose(temp);
    remove("DETAIL");
    rename("temp", "DETAIL");
    getchar(); //buffer
    getchar(); //hold
    main();
}

void modifyrecord()
{
    char name1[10], caste1[10];
    int data = 0;
    clear();
    header();
    printf("Enter Name: ");
    scanf("%s %s", name1, caste1);
    box = fopen("DETAIL", "rb");
    temp = fopen("temp", "wb");
    while (fread(&d1, sizeof(d1), 1, box))
    {
        if (strcmp(name1, d1.name) == 0 && (strcmp(caste1, d1.cast)) == 0)
        {
            data = 1;
            int ans;
            char name2[10],cast2[10];
            long ph_no2;
            printf("DO you want to change\n[1]-Full-Name\n[2]-number\n");
            scanf("%d",&ans);
            if(ans == 1)
            {
                clear();
                printf("Enter New-Name: ");
                scanf("%s %s",name2,cast2);    
                strcpy(d1.name,name2);
                strcpy(d1.cast,cast2);
                fwrite(&d1, sizeof(d1), 1, temp);
                data = -1;
            }
            if(ans==2)
            {
                clear();
                printf("Enter New-Phone-Number: ");
                scanf("%li",&ph_no2);
                d1.ph_no = ph_no2;
                fwrite(&d1, sizeof(d1), 1, temp);
                data = -1;
            }

        }
        else
        {
            fwrite(&d1, sizeof(d1), 1, temp);
        }
    }
    if (data == 0)
    {
        clear();
        printf("Record dosen't found\n");
    }
    if (data == -1)
    {
        clear();
        printf("REcord changed successfully");
    }
    fclose(box);
    fclose(temp);
    remove("DETAIL");
    rename("temp", "DETAIL");
    getchar(); //buffer
    getchar(); //hold
    main();
}