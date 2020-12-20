#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct data
{
    char name[10],cast[10];
    long ph_no;
    float amount;
}DATA;
DATA d1;
FILE *box, *temp;
void clear()
{
    system("clear");
}

void header()
{
    printf("\t\t\tTelephone Billing system\n\n");
}
void title()
{
    printf("[1]-ADD RECORD\n");
    printf("[2]-LIST RECORD\n");
    printf("[3]-DELETE RECORD\n");
    printf("[4]-PAYMENT\n");
    printf("[5]-MODIFY RECORD\n");
    printf("[6]-SEARCH RECORD\n");
    printf("[0]-EXIT\n\n");
}

int check(char name1[10],char cast1[10])
{
    FILE *box;
    DATA d1;
    while(fread(&d1,sizeof(d1),1,box)==1)
    {
        if(strcmp(name1,d1.name)==0 && strcmp(cast1,d1.cast)==0)
        {
            if(d1.amount !=0)
            {
                printf("Amount is not clear\n");
                getchar();//hold
            }
            char ans;
            printf("Are you sure you want to delete %s %s record\n[y/n]",name1,cast1);
            scanf("%c",&ans);
            if(ans == 'y')
                return 1;
            else if(ans == 'n')
                return 0;

        }
        else
        {
            printf("Record Dosen't exist");
            getchar();
        }
            
    }
}

void update()
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
            if (d1.amount >= 0)
            {
                float money, final_money;
                clear();
                printf("\nAmount = Rs.%.2f\n", d1.amount);
                printf("\nAdd-Amount: ");
                scanf("%f", &money);
                final_money = d1.amount + money;
                amt = final_money;

                d1.amount = final_money;
                fwrite(&d1, sizeof(d1), 1, temp);
                data = -1;
            }
            else
            {
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
        printf("\nAmount Added Rs.%.2f\n",amt);
        printf("\nTOtal Amount od %s %s = Rs.%.2f\n",name1,caste1,amt);
    }
    fclose(box);
    fclose(temp);
    remove("DETAIL");
    rename("temp", "DETAIL");
    getchar(); //buffer
    getchar(); //hold
}