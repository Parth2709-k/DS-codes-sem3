#include<stdio.h>
#include<stdlib.h>

struct student
{
    int rno;
    char name[100];
    struct student *next;
};

void create(struct student *head);
void display(struct student *head);
int len_ll(struct student *head);
void add_data(struct student *head);
void remove_data(struct student *head);
int total_count(struct student *head);
void sort_list(struct student *head);
void reverse(struct student *head);

int main()
{
    struct student *head;
    head = (struct student*)malloc(sizeof(struct student));

    head->rno = 0;
    head->name[0] = '\0';
    head->next = NULL;

    int choice;
    int t_length;

    while(1)
    {
        printf("\nWORKSHOP ENROLLMENT MENU\n");
        printf("1. Add a Student\n");
        printf("2. Remove a Student\n");
        printf("3. Display the List\n");
        printf("4. Count Total Participants\n");
        printf("5. Sort the List\n");
        printf("6. Reverse the List\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice)
        {
            case 1:
                printf("\nAdding a student:\n");
                add_data(head);
                break;

            case 2:
                printf("\nRemoving a student:\n");
                remove_data(head);
                break;

            case 3:
                printf("\nDisplaying linked list:\n");
                display(head);
                break;

            case 4:
                t_length = total_count(head);
                printf("\nTotal Participants: %d\n", t_length);
                break;

            case 5:
                printf("\nSorting the list:\n");
                sort_list(head);
                display(head);
                break;

            case 6:
                printf("\nReversing the list:\n");
                reverse(head);
                display(head);
                break;

            case 7:
                printf("Exiting the program\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void create(struct student *head)
{
    struct student *newnd, *last;
    char ch;

    last = head;

    while(last->next != NULL)
    {
        last = last->next;
    }

    do
    {
        newnd = (struct student*)malloc(sizeof(struct student));

        printf("Enter name: ");
        fgets(newnd->name, sizeof(newnd->name), stdin);

        int i = 0;
        while(newnd->name[i] != '\0')
        {
            if(newnd->name[i] == '\n')
            {
                newnd->name[i] = '\0';
                break;
            }
            i++;
        }

        printf("Enter roll no: ");
        scanf("%d", &newnd->rno);
        getchar();

        newnd->next = NULL;
        last->next = newnd;
        last = newnd;

        printf("Enter y to continue adding: ");
        scanf("%c", &ch);
        getchar();

    } while(ch == 'y' || ch == 'Y');
}

void add_data(struct student *head)
{
    struct student *temp, *newnd;
    int elem;

    newnd = (struct student*)malloc(sizeof(struct student));

    if(newnd == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    printf("Enter roll no: ");
    scanf("%d", &elem);
    getchar();

    temp = head->next;

    while(temp != NULL)
    {
        if(temp->rno == elem)
        {
            printf("Roll number already exists\n");
            free(newnd);
            return;
        }
        temp = temp->next;
    }

    newnd->rno = elem;

    printf("Enter name: ");
    fgets(newnd->name, sizeof(newnd->name), stdin);

    int i = 0;
    while(newnd->name[i] != '\0')
    {
        if(newnd->name[i] == '\n')
        {
            newnd->name[i] = '\0';
            break;
        }
        i++;
    }

    newnd->next = NULL;

    temp = head;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }

    temp->next = newnd;

    printf("Student added successfully\n");
}

void remove_data(struct student *head)
{
    struct student *temp, *prev;
    int elem;

    printf("Enter roll no to delete: ");
    scanf("%d", &elem);

    prev = head;
    temp = head->next;

    while(temp != NULL && temp->rno != elem)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        printf("Student not found\n");
    }
    else
    {
        prev->next = temp->next;
        free(temp);
        printf("Student removed successfully\n");
    }
}

void display(struct student *head)
{
    struct student *temp;

    if(head->next == NULL)
    {
        printf("LL is empty\n");
    }
    else
    {
        temp = head->next;

        while(temp != NULL)
        {
            printf("Current Node Addr: %p\t", (void*)temp);
            printf("Name: %s\t", temp->name);
            printf("Roll No: %d\t", temp->rno);
            printf("Next Node Addr: %p\n", (void*)temp->next);

            temp = temp->next;
        }
    }
}

int len_ll(struct student *head)
{
    struct student *temp;
    int c = 0;

    temp = head->next;

    while(temp != NULL)
    {
        c++;
        temp = temp->next;
    }

    return c;
}

int total_count(struct student *head)
{
    return len_ll(head);
}

void sort_list(struct student *head)
{
    struct student *temp, *nextnd;
    int swap;
    char swapname[100];

    if(head->next == NULL)
    {
        printf("LL is empty\n");
        return;
    }

    temp = head->next;

    while(temp != NULL)
    {
        nextnd = temp->next;

        while(nextnd != NULL)
        {
            if(temp->rno > nextnd->rno)
            {
                swap = temp->rno;
                temp->rno = nextnd->rno;
                nextnd->rno = swap;

                int i = 0;

                while(temp->name[i] != '\0' &&
                      nextnd->name[i] != '\0')
                {
                    swapname[i] = temp->name[i];
                    temp->name[i] = nextnd->name[i];
                    nextnd->name[i] = swapname[i];
                    i++;
                }

                while(temp->name[i] != '\0')
                {
                    swapname[i] = temp->name[i];
                    temp->name[i] = nextnd->name[i];
                    nextnd->name[i] = swapname[i];
                    i++;
                }

                while(nextnd->name[i] != '\0')
                {
                    swapname[i] = temp->name[i];
                    temp->name[i] = nextnd->name[i];
                    nextnd->name[i] = swapname[i];
                    i++;
                }
            }

            nextnd = nextnd->next;
        }

        temp = temp->next;
    }

    printf("List sorted successfully\n");
}

void reverse(struct student *head)
{
    struct student *lastrev, *present, *infuture;

    lastrev = NULL;
    present = head->next;
    infuture = NULL;

    while(present != NULL)
    {
        infuture = present->next;
        present->next = lastrev;
        lastrev = present;
        present = infuture;
    }

    head->next = lastrev;

    printf("List reversed successfully\n");
}
