#include<stdio.h>
#include<stdlib.h>

struct polynomial
{
    int coeff;
    int exp;
    struct polynomial *next;
};

void create(struct polynomial *head);
void display(struct polynomial *head);
void add_poly(struct polynomial *p1, struct polynomial *p2,
              struct polynomial *result);
void insert_term(struct polynomial *head, int coeff, int exp);

int main()
{
    struct polynomial *p1, *p2, *result;
    int choice;

    p1 = (struct polynomial*)malloc(sizeof(struct polynomial));
    p2 = (struct polynomial*)malloc(sizeof(struct polynomial));
    result = (struct polynomial*)malloc(sizeof(struct polynomial));

    p1->next = p1;
    p2->next = p2;
    result->next = result;

    while(1)
    {
        printf("\nPOLYNOMIAL OPERATIONS MENU\n");
        printf("1. Create First Polynomial\n");
        printf("2. Create Second Polynomial\n");
        printf("3. Display Polynomials\n");
        printf("4. Add Polynomials\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("\nEnter First Polynomial:\n");
                p1->next = p1;
                create(p1);
                break;

            case 2:
                printf("\nEnter Second Polynomial:\n");
                p2->next = p2;
                create(p2);
                break;

            case 3:
                printf("\nFirst Polynomial: ");
                display(p1);

                printf("Second Polynomial: ");
                display(p2);
                break;

            case 4:
                result->next = result;
                add_poly(p1, p2, result);

                printf("\nFirst Polynomial: ");
                display(p1);

                printf("Second Polynomial: ");
                display(p2);

                printf("Resultant Polynomial: ");
                display(result);
                break;

            case 5:
                printf("Exiting the program\n");
                exit(0);

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}

void create(struct polynomial *head)
{
    struct polynomial *newnd, *last;
    int n, i;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    last = head;

    for(i = 0; i < n; i++)
    {
        newnd = (struct polynomial*)malloc(sizeof(struct polynomial));

        if(newnd == NULL)
        {
            printf("Memory allocation failed\n");
            return;
        }

        printf("Enter coefficient: ");
        scanf("%d", &newnd->coeff);

        printf("Enter exponent: ");
        scanf("%d", &newnd->exp);

        newnd->next = head;
        last->next = newnd;
        last = newnd;
    }

    printf("Polynomial created successfully\n");
}

void display(struct polynomial *head)
{
    struct polynomial *temp;
    int first = 1, c;

    if(head->next == head)
    {
        printf("0\n");
        return;
    }

    temp = head->next;

    while(temp != head)
    {
        if(temp->coeff != 0)
        {
            if(!first)
            {
                if(temp->coeff > 0)
                    printf(" + ");
                else
                    printf(" - ");
            }
            else if(temp->coeff < 0)
            {
                printf("-");
            }

            c = abs(temp->coeff);

            if(temp->exp == 0)
                printf("%d", c);
            else if(temp->exp == 1)
            {
                if(c != 1)
                    printf("%d", c);

                printf("x");
            }
            else
            {
                if(c != 1)
                    printf("%d", c);

                printf("x^%d", temp->exp);
            }

            first = 0;
        }

        temp = temp->next;
    }

    if(first)
        printf("0");

    printf("\n");
}

void insert_term(struct polynomial *head, int coeff, int exp)
{
    struct polynomial *newnd, *temp;

    if(coeff == 0)
        return;

    temp = head;

    while(temp->next != head)
    {
        if(temp->next->exp == exp)
        {
            temp->next->coeff += coeff;
            return;
        }

        temp = temp->next;
    }

    newnd = (struct polynomial*)malloc(sizeof(struct polynomial));

    if(newnd == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    newnd->coeff = coeff;
    newnd->exp = exp;
    newnd->next = head;

    temp->next = newnd;
}

void add_poly(struct polynomial *p1, struct polynomial *p2,
              struct polynomial *result)
{
    struct polynomial *temp;

    temp = p1->next;

    while(temp != p1)
    {
        insert_term(result, temp->coeff, temp->exp);
        temp = temp->next;
    }

    temp = p2->next;

    while(temp != p2)
    {
        insert_term(result, temp->coeff, temp->exp);
        temp = temp->next;
    }

    printf("Polynomials added successfully\n");
}
