
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5

struct PrintJob
{
    int jobID;
    char title[50];
};

struct PrintJob queue[MAX];
int front = -1, rear = -1;

void add()
{
    struct PrintJob job;

    if (rear == MAX - 1)
    {
        printf("\nQueue Overflow! No space for new jobs.\n");
        return;
    }

    printf("Enter Job ID: ");
    scanf("%d", &job.jobID);

    printf("Enter Document Title: ");
    scanf(" %49[^\n]", job.title);

    if (front == -1)
        front = 0;

    rear++;
    queue[rear] = job;

    printf("Print job added successfully.\n");
}

void delete()
{
    if (front == -1)
    {
        printf("\nQueue Underflow! No jobs to process.\n");
        return;
    }

    printf("\nProcessing Job ID: %d", queue[front].jobID);
    printf("\nDocument Title: %s\n", queue[front].title);

    if (front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front++;
    }

    printf("Print job completed.\n");
}

void display()
{
    int i;

    if (front == -1)
    {
        printf("\nNo pending print jobs.\n");
        return;
    }

    printf("\nPending Print Jobs:\n");
    printf("Job ID\tDocument Title\n");

    for (i = front; i <= rear; i++)
    {
        printf("%d\t%s\n", queue[i].jobID, queue[i].title);
    }
}

int main()
{
    int choice;

    do
    {
        printf("\n--- Printer Queue Menu ---\n");
        printf("1. Add Print Job\n");
        printf("2. Delete/Process Print Job\n");
        printf("3. Display Pending Jobs\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                add();
                break;

            case 2:
                delete();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting Printer Queue System.\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}

