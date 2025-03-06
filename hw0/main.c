#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義鏈結串列節點結構
typedef struct Node {
    char character;
    int value;       // ASCII值
    struct Node* next;
} Node;

// 新增節點到鏈結串列
void addNode(Node** head, char c) {
    // 建立新節點
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("記憶體分配失敗！\n");
        exit(1);
    }
    
    newNode->character = c;
    newNode->value = (int)c;  // 取得字元的ASCII值
    newNode->next = NULL;
    
    // 如果鏈結串列為空，新節點成為頭節點
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    
    // 否則，找到最後一個節點並連接新節點
    Node* current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = newNode;
}

// 輸出鏈結串列中的所有節點
void printList(Node* head) {
    Node* current = head;
    
    while (current != NULL) {
        printf("%c : %d\n", current->character, current->value);
        current = current->next;
    }
    printf("...........\n");
}

int main() {
    Node* head = NULL;
    char name[100];
    
    printf("請輸入你的名字: ");
    scanf("%s", name);
    
    // 將每個字元添加到鏈結串列
    for (int i = 0; i < strlen(name); i++) {
        addNode(&head, name[i]);
    }
    
    // 輸出鏈結串列
    printList(head);
    
    // 釋放鏈結串列記憶體
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    
    return 0;
}
