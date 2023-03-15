//
//  main.c
//  AlgoritmaAnalizi_Proje
//
//  Created by Onat Duman on 2.01.2023.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* color[] = {
    "INVALID", "Kirmizi", "Mavi", "Yesil", "Beyaz", "Siyah", "Mor", "Kahverengi", "Turuncu", "Sari", "Pembe", "Gri", "kirmizi", "mavi", "yesil", "beyaz", "siyah", "mor", "kahverengi", "turuncu", "sari", "pembe", "gri"
};

void printMatrix(int** matrix, int n){
    int i, j;
    char str[20];
    printf("\n");
    for (i=0; i<n; i++) {
        printf("|");
        for (j=0; j<n; j++) {
            strcpy(str, color[matrix[i][j]]);
            printf(" %10s |", str);
        }
        printf("\n");
    }
}

int getColorIndex(char str[20]){
    int n = 23;
    int index = 0;
    while (index<n != 0 && strcmp(str, color[index])) {
        index++;
    }
    if(index == n){
        printf("\nOlmayan bir renk girdiniz.\n");
        return 0;
    }
    return index;
}

void shift(int** matrix, int n, int row){
    int tmp, i;
    tmp = matrix[row][n-1];
    for (i=n-1; i>0; i--) {
        matrix[row][i] = matrix[row][i-1];
    }
    matrix[row][0] = tmp;
}

int checkAbove(int** matrix, int n, int row){
    int i, j;
    int unique = 0;
    for (i=0; i<row; i++) {
        for (j=0; j<n; j++) {
            if(matrix[row][j] == matrix[i][j]){
                unique = 1;
            }
        }
    }
    return unique;
}

int fixMatrix(int** matrix, int n, int row, int sum, int local){
    int i;
    int unique = 0;
    if(row < n && local <= sum){
        unique = checkAbove(matrix, n, row);
        if(unique == 1){
            i = 0;
            while (i<n && unique == 1) {
                shift(matrix, n, row);
                unique = checkAbove(matrix, n, row);
                i++;
            }
            unique = 0;
            if(i == n){
                unique = 1;
            }else{
                unique = fixMatrix(matrix, n, row+1,  sum, local + matrix[row][0]);
            }
        }else{
            unique = fixMatrix(matrix, n, row+1, sum, local + matrix[row][0]);
        }
    }
    return unique;
}

int fixMatrixForDetailedMod(int** matrix, int n, int row, int sum, int local){
    int i;
    int unique = 0;
    if(row < n && local <= sum){
        unique = checkAbove(matrix, n, row);
        if(unique == 1){
            i = 0;
            while (i<n && unique == 1) {
                shift(matrix, n, row);
                printf("\n%d. satir kaydirildi.\n", row+1);
                printMatrix(matrix, n);
                unique = checkAbove(matrix, n, row);
                i++;
            }
            unique = 0;
            if(i == n){
                unique = 1;
            }else{
                unique = fixMatrixForDetailedMod(matrix, n, row+1,  sum, local + matrix[row][0]);
            }
        }else{
            unique = fixMatrixForDetailedMod(matrix, n, row+1, sum, local + matrix[row][0]);
        }
    }
    return unique;
}

int main(int argc, const char * argv[]) {
    int tmp, i, j, n, sum = 0;
    int** matrix = NULL;
    int choice = 0;
    char str[20];
    while (choice != 3) {
        printf("(1)-Normal mod\n(2)-Detay mod\n(3)-Cikis\n");
        scanf(" %d", &choice);
        if(choice == 1){
            printf("Matris buyuklugunu giriniz: ");
            scanf(" %d", &n);
            matrix = (int**)malloc(sizeof(int*) * n);
            for (i=0; i<n; i++) {
                matrix[i] = (int*)malloc(sizeof(int) * n);
            }
            for (i=0; i<n; i++) {
                sum = 0;
                for (j=0; j<n; j++) {
                    printf("%d.satir %d.sutundaki rengi giriniz: ", i+1, j+1);
                    scanf(" %s", str);
                    matrix[i][j] = getColorIndex(str);
                    sum = sum + matrix[i][j];
                }
                printf("\n");
            }
            tmp = fixMatrix(matrix, n, 0, sum, 0);
            if(tmp == 0){
                printMatrix(matrix, n);
            }else{
                printf("\nGirdiginiz matris icin sonuc yoktur.");
            }
            free(matrix);
        }else if (choice == 2){
            printf("Matris buyuklugunu giriniz: ");
            scanf(" %d", &n);
            matrix = (int**)malloc(sizeof(int*) * n);
            for (i=0; i<n; i++) {
                matrix[i] = (int*)malloc(sizeof(int) * n);
            }
            for (i=0; i<n; i++) {
                sum = 0;
                for (j=0; j<n; j++) {
                    printf("%d.satir %d.sutundaki rengi giriniz: ", i+1, j+1);
                    scanf(" %s", str);
                    matrix[i][j] = getColorIndex(str);
                    sum = sum + matrix[i][j];
                }
                printf("\n");
            }
            tmp = fixMatrixForDetailedMod(matrix, n, 0, sum, 0);
            if(tmp == 0){
                printMatrix(matrix, n);
            }else{
                printf("\nGirdiginiz matris icin sonuc yoktur.");
            }
            free(matrix);
        }
        printf("\n\n\n");
    }
    return 0;
}
