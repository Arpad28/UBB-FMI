#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct node {
    char* name;
    struct node* next;
};

struct node* add(struct node *head, char* name) {
    struct node* n;
    struct node* p;

    n = (struct node*)malloc(sizeof(struct node));
    n->name = (char*)malloc((strlen(name)+1)*sizeof(char));
    strcpy(n->name, name);
    n->next = NULL;

    if(head == NULL) {
        return n;
    }

    p = head;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = n;
    return head;
}

int known(struct node* head, char name[]) {
    struct node* p;

    p = head;
    while(p!= NULL && strcmp(p->name,name)!= 0) {
        p = p->next;
    }
    return p != NULL;
}

void clear(struct node* head) {
    if(head == NULL) {
        return;
    }
    clear(head->next);
    free(head->name);
    free(head);
}

int main(int argc, char** argv) {
    char name[64];
    struct node* head=NULL;

    while(scanf("%s", name) == 1) {
        if(known(head, name)) {
            printf("Still around %s, eh?\n", name);
        }
        else {
            head = add(head, name);
            printf("Hello %s\n", name);
        }
    }
    clear(head);
    return 0;
}
szilagyi_arpad@DESKTOP-G2DV9CG:~/exercitii_c/c-test-practice$ ls
hello-remember    matrix-from-binary    matrix-from-text    matrix-to-binary    matrix.bin  names.txt
hello-remember.c  matrix-from-binary.c  matrix-from-text.c  matrix-to-binary.c  matrix.txt
szilagyi_arpad@DESKTOP-G2DV9CG:~/exercitii_c/c-test-practice$ cat matrix-from-binary.c
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    int fd, rows, cols, i, j;
    int** m;

    if(argc <= 1) {
        fprintf(stderr, "No input file specified");
        exit(1);
    }

    fd = open(argv[1],O_RDONLY);
    if(fd ==-1) {
        perror("Failed to open input file");
        exit(1);
    }

    if(read(fd, &rows, sizeof(int)) <= 0) {
        perror("Could not read the number of rows");
        exit(1);
    }

    if(read(fd, &cols, sizeof(int)) <= 0) {
        perror("Could not read the number of columns");
        exit(1);
    }

    m = (int**)malloc(rows*sizeof(int*));
    for(i=0; i<rows; i++) {
        m[i] = (int*)malloc(cols*sizeof(int));
        read(fd, m[i],cols* sizeof(int));
        for(j=0; j<cols; j++) {
            printf("%2d " ,m[i][j]);
        }
        printf("\n");
    }
    for(int i=0;i<rows;++i)
        free(m[i]);
    free(m);

    close(fd);
    return 0;
}