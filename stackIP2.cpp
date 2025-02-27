#include <stdio.h>
#include <string.h>

int precedence(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

int isAlphanumeric(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

void infixToPostfix(char* exp) {
    int len = strlen(exp);
    char result[len + 1];
    char stack[len];
    int j = 0;
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        if (isAlphanumeric(c))
            result[j++] = c;

        else if (c == '(')
            stack[++top] = '(';

        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--];
            }
            top--;
        }

        else {
            while (top != -1 && (precedence(c) < precedence(stack[top]) || precedence(c) == precedence(stack[top]))) {
                result[j++] = stack[top--];
            }
            stack[++top] = c;
        }
    }

    while (top != -1) {
        result[j++] = stack[top--];
    }

    result[j] = '\0';
    printf("Postfix: %s\n", result);
}

void postfixToInfix(char* exp) {
    int len = strlen(exp);
    char stack[len][len];
    int top = -1;

    for (int i = 0; i < len; i++) {
        char c = exp[i];

        if (isAlphanumeric(c)) {
            char operand[2] = {c, '\0'};
            strcpy(stack[++top], operand);
        }

        else {
            char operand2[len], operand1[len];
            strcpy(operand2, stack[top--]);
            strcpy(operand1, stack[top--]);

            char temp[len * 2];
            sprintf(temp, "(%s%c%s)", operand1, c, operand2);
            strcpy(stack[++top], temp);
        }
    }
    printf("Infix: %s\n", stack[top]);
}

int main() {
    char exp[100];
    int choice;

    printf("1. Infix to Postfix\n");
    printf("2. Postfix to Infix\n");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter infix: ");
        scanf("%[^\n]", exp);
        infixToPostfix(exp);
    } else if (choice == 2) {
        printf("Enter postfix: ");
        scanf("%[^\n]", exp);
        postfixToInfix(exp);
    } else {
        printf("Invalid\n");
    }

    return 0;
}