#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node *start = NULL;

void radix_sort(FILE *file);
int larger_digit();
int digit_finder(int number, int k);

int main(void) {
    struct node *temp, *x;
    int count, limit = 1, element;
    char temp_char;
    FILE *fptr;

    fptr = fopen("..\\read.txt", "r+");

    if(fptr == NULL) {
        printf("ERROR 00");
        return 0;
    }

    while((temp_char = fgetc(fptr)) != EOF) {
        if(temp_char == '\n')
            limit++;
    }

    fclose(fptr);
    fptr = fopen(".\\read.txt", "r+");

    for(count = 0; count < limit; count++) {
        fscanf(fptr, "%d", &element);
        temp = malloc(sizeof(struct node));
        temp->data = element;
        temp->link = NULL;

        if(start == NULL) {
            start = temp;
        }
        else {
            x = start;
            while(x->link != NULL) {
                x = x->link;
            }
            x->link = temp;
        }
    }
    fclose(fptr);

    fptr = fopen(".\\write.txt", "w+");
    radix_sort(fptr);
    printf("Sorted List\n");
    x = start;

    while(x != NULL) {
        printf("%3d ", x->data);
        x = x->link;
    }
    printf("\n");
    return 0;
}

void radix_sort(FILE *file) {
    int count, k, digit, least_significant, most_significant;
    struct node *rear[10], *front[10], *p;
    least_significant = 1;
    most_significant = larger_digit(start);
    for(k = least_significant; k <= most_significant; k++) {
        for(count = 0; count <= 9; count++) {
            rear[count] = NULL;
            front[count] = NULL ;
        }

        for(p = start; p != NULL; p = p->link) {
            digit = digit_finder(p->data, k);
            if(front[digit] == NULL) {
                front[digit] = p;
            }
            else {
                rear[digit]->link = p;
            }
            rear[digit] = p;
            fprintf(file, "%d ", p->data);
        }
        fprintf(file, "\n");

        count = 0;
        while(front[count] == NULL) {
            count++;
        }
        start = front[count];
        while(count < 9) {
            if(rear[count + 1] != NULL) {
                rear[count]->link = front[count + 1];
            }
            else {
                rear[count + 1] = rear[count];
            }
            count++;
        }
        rear[9]->link = NULL;
    }
}

int larger_digit() {
    struct node *p = start;
    int temp = 0, digit = 0;
    while(p != NULL) {
        if(p ->data > temp) {
            temp = p->data;
        }
        p = p->link ;
    }
    while(temp != 0) {
        digit++;
        temp = temp / 10;
    }
    return(digit);
}

int digit_finder(int number, int k) {
    int term, count;
    for(count = 1; count <= k; count++) {
        term = number % 10;
        number = number / 10;
    }
    return(term);
}
