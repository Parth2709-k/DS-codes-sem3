
#include <stdio.h>
#include <stdlib.h>

#define MAX 5

struct PrintJob
{
    int jobID;
    char title[50];
};

struct PrintJob queue[MAX];
int front = -1, rear = -1;

void add();
void delete();
void display();

int main()
{
    int choice;

    do
    {
        printf("\n\n--- PRINTER QUEUE MANAGER ---");
        printf("\n1. Add a Print Job");
        printf("\n2. Process a Print Job");
        printf("\n3. Display Pending Print Jobs");
        printf("\n4. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
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
                printf("\nExiting Printer Queue Manager.\n");
                break;

            default:
                printf("\nInvalid choice!");
        }

    } while(choice != 4);

    return 0;
}

void add()
{
    if((rear + 1) % MAX == front)
    {
        printf("\nPrinter queue is full!");
        return;
    }

    if(front == -1)
    {
        front = 0;
        rear = 0;
    }
    else
    {
        rear = (rear + 1) % MAX;
    }

    printf("\nEnter Job ID: ");
    scanf("%d", &queue[rear].jobID);

    printf("Enter Document Title: ");
    scanf(" %49[^\n]", queue[rear].title);

    printf("\nPrint job added successfully!");
}

void delete()
{
    if(front == -1)
    {
        printf("\nPrinter queue is empty!");
        return;
    }

    printf("\nProcessing Print Job...");
    printf("\nJob ID: %d", queue[front].jobID);
    printf("\nDocument Title: %s", queue[front].title);

    if(front == rear)
    {
        front = -1;
        rear = -1;
    }
    else
    {
        front = (front + 1) % MAX;
    }

    printf("\nPrint job processed successfully!");
}

void display()
{
    int i;

    if(front == -1)
    {
        printf("\nNo pending print jobs!");
        return;
    }

    printf("\n\n--- PENDING PRINT JOBS ---");

    i = front;

    while(1)
    {
        printf("\nJob ID: %d", queue[i].jobID);
        printf("\nDocument Title: %s\n", queue[i].title);

        if(i == rear)
            break;

        i = (i + 1) % MAX;
    }
}

