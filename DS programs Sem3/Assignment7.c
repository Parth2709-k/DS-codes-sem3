
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 20

int stack[MAX];
int top = -1;

void push(int value);
int pop();
int isEmpty();
int isFull();
int evaluatePostfix(char postfix[]);

int main()
{
    char postfix[MAX];
    int result;

    printf("Enter postfix expression: ");
    scanf("%19s", postfix);

    result = evaluatePostfix(postfix);

    printf("Result = %d\n", result);

    return 0;
}

void push(int value)
{
    if (isFull())
    {
        printf("Stack Overflow\n");
        exit(1);
    }

    stack[++top] = value;
}

int pop()
{
    if (isEmpty())
    {
        printf("Stack Underflow\n");
        exit(1);
    }

    return stack[top--];
}

int isEmpty()
{
    return top == -1;
}

int isFull()
{
    return top == MAX - 1;
}

int evaluatePostfix(char postfix[])
{
    int i, a, b, result;
    char ch;

    for (i = 0; postfix[i] != '\0'; i++)
    {
        ch = postfix[i];

        if (isdigit(ch))
        {
            push(ch - '0');
        }
        else
        {
            b = pop();
            a = pop();

            switch (ch)
            {
                case '+':
                    result = a + b;
                    break;

                case '-':
                    result = a - b;
                    break;

                case '*':
                    result = a * b;
                    break;

                case '/':
                    if (b == 0)
                    {
                        printf("Division by zero error\n");
                        exit(1);
                    }
                    result = a / b;
                    break;

                case '%':
                    if (b == 0)
                    {
                        printf("Modulo by zero error\n");
                        exit(1);
                    }
                    result = a % b;
                    break;

                default:
                    printf("Invalid operator\n");
                    exit(1);
            }

            push(result);
        }
    }

    result = pop();
    return result;
}

