#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct person
{
    char phoneNumber[11];
    char name[50];
    char email[50];
    char address[50];
    char gender[6];
    struct person *next;
} *head, *tail;
FILE *file;
void addContact()
{
    int c;
    do
    {
        struct person *newNode = (struct person *)malloc(sizeof(struct person));
        printf("\n\nEnter Name :");
        scanf("%s", newNode->name);
        printf("Enter Contact Number: ");
        scanf("%s", newNode->phoneNumber);
        printf("Enter Email :");
        scanf("%s", newNode->email);
        printf("Enter Address :");
        scanf("%s", newNode->address);
        printf("Enter Gender :");
        scanf("%s", newNode->gender);
        newNode->next = NULL;
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
        file = fopen("contacts.txt", "a");
        if (file == NULL)
        {
            printf("Error opening file!\n");
            return;
        }
        fprintf(file, "%s %s %s %s %s\n", newNode->name, newNode->phoneNumber, newNode->email, newNode->address, newNode->gender);
        fclose(file);
        printf("Do You Want to add Another Contact ?");
        printf("press 1 to add else press any number :");
        scanf("%d", &c);
    } while (c == 1);
}
void loadContacts()
{
    file = fopen("contacts.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        struct person *newNode = (struct person *)malloc(sizeof(struct person));
        sscanf(line, "%49s %10s %49s %49s %5s", newNode->name, newNode->phoneNumber, newNode->email, newNode->address, newNode->gender);
        newNode->next = NULL;
        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    fclose(file);
}

void recordList()
{
    printf("\n\t\t-------------------------------------------\n");
    printf("\t\t\t\tList of Contact\n");
    printf("\t\t-------------------------------------------\n\n");
    int n = 1;
    struct person *ptr = head;
    if (ptr == NULL)
    {
        printf("\n\t\t\t<-- Contact Is Empty : -->\n");
    }
    else
    {
        while (ptr != NULL)
        {
            printf("%d", n);
            n++;
            printf("\tName : %s \n", ptr->name);
            printf("\tContact Number : %s \n", ptr->phoneNumber);
            printf("\tEmail : %s \n", ptr->email);
            printf("\tAddress : %s \n", ptr->address);
            printf("\tGender : %s \n", ptr->gender);
            ptr = ptr->next;
            printf("\n\n");
        }
    }
    printf("\n");
}
void deleteContact()
{
    char n[11], c;
    printf("\nEnter Phone Number For Searching Contact : ");
    scanf("%s", n);
    int pos = -1;
    struct person *ptr = head, *prv = NULL;
    while (ptr != NULL)
    {
        if (strcmp(n, ptr->phoneNumber) == 0)
        {
            pos = 0;
            printf("\n\t\t<-- Contact Found : -->\n");
            printf("\n\tContact Details :\n");
            printf("\tName : %s \n", ptr->name);
            printf("\tEmail : %s \n", ptr->email);
            printf("\tAddress : %s \n", ptr->address);
            printf("\tGender : %s \n\n", ptr->gender);
            printf("Press Y To Delete And Press Any key to Not Delete :");
            scanf(" %c", &c);
            if (c == 'y' || c == 'Y')
            {
                if (ptr == head)
                {
                    head = ptr->next;
                    free(ptr);
                }
                else
                {
                    prv->next = ptr->next;
                    if (ptr == tail)
                    {
                        tail = prv;
                    }
                    free(ptr);
                }
                printf("\n\t\t<-- Contact Has been Deleted : -->\n");
            }
            else
            {
                printf("\n\t\t<-- Contact Hasn't been Deleted : -->\n");
            }
            break;
        }
        prv = ptr;
        ptr = ptr->next;
    }
    if (pos == -1)
    {
        printf("\n\t\t!!! Contact Not Found !!!\n");
    }
}
void deleteAll()
{
    struct person *ptr = head, *temp;
    while (ptr != NULL)
    {
        temp = ptr->next;
        free(ptr);
        ptr = temp;
    }
    head = NULL;
    tail = NULL;
    printf("\n\t\t!!! All Contact Has been Deleted !!!\n");
}
void searchContact()
{
    char n[11];
    printf("\nEnter Phone Number For Searching Contact : ");
    scanf("%s", n);
    int pos = -1;
    struct person *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(n, ptr->phoneNumber) == 0)
        {
            pos = 0;
            printf("\n\t\t<-- Contact Found : -->\n");
            printf("\n\tContact Details :\n");
            printf("\tName : %s \n", ptr->name);
            printf("\tEmail : %s \n", ptr->email);
            printf("\tAddress : %s \n", ptr->address);
            printf("\tGender : %s \n\n", ptr->gender);
            break;
        }
        ptr = ptr->next;
    }
    if (pos == -1)
    {
        printf("\n\t\t!!! Contact Not Found !!!\n");
    }
}
void updateContact()
{
    char n[11];
    int d, f = 1;
    printf("\nEnter Phone Number For Update Contact : ");
    scanf("%s", n);
    int pos = -1;
    struct person *ptr = head;
    while (ptr != NULL)
    {
        if (strcmp(n, ptr->phoneNumber) == 0)
        {
            pos = 0;
            printf("\n\t\t<-- Contact Found : -->\n");
            printf("\n\tContact Details :\n");
            printf("\tName : %s \n", ptr->name);
            printf("\tContact Number : %s \n", ptr->phoneNumber);
            printf("\tEmail : %s \n", ptr->email);
            printf("\tAddress : %s \n", ptr->address);
            printf("\tGender : %s \n\n", ptr->gender);
            while (f)
            {

                printf("\t\t\t1 - Update Contact Name \n");
                printf("\t\t\t2 - Update Contact Number \n");
                printf("\t\t\t3 - Update Contact Email\n");
                printf("\t\t\t4 - Update Contact Address \n");
                printf("\t\t\t5 - Update Contact Gender \n");
                printf("\t\t\t6 - Exit Update Contact \n");
                printf("\tEnter choice : ");
                scanf("%d", &d);
                switch (d)
                {
                case 1:
                    printf("\n\tEnter New Name :");
                    scanf("%s", ptr->name);
                    break;
                case 2:
                    printf("\n\tEnter New Phone Number :");
                    scanf("%s", ptr->phoneNumber);
                    break;

                case 3:
                    printf("\n\tEnter New Email :");
                    scanf("%s", ptr->email);
                    break;
                case 4:
                    printf("\n\tEnter New Address :");
                    scanf("%s", ptr->address);
                    break;
                case 5:
                    printf("\n\tEnter New Gender :");
                    scanf("%s", ptr->gender);
                    break;
                case 6:
                    f = 0;
                    break;

                default:
                    printf("\n\t\t!!! Invalid Key !!! \n\n");
                    break;
                }
            }
            printf("\n\t\t<-- Contact Updated : -->\n");
            printf("\tName : %s \n", ptr->name);
            printf("\tContact Number : %s \n", ptr->phoneNumber);
            printf("\tEmail : %s \n", ptr->email);
            printf("\tAddress : %s \n", ptr->address);
            printf("\tGender : %s \n\n", ptr->gender);
            break;
        }
        ptr = ptr->next;
    }
    if (pos == -1)
    {
        printf("\n\t\t!!! Contact Not Found !!!\n");
    }
}
void saveContacts()
{
    file = fopen("contacts.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    struct person *ptr = head;
    while (ptr != NULL)
    {
        fprintf(file, "%s %s %s %s %s\n", ptr->name, ptr->phoneNumber, ptr->email, ptr->address, ptr->gender);
        ptr = ptr->next;
    }
    fclose(file);
}
void mainMenu()
{
    loadContacts();
    int n;
    while (1)
    {
        printf("\n\t\t-------------------------------------------\n");
        printf("\t\t\t\tMain Menu\n");
        printf("\t\t-------------------------------------------\n\n");
        printf("\t\t\t1 - Create New Contact \n");
        printf("\t\t\t2 - Delete Contact \n");
        printf("\t\t\t3 - Update Contact \n");
        printf("\t\t\t4 - Search Contact \n");
        printf("\t\t\t5 - Contact List \n");
        printf("\t\t\t6 - Delete All Contact \n");
        printf("\t\t\t7 - Exit Phone Book \n");
        printf("Enter Option : ");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;

        case 3:
            updateContact();
            break;
        case 4:
            searchContact();
            break;
        case 5:
            recordList();
            break;
        case 6:
            deleteAll();
            break;
        case 7:
            saveContacts();
            printf("\n\n\t\t\t\t<-- Good Bye --> \n\n");
            exit(1);
            break;

        default:
            printf("\n\n\t\t!!! Invalid Key !!! \n\n");
            break;
        }
    }
}
int main()
{
    file = NULL;
    mainMenu();
    return 0;
}