#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 100
#define MAX_STACK_SIZE 100

typedef int element;
typedef struct {
    element data[MAX_QUEUE_SIZE];
    int front, rear;
} QueueType;

typedef struct {
    int data[MAX_STACK_SIZE];
    int top;
} Stack;

void init_queue(QueueType* q) {
    q->front = q->rear = 0;
}

int is_empty_queue(QueueType* q) {
    return q->front == q->rear;
}

int is_full_queue(QueueType* q) {
    return (q->rear + 1) % MAX_QUEUE_SIZE == q->front;
}

void enqueue(QueueType* q, element item) {
    if (is_full_queue(q)) {
        fprintf(stderr, "Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = item;
}

element dequeue(QueueType* q) {
    if (is_empty_queue(q)) {
        fprintf(stderr, "Queue is empty\n");
        exit(1);
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void init_stack(Stack* s) {
    s->top = -1;
}

int is_empty_stack(Stack* s) {
    return s->top == -1;
}

int is_full_stack(Stack* s) {
    return s->top == (MAX_STACK_SIZE - 1);
}

void push(Stack* s, int item) {
    if (is_full_stack(s)) {
        fprintf(stderr, "Stack is full\n");
        return;
    }
    s->data[++(s->top)] = item;
}

int pop(Stack* s) {
    if (is_empty_stack(s)) {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }
    return s->data[(s->top)--];
}

int main() {
    int choice;
    char input[MAX_QUEUE_SIZE];

    QueueType q;
    Stack s;
    init_queue(&q);
    init_stack(&s);

    while (1) {
        printf("1. 회문 입력\n");
        printf("2. 회문 검사\n");
        printf("3. 종료\n");
        printf("메뉴 선택: ");
        scanf("%d", &choice);
        while (getchar() != '\n');

        switch (choice) {
        case 1:
            printf("회문을 입력하세요: ");
            scanf("%s", input);
            for (int i = 0; i < strlen(input); i++) {
                enqueue(&q, input[i]);
                push(&s, input[i]);
            }
            break;
        case 2:
            while (!is_empty_queue(&q)) {
                if (dequeue(&q) != pop(&s)) {
                    printf("회문이 아닙니다.\n");
                    break;
                }
            }
            if (is_empty_queue(&q))
                printf("회문입니다.\n");
            break;
        case 3:
            exit(0);
        default:
            printf("잘못된 메뉴 선택\n");
            break;
        }
    }

    return 0;
}