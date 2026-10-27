
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20

char stack[MAX][MAX];
int top = -1;

void push(char value[]);
void pop(char value[]);
int isEmpty();
int isFull();
void display();
int preced(char ch);

void infix_postfix(char infix[], char postfix[]);
void infix_prefix(char infix[], char prefix[]);
void postfix_infix(char postfix[], char infix[]);
void prefix_infix(char prefix[], char infix[]);
void postfix_prefix(char postfix[], char prefix[]);
void prefix_postfix(char prefix[], char postfix[]);

int main()
{
    int choice;
    char value[MAX];
    char infix[MAX], postfix[MAX], prefix[MAX];

    while (1)
    {
        printf("\nStack Operations\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Display\n");
        printf("4. Infix to Postfix\n");
        printf("5. Infix to Prefix\n");
        printf("6. Postfix to Infix\n");
        printf("7. Prefix to Infix\n");
        printf("8. Postfix to Prefix\n");
        printf("9. Prefix to Postfix\n");
        printf("10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("Enter character to push: ");
                scanf(" %19s", value);
                push(value);
                break;

            case 2:
                if (!isEmpty())
                {
                    pop(value);
                    printf("Popped element: %s\n", value);
                }
                else
                    printf("Stack is empty.\n");
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Enter infix expression: ");
                scanf("%19s", infix);
                infix_postfix(infix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;

            case 5:
                printf("Enter infix expression: ");
                scanf("%19s", infix);
                infix_prefix(infix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;

            case 6:
                printf("Enter postfix expression: ");
                scanf("%19s", postfix);
                postfix_infix(postfix, infix);
                printf("Infix expression: %s\n", infix);
                break;

            case 7:
                printf("Enter prefix expression: ");
                scanf("%19s", prefix);
                prefix_infix(prefix, infix);
                printf("Infix expression: %s\n", infix);
                break;

            case 8:
                printf("Enter postfix expression: ");
                scanf("%19s", postfix);
                postfix_prefix(postfix, prefix);
                printf("Prefix expression: %s\n", prefix);
                break;

            case 9:
                printf("Enter prefix expression: ");
                scanf("%19s", prefix);
                prefix_postfix(prefix, postfix);
                printf("Postfix expression: %s\n", postfix);
                break;

            case 10:
                printf("Exiting Code.\n");
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

int isFull()
{
    return top == MAX - 1;
}

int isEmpty()
{
    return top == -1;
}

void push(char value[])
{
    if (isFull())
        printf("Stack overflow!\n");
    else
        strcpy(stack[++top], value);
}

void pop(char value[])
{
    if (isEmpty())
    {
        value[0] = '\0';
        printf("Stack underflow!\n");
    }
    else
        strcpy(value, stack[top--]);
}

void display()
{
    if (isEmpty())
        printf("Stack is empty.\n");
    else
    {
        printf("Stack elements:\n");

        for (int i = top; i >= 0; i--)
            printf("%s\n", stack[i]);
    }
}

int preced(char ch)
{
    if (ch == '+' || ch == '-')
        return 1;
    else if (ch == '*' || ch == '/')
        return 2;
    else if (ch == '^')
        return 3;
    else
        return 0;
}

/* 1. Infix to Postfix */

void infix_postfix(char infix[], char postfix[])
{
    int i, k = 0;
    char temp[2];

    top = -1;

    for (i = 0; infix[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)infix[i]))
            postfix[k++] = infix[i];

        else if (infix[i] == '(')
        {
            temp[0] = '(';
            temp[1] = '\0';
            push(temp);
        }
        else if (infix[i] == ')')
        {
            while (!isEmpty() && stack[top][0] != '(')
            {
                pop(temp);
                postfix[k++] = temp[0];
            }

            if (!isEmpty())
                pop(temp);
        }
        else
        {
            while (!isEmpty() && stack[top][0] != '(' &&
                  (preced(stack[top][0]) > preced(infix[i]) ||
                  (preced(stack[top][0]) == preced(infix[i]) &&
                   infix[i] != '^')))
            {
                pop(temp);
                postfix[k++] = temp[0];
            }

            temp[0] = infix[i];
            temp[1] = '\0';
            push(temp);
        }
    }

    while (!isEmpty())
    {
        char op[MAX];
        pop(op);

        if (op[0] != '(')
            postfix[k++] = op[0];
    }

    postfix[k] = '\0';
}

/* 2. Infix to Prefix */

void infix_prefix(char infix[], char prefix[])
{
    char temp[MAX], op[2];
    int i, k = 0;

    strcpy(temp, infix);

    for (i = 0; temp[i] != '\0'; i++)
    {
        if (temp[i] == '(')
            temp[i] = ')';
        else if (temp[i] == ')')
            temp[i] = '(';
    }

    for (i = 0; i < (int)strlen(temp) / 2; i++)
    {
        char ch = temp[i];
        temp[i] = temp[strlen(temp) - 1 - i];
        temp[strlen(temp) - 1 - i] = ch;
    }

    top = -1;

    for (i = 0; temp[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)temp[i]))
            prefix[k++] = temp[i];

        else if (temp[i] == '(')
        {
            op[0] = '(';
            op[1] = '\0';
            push(op);
        }
        else if (temp[i] == ')')
        {
            while (!isEmpty() && stack[top][0] != '(')
            {
                pop(op);
                prefix[k++] = op[0];
            }

            if (!isEmpty())
                pop(op);
        }
        else
        {
            while (!isEmpty() && stack[top][0] != '(' &&
                  (preced(stack[top][0]) > preced(temp[i]) ||
                  (preced(stack[top][0]) == preced(temp[i]) &&
                   temp[i] == '^')))
            {
                pop(op);
                prefix[k++] = op[0];
            }

            op[0] = temp[i];
            op[1] = '\0';
            push(op);
        }
    }

    while (!isEmpty())
    {
        pop(op);
        prefix[k++] = op[0];
    }

    prefix[k] = '\0';

    for (i = 0; i < (int)strlen(prefix) / 2; i++)
    {
        char ch = prefix[i];
        prefix[i] = prefix[strlen(prefix) - 1 - i];
        prefix[strlen(prefix) - 1 - i] = ch;
    }
}

/* 3. Postfix to Infix */

void postfix_infix(char postfix[], char infix[])
{
    char op1[MAX], op2[MAX], temp[MAX];
    int i;

    top = -1;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)postfix[i]))
        {
            temp[0] = postfix[i];
            temp[1] = '\0';
            push(temp);
        }
        else
        {
            if (top < 1)
            {
                printf("Invalid postfix expression!\n");
                infix[0] = '\0';
                top = -1;
                return;
            }

            pop(op2);
            pop(op1);

            snprintf(temp, MAX, "(%s%c%s)",
                     op1, postfix[i], op2);

            push(temp);
        }
    }

    pop(infix);
}

