#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義 linked list 節點
typedef struct Node {
    char data;
    int count;
    struct Node* next;
} Node;

// 新增節點到 linked list
Node* addNode(Node* head, char ch) {
    // 忽略換行符和製表符
    if (ch == '\n' || ch == '\t') {
        return head;
    }
    
    Node* current = head;
    Node* prev = NULL;

    // 檢查是否字元已存在
    while (current != NULL) {
        if (current->data == ch) {
            current->count++;
            return head;
        }
        prev = current;
        current = current->next;
    }

    // 如果字元不存在，新增新節點
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ch;
    newNode->count = 1;
    newNode->next = NULL;

    if (prev == NULL) {
        return newNode;
    } else {
        prev->next = newNode;
    }

    return head;
}

// 列印 linked list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%c : %d\n", current->data, current->count);
        current = current->next;
    }
}

// 釋放 linked list 記憶體
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    FILE *file = fopen(__FILE__, "r"); // 打開自身檔案
    if (file == NULL) {
        printf("無法開啟檔案\n");
        return 1;
    }

    Node* head = NULL;
    char ch;

    // 逐字元讀取檔案內容
    while ((ch = fgetc(file)) != EOF) {
        head = addNode(head, ch);
    }

    fclose(file); // 關閉檔案

    // 印出 linked list 內容
    printList(head);

    // 釋放記憶體
    freeList(head);

    return 0;
}
