#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int row, col;
    int value;
    struct Node* nextRow;
    struct Node* nextCol;
} Node;

Node* createNode(int row, int col, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->row = row;
    newNode->col = col;
    newNode->value = value;
    newNode->nextRow = NULL;
    newNode->nextCol = NULL;
    return newNode;
}

void insertNode(Node** rowHead, Node** colHead, int row, int col, int value) {
    Node* newNode = createNode(row, col, value);

    if (rowHead[row] == NULL || col < rowHead[row]->col) {
        newNode->nextRow = rowHead[row];
        rowHead[row] = newNode;
    } else {
        Node* temp = rowHead[row];
        while (temp->nextRow != NULL && temp->nextRow->col < col) {
            temp = temp->nextRow;
        }
        newNode->nextRow = temp->nextRow;
        temp->nextRow = newNode;
    }

    if (colHead[col] == NULL || row < colHead[col]->row) {
        newNode->nextCol = colHead[col];
        colHead[col] = newNode;
    } else {
        Node* temp = colHead[col];
        while (temp->nextCol != NULL && temp->nextCol->row < row) {
            temp = temp->nextCol;
        }
        newNode->nextCol = temp->nextCol;
        temp->nextCol = newNode;
    }
}

void printSparseMatrix(Node** rowHead, int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        Node* current = rowHead[i];
        for (int j = 0; j < cols; ++j) {
            if (current != NULL && current->col == j) {
                printf("%d ", current->value);
                current = current->nextRow;
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }
}

// Função para calcular o número de bombas ao redor de uma célula
int countBombsAround(Node** rowHead, int row, int col) {
    int count = 0;

    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < row && j >= 0 && j < col) {
                Node* current = rowHead[i];
                while (current != NULL && current->col <= j) {
                    if (current->col == j && current->value == -1) {
                        ++count;
                    }
                    current = current->nextRow;
                }
            }
        }
    }

    return count;
}

int main() {
    int rows, cols, numBombs;

    printf("Digite o número de linhas e colunas: ");
    scanf("%d %d", &rows, &cols);

    Node** rowHead = (Node**)malloc(rows * sizeof(Node*));
    Node** colHead = (Node**)malloc(cols * sizeof(Node*));

    for (int i = 0; i < rows; ++i) {
        rowHead[i] = NULL;
    }

    for (int i = 0; i < cols; ++i) {
        colHead[i] = NULL;
    }

    printf("Digite o número de bombas: ");
    scanf("%d", &numBombs);

    for (int i = 0; i < numBombs; ++i) {
        int row, col;
        printf("Digite a posição da bomba %d (linha coluna): ", i + 1);
        scanf("%d %d", &row, &col);
        insertNode(rowHead, colHead, row, col, -1);
    }

    printf("\nCampo Minado:\n");

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (rowHead[i] != NULL && rowHead[i]->col == j && rowHead[i]->value == -1) {
                printf("* ");
            } else {
                int bombsAround = countBombsAround(rowHead, i, j);
                printf("%d ", bombsAround);
            }
        }
        printf("\n");
    }

    // Liberação de memória
    for (int i = 0; i < rows; ++i) {
        Node* current = rowHead[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->nextRow;
            free(temp);
        }
    }

    for (int i = 0; i < cols; ++i) {
        Node* current = colHead[i];
        while (current != NULL) {
            Node* temp = current;
            current = current->nextCol;
            free(temp);
        }
    }

    free(rowHead);
    free(colHead);

    return 0;
}
