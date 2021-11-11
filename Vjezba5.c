#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Element;
typedef struct Element* position;
typedef struct Element
{
    double number;
    position next;
}element;

position create_element(double number);
int insert_after(position p, position new_el);
int push(position head, double number);
int delete_after(position p);
int pop(position head, double* result);
int perform_operation(position head, char operation);
int calculate_postfix_from_file(char* file_name, double* result);

int main()
{
    return 0;
}

position create_element(double number)
{
    //fali
}

int insert_after(position p, position new_el)
{
    new_el->next = position->next;
    position->next = new_el;
    return 0;
}

int push(position head, double number)
{
    position new_el = NULL;
    new_el = create_element(number);

}

int delete_after(position p)
{
    position temp = position->next;
    if (!temp)
    {
        return 0;
    }
    position->next = temp->next;
    free(temp);
    return 0;
}

int pop(position head, double* result)
{
    position first = head->next;
    if (!first)
    {
        printf("Postfix not found.\n");
    }
    *result = first->number;
    delete_after(head);
    return 0;
}

int perform_operation(position head, char operation)
{
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;
    double result = 0;
    status2 = pop(&operand2, head);
    if (!status2)
    {
        return -1;
    }
    status1 = pop(&operand1, head);
    if (!status1)
    {
        return -2;
    }
    switch (operation)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '*':
        result = operand1 * operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '/':
        if (operand2 = 0)
        {
            printf("You can't devide by zero.\n");
            return -3;
        }
        result = operand1 / operand2;
        break;
    }
    //fali nesto
    return push(head, result);
}

int calculate_postfix_from_file(char* file_name, double* result)
{
    FILE* file = NULL;
    file = fopen(file_name, "rb");
    if (!file)
    {
        printf("Can't open file.\n");
        return -1;
    }
}
