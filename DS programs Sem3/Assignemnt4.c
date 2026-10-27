
#include <stdio.h>
#include <stdlib.h>

struct student
{
    int rno;
    struct student *next;
};

void display(struct student *head);
void add_data(struct student *head);
void remove_data(struct student *head);
int total_count(struct student *head);
void sort_list(struct student *head);
void reverse(struct student *head);

int main()
{
    int choice;

    // Create the dummy head node
    struct student *head =
        (struct student *)malloc(sizeof(struct student));

    if (head == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    head->next = NULL;

    do
    {
        printf("\n----- WORKSHOP ENROLLMENT MENU -----\n");
        printf("1. Add a Student\n");
        printf("2. Remove a Student\n");
        printf("3. Display the List\n");
        printf("4. Count Total Participants\n");
        printf("5. Sort the List\n");
        printf("6. Reverse the List\n");
        printf("7. Exit\n");

        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input\n");
            break;
        }

        switch (choice)
        {
            case 1:
                add_data(head);
                break;

            case 2:
                remove_data(head);
                break;

            case 3:
                display(head);
                break;

            case 4:
                printf("Total Participants: %d\n",
                       total_count(head));
                break;

            case 5:
                sort_list(head);
                printf("List sorted successfully\n");
                display(head);
                break;

            case 6:
                reverse(head);
                printf("List reversed successfully\n");
                display(head);
                break;

            case 7:
                printf("Exiting the program\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 7);

    // Free all student nodes
    while (head->next != NULL)
    {
        struct student *temp = head->next;
        head->next = temp->next;
        free(temp);
    }

    free(head);

    return 0;
}

void add_data(struct student *head)
{
    struct student *temp, *newnd;
    int elem;

    printf("Enter roll number: ");

    if (scanf("%d", &elem) != 1)
    {
        printf("Invalid roll number\n");
        return;
    }

    temp = head->next;

    // Check for duplicate roll number
    while (temp != NULL)
    {
        if (temp->rno == elem)
        {
            printf("Roll number already exists\n");
            return;
        }

        temp = temp->next;
    }

    newnd = (struct student *)malloc(sizeof(struct student));

    if (newnd == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newnd->rno = elem;
    newnd->next = NULL;

    // Find the last node
    temp = head;

    while (temp->next != NULL)
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

    printf("Enter roll number to delete: ");
    scanf("%d", &elem);

    prev = head;
    temp = head->next;

    while (temp != NULL && temp->rno != elem)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("No data found to delete\n");
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
    struct student *temp = head->next;

    if (temp == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }

    printf("Roll numbers: ");

    while (temp != NULL)
    {
        printf("%d -> ", temp->rno);
        temp = temp->next;
    }

    printf("NULL\n");
}

int total_count(struct student *head)
{
    struct student *temp = head->next;
    int count = 0;

    while (temp != NULL)
    {
        count++;
        temp = temp->next;
    }

    return count;
}

void sort_list(struct student *head)
{
    struct student *temp, *nextnd;
    int swap;

    for (temp = head->next; temp != NULL; temp = temp->next)
    {
        for (nextnd = temp->next;
             nextnd != NULL;
             nextnd = nextnd->next)
        {
            if (temp->rno > nextnd->rno)
            {
                swap = temp->rno;
                temp->rno = nextnd->rno;
                nextnd->rno = swap;
            }
        }
    }
}

void reverse(struct student *head)
{
    struct student *lastrev = NULL;
    struct student *present = head->next;
    struct student *infuture;

    while (present != NULL)
    {
        infuture = present->next;
        present->next = lastrev;
        lastrev = present;
        present = infuture;
    }

    head->next = lastrev;
}

