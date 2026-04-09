#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef enum {
    OMG,
    LOL,
    ROFL,
    LMAO,
    BRB,
    AFK
} Meme;

const char* memeNames[] = {
    "OMG",
    "LOL",
    "ROFL",
    "LMAO",
    "BRB",
    "AFK"
};

const int MEME_COUNT = 6;

typedef struct TreeNode {
    Meme data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(Meme value) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

TreeNode* insert(TreeNode* root, Meme value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Значение %s уже есть в дереве!\n", memeNames[value]);
    }
    return root;
}

TreeNode* findMin(TreeNode* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

TreeNode* deleteNode(TreeNode* root, Meme value) {
    if (root == NULL) {
        printf("Узел не найден.\n");
        return NULL;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void visualize(TreeNode* root, int depth) {
    if (root == NULL) return;

    visualize(root->right, depth + 1);

    for (int i = 0; i < depth; i++) {
        printf("    ");
    }
    printf("%s\n", memeNames[root->data]);

    visualize(root->left, depth + 1);
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int isLinearList(TreeNode* root) {
    if (root == NULL) return 1;

    if (root->left != NULL && root->right != NULL) {
        return 0;
    }

    if (root->left != NULL) {
        return isLinearList(root->left);
    }
    if (root->right != NULL) {
        return isLinearList(root->right);
    }
    return 1;
}

Meme stringToMeme(char* str) {
    for (int i = 0; str[i]; i++) {
        str[i] = toupper(str[i]);
    }
    
    for (int i = 0; i < MEME_COUNT; i++) {
        if (strcmp(str, memeNames[i]) == 0) {
            return (Meme)i;
        }
    }
    return OMG;
}

int main() {
    TreeNode* root = NULL;
    int choice;
    char input[20];
    Meme value;

    do {
        printf("\n=== МЕНЮ ===\n");
        printf("1. Добавить узел\n");
        printf("2. Визуализировать дерево\n");
        printf("3. Удалить узел\n");
        printf("4. Проверить, является ли дерево линейным списком вершин\n");
        printf("5. Выйти\n");
        printf("Выбор: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Введите значение (OMG, LOL, ROFL, LMAO, BRB, AFK): ");
                scanf("%s", input);
                value = stringToMeme(input);
                root = insert(root, value);
                break;
            case 2:
                printf("\nВизуализация дерева:\n");
                visualize(root, 0);
                break;
            case 3:
                printf("Введите значение для удаления: ");
                scanf("%s", input);
                value = stringToMeme(input);
                root = deleteNode(root, value);
                break;
            case 4:
                if (isLinearList(root)) {
                    printf("ДА, дерево является линейным списком вершин.\n");
                } else {
                    printf("НЕТ, дерево НЕ является линейным списком вершин.\n");
                }
                break;
            case 5:
                printf("До свидания!\n");
                break;
            default:
                printf("Неверный выбор!\n");
        }
    } while (choice != 5);

    freeTree(root);
    return 0;
}