/* 4. Prefix to Infix */

void prefix_infix(char prefix[], char infix[])
{
    char op1[MAX], op2[MAX], temp[MAX];
    int i;

    top = -1;

    for (i = (int)strlen(prefix) - 1; i >= 0; i--)
    {
        if (isalnum((unsigned char)prefix[i]))
        {
            temp[0] = prefix[i];
            temp[1] = '\0';
            push(temp);
        }
        else
        {
            if (top < 1)
            {
                printf("Invalid prefix expression!\n");
                infix[0] = '\0';
                top = -1;
                return;
            }

            pop(op1);
            pop(op2);

            snprintf(temp, MAX, "(%s%c%s)",
                     op1, prefix[i], op2);

            push(temp);
        }
    }

    pop(infix);
}

/* 5. Postfix to Prefix */

void postfix_prefix(char postfix[], char prefix[])
{
    char op1[MAX], op2[MAX], temp[MAX];
    int i;

    top = -1;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        if (isalnum((unsigned char)postfix[i]))
        {
            temp[0] = postfix[i];
            temp[1] = '\0';
            push(temp);
        }
        else
        {
            if (top < 1)
            {
                printf("Invalid postfix expression!\n");
                prefix[0] = '\0';
                top = -1;
                return;
            }

            pop(op2);
            pop(op1);

            snprintf(temp, MAX, "%c%s%s",
                     postfix[i], op1, op2);

            push(temp);
        }
    }

    pop(prefix);
}

/* 6. Prefix to Postfix */

void prefix_postfix(char prefix[], char postfix[])
{
    char op1[MAX], op2[MAX], temp[MAX];
    int i;

    top = -1;

    for (i = (int)strlen(prefix) - 1; i >= 0; i--)
    {
        if (isalnum((unsigned char)prefix[i]))
        {
            temp[0] = prefix[i];
            temp[1] = '\0';
            push(temp);
        }
        else
        {
            if (top < 1)
            {
                printf("Invalid prefix expression!\n");
                postfix[0] = '\0';
                top = -1;
                return;
            }

            pop(op1);
            pop(op2);

            snprintf(temp, MAX, "%s%s%c",
                     op1, op2, prefix[i]);

            push(temp);
        }
    }

    pop(postfix);
}

