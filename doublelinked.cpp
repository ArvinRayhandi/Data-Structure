#include <stdio.h>
#include <stdlib.h>

struct tnode {
    int x;
    struct tnode *next;
    struct tnode *prev;
};

struct tnode *head = NULL, *tail = NULL;

void push_front(int value) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
        head->prev = NULL;
    }
}

void push_back(int value) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;
    
    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
        tail->next = NULL;
    }
}

void push_mid(int value, int searchKey) {
    struct tnode *node = (struct tnode*)malloc(sizeof(struct tnode));
    node->x = value;

    if (head == NULL) {
        head = tail = node;
        node->next = node->prev = NULL;
    } else {
        struct tnode *curr = head;
        while (curr != NULL) {
            if (curr->x == searchKey) {
                if (curr == tail) {
                    push_back(value);
                } else {
                    node->next = curr->next;
                    node->prev = curr;
                    curr->next->prev = node;
                    curr->next = node;
                }
                return;
            }
            curr = curr->next;
        }
        printf("Data %d not found\n", searchKey);
        free(node);
    }
}

void del_front() {
    if (head == NULL) {
        printf("There is no data\n");
    } else {
        struct tnode *del = head;
        head = head->next;
        if (head) head->prev = NULL;
        else tail = NULL;
        free(del);
    }
}

void del_back() {
    if (head == NULL) {
        printf("There is no data\n");
    } else {
        struct tnode *del = tail;
        tail = tail->prev;
        if (tail) tail->next = NULL;
        else head = NULL;
        free(del);
    }
}

void del_mid(int value) {
    if (head == NULL) {
        printf("There is no data\n");
        return;
    }
    struct tnode *curr = head;
    
    while (curr != NULL) {
        if (curr->x == value) {
            if (curr == head) {
                del_front();
            } else if (curr == tail) {
                del_back();
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                free(curr);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Data %d not found\n", value);
}

void printList() {
    if (head == NULL) {
        printf("There is no data\n");
        return;
    }
    struct tnode *curr = head;
    while (curr != NULL) {
        printf("%d ", curr->x);
        curr = curr->next;
    }
    printf("\n");
}

int main() {
    printf("Linked List\n");

    push_front(76);
    push_front(90);
    push_front(45);
    push_mid(33, 90);
    del_back();
    del_front();
    del_mid(33);

    printList();
    return 0;
}
