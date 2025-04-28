#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node *link;
};

struct node* last = NULL;

void create() {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("\nMemory not available right now\n");
        return;
    }
    printf("\nEnter first element of Circular Linked List: ");
    scanf("%d", &temp->data);
    last = temp;
    temp->link = temp;
    printf("\nCircular Linked List created successfully\n");
}

void insert_first() {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("\nMemory not available right now\n");
        return;
    }
    printf("\nEnter data: ");
    scanf("%d", &temp->data);
    temp->link = last->link;
    last->link = temp;
    printf("\nData inserted successfully at first\n");
}

void insert_end() {
    struct node *temp;
    temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("\nMemory not available right now\n");
        return;
    }
    printf("\nEnter data to be inserted at end: ");
    scanf("%d", &temp->data);
    temp->link = last->link;
    last->link = temp;
    last = temp;
    printf("\nData inserted successfully at end\n");
}

void insert_atposition() {
    int pos, count = 1;
    printf("\nEnter position where you want to insert data: ");
    scanf("%d", &pos);

    if(pos <= 0) {
        printf("\nPosition should be greater than 0\n");
        return;
    }

    if(pos == 1) {
        insert_first();
        return;
    }

    struct node *temp, *q;
    temp = (struct node *)malloc(sizeof(struct node));
    if(temp == NULL) {
        printf("\nMemory not available right now\n");
        return;
    }

    q = last->link;
    while(q != last) {
        count++;
        q = q->link;
    }

    if(count < pos-1) {
        printf("\nPosition out of bound\n");
        free(temp);
        return;
    }

    printf("\nEnter data to insert: ");
    scanf("%d", &temp->data);

    struct node *r = last->link;
    for(int i = 1; i < pos-1; i++) {
        r = r->link;
    }

    temp->link = r->link;
    r->link = temp;
    printf("\nData inserted successfully at position\n");
}

void insert_after() {
    int value, found = 0;
    struct node *q;
    printf("\nEnter value after which you want to insert data: ");
    scanf("%d", &value);

    q = last->link;
    do {
        if(q->data == value) {
            found = 1;
            break;
        }
        q = q->link;
    } while(q != last->link);

    if(found) {
        struct node *temp = (struct node *)malloc(sizeof(struct node));
        if(temp == NULL) {
            printf("\nMemory not available right now\n");
            return;
        }
        printf("\nEnter data to insert: ");
        scanf("%d", &temp->data);
        temp->link = q->link;
        q->link = temp;
        if(q == last) {
            last = temp;
        }
        printf("\nData inserted successfully after %d\n", value);
    } else {
        printf("\n%d not found in the list\n", value);
    }
}

int check() {
    if(last == NULL)
        return 0;
    if(last->link == last) {
        int ch;
        printf("\nOnly one element present. Delete it? (1 for Yes): ");
        scanf("%d", &ch);
        if(ch == 1) {
            free(last);
            last = NULL;
            printf("\nData deleted successfully\n");
        } else {
            printf("\nNo deletion performed\n");
        }
        return 0;
    }
    return 1;
}

void del_first() {
    if(!check())
        return;
    struct node *temp = last->link;
    last->link = temp->link;
    free(temp);
    printf("\nFirst node deleted successfully\n");
}

void del_end() {
    if(!check())
        return;
    struct node *temp = last->link;
    while(temp->link != last) {
        temp = temp->link;
    }
    temp->link = last->link;
    free(last);
    last = temp;
    printf("\nLast node deleted successfully\n");
}

void del_pos() {
    if(!check())
        return;

    int pos, count = 1;
    printf("\nEnter position to delete: ");
    scanf("%d", &pos);

    if(pos <= 0) {
        printf("\nPosition should be greater than 0\n");
        return;
    }

    struct node *q = last->link;
    while(q != last) {
        count++;
        q = q->link;
    }

    if(count < pos) {
        printf("\nPosition out of bound\n");
        return;
    }

    if(pos == 1) {
        del_first();
        return;
    }

    struct node *temp = last->link, *prev = NULL;
    for(int i = 1; i < pos; i++) {
        prev = temp;
        temp = temp->link;
    }
    prev->link = temp->link;
    if(temp == last)
        last = prev;
    free(temp);
    printf("\nNode deleted successfully at position\n");
}

void del_spe() {
    if(!check())
        return;

    int value;
    printf("\nEnter value to delete: ");
    scanf("%d", &value);

    struct node *temp = last->link, *prev = last;
    do {
        if(temp->data == value) {
            if(temp == last->link) {
                del_first();
            } else if(temp == last) {
                del_end();
            } else {
                prev->link = temp->link;
                free(temp);
                printf("\nValue %d deleted successfully\n", value);
            }
            return;
        }
        prev = temp;
        temp = temp->link;
    } while(temp != last->link);

    printf("\nValue %d not found\n", value);
}

void dis() {
    if(last == NULL) {
        printf("\nList is empty\n");
        return;
    }
    struct node *temp = last->link;
    printf("\nCircular Linked List: ");
    do {
        printf("# %d #", temp->data);
        temp = temp->link;
    } while(temp != last->link);
    printf("\n");
}

int main() {
    int k;
    printf("---Circular Linked List---\n");
    while(1) {
        printf("\n1. Create Circular Linked List\n");
        printf("2. Insert data\n");
        printf("3. Delete data\n");
        printf("4. Display list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &k);

        switch(k) {
            case 1:
                if(last == NULL)
                    create();
                else
                    printf("\nCircular Linked List already created\n");
                break;

            case 2:
                if(last == NULL) {
                    printf("\nPlease create the list first\n");
                } else {
                    int l;
                    printf("\n1. Insert at first\n");
                    printf("2. Insert at specific position\n");
                    printf("3. Insert after a value\n");
                    printf("4. Insert at end\n");
                    printf("Enter your choice: ");
                    scanf("%d", &l);

                    switch(l) {
                        case 1: insert_first(); break;
                        case 2: insert_atposition(); break;
                        case 3: insert_after(); break;
                        case 4: insert_end(); break;
                        default: printf("\nInvalid input\n");
                    }
                }
                break;

            case 3:
                if(last == NULL) {
                    printf("\nPlease create the list first\n");
                } else {
                    int p;
                    printf("\n1. Delete first node\n");
                    printf("2. Delete node at specific position\n");
                    printf("3. Delete node with specific value\n");
                    printf("4. Delete last node\n");
                    printf("Enter your choice: ");
                    scanf("%d", &p);

                    switch(p) {
                        case 1: del_first(); break;
                        case 2: del_pos(); break;
                        case 3: del_spe(); break;
                        case 4: del_end(); break;
                        default: printf("\nInvalid input\n");
                    }
                }
                break;

            case 4:
                dis();
                break;

            case 5:
                printf("\nExiting...\n");
                exit(0);

            default:
                printf("\nInvalid input\n");
        }
    }
    return 0;
}
