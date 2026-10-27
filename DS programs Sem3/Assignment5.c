
#include <stdio.h>
#include <stdlib.h>

struct node
{
    int coeff;
    int exp;
    struct node *next;
};

typedef struct node Node;

Node *createNode(int coeff, int exp)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    newNode->coeff = coeff;
    newNode->exp = exp;
    newNode->next = newNode;

    return newNode;
}

void insertTerm(Node **head, int coeff, int exp)
{
    if (coeff == 0)
        return;

    Node *newNode = createNode(coeff, exp);

    if (*head == NULL)
    {
        *head = newNode;
        return;
    }

    Node *temp = *head;

    while (temp->next != *head)
        temp = temp->next;

    temp->next = newNode;
    newNode->next = *head;
}

Node *createPolynomial()
{
    Node *head = NULL;
    int n, coeff, exp;

    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &coeff, &exp);

        insertTerm(&head, coeff, exp);
    }

    return head;
}

void displayPolynomial(Node *head)
{
    if (head == NULL)
    {
        printf("0\n");
        return;
    }

    Node *temp = head;
    int first = 1;

    do
    {
        if (temp->coeff != 0)
        {
            if (!first && temp->coeff > 0)
                printf(" + ");
            else if (temp->coeff < 0)
                printf(" - ");

            if (first && temp->coeff < 0)
            {
                /* Minus sign printed above */
            }

            int c = abs(temp->coeff);

            if (temp->exp == 0)
                printf("%d", c);
            else if (temp->exp == 1)
            {
                if (c != 1)
                    printf("%d", c);
                printf("x");
            }
            else
            {
                if (c != 1)
                    printf("%d", c);
                printf("x^%d", temp->exp);
            }

            first = 0;
        }

        temp = temp->next;
    } while (temp != head);

    if (first)
        printf("0");

    printf("\n");
}

Node *addPolynomials(Node *p1, Node *p2)
{
    Node *result = NULL;

    if (p1 == NULL && p2 == NULL)
        return NULL;

    /* Copy terms of the first polynomial */
    if (p1 != NULL)
    {
        Node *temp = p1;

        do
        {
            insertTerm(&result, temp->coeff, temp->exp);
            temp = temp->next;
        } while (temp != p1);
    }

    /* Add terms of the second polynomial */
    if (p2 != NULL)
    {
        Node *temp = p2;

        do
        {
            Node *current = result;
            int found = 0;

            if (result != NULL)
            {
                do
                {
                    if (current->exp == temp->exp)
                    {
                        current->coeff += temp->coeff;
                        found = 1;
                        break;
                    }

                    current = current->next;
                } while (current != result);
            }

            if (!found)
                insertTerm(&result, temp->coeff, temp->exp);

            temp = temp->next;
        } while (temp != p2);
    }

    /* Remove terms whose coefficients become zero */
    if (result != NULL)
    {
        Node *current = result;
        Node *previous = NULL;

        do
        {
            Node *nextNode = current->next;

            if (current->coeff == 0)
            {
                if (current->next == current)
                {
                    free(current);
                    result = NULL;
                    break;
                }

                if (previous == NULL)
                {
                    Node *last = current;

                    while (last->next != current)
                        last = last->next;

                    result = current->next;
                    last->next = result;
                    free(current);
                    current = result;
                    continue;
                }
                else
                {
                    previous->next = nextNode;
                    free(current);
                    current = nextNode;
                    continue;
                }
            }

            previous = current;
            current = nextNode;

        } while (current != result);
    }

    return result;
}

int main()
{
    Node *p1 = NULL;
    Node *p2 = NULL;
    Node *sum = NULL;

    printf("\nEnter first polynomial:\n");
    p1 = createPolynomial();

    printf("\nEnter second polynomial:\n");
    p2 = createPolynomial();

    printf("\nFirst polynomial: ");
    displayPolynomial(p1);

    printf("Second polynomial: ");
    displayPolynomial(p2);

    sum = addPolynomials(p1, p2);

    printf("Sum of polynomials: ");
    displayPolynomial(sum);

    return 0;
}

