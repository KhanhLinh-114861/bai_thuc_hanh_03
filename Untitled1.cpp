#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char hoten[30];
    int masv;
    float d1, d2, d3;
} Data;

typedef struct tagNode {
    Data infor;
    struct tagNode *link;
} Node;

typedef struct {
    Node *pHead;
    Node *pTail;
    int spt;
} LList;

/////////////////////////////////////
void initList(LList *L) {
    L->pHead = NULL;
    L->pTail = NULL;
    L->spt = 0;
}
/////////////////////////////////////
int emptyList(LList L) {
    return (L.spt == 0);
}
/////////////////////////////////////
void insert_Head(LList *L, Data x) {
    Node *pp;
    pp = (Node*) malloc(sizeof(Node));
    pp->infor = x;
    pp->link = NULL;
    if (emptyList(*L)) {
        L->pHead = pp;
        L->pTail = pp;
    } else {
        pp->link = L->pHead;
        L->pHead = pp;
    }
    L->spt++;
}
/////////////////////////////////////
void insert_Tail(LList *L, Data x) {
    Node *pp = (Node*) malloc(sizeof(Node));
    pp->infor = x;
    pp->link = NULL;
    if (emptyList(*L)) L->pHead = pp;
    else L->pTail->link = pp;
    L->pTail = pp;
    L->spt++;
}
/////////////////////////////////////
Node* search_ByMa(LList L, int ma) {
    Node *p = L.pHead;
    while (p != NULL && p->infor.masv != ma) p = p->link;
    return p;
}

Node* search_ByTen(LList L, char ten[]) {
    Node *p = L.pHead;
    while (p != NULL && strcmp(p->infor.hoten, ten) != 0) p = p->link;
    return p;
}
/////////////////////////////////////
void delete_ByMa(LList *L, int ma) {
    Node *p = L->pHead, *q = NULL;
    while (p != NULL && p->infor.masv != ma) { q = p; p = p->link; }
    if (p == NULL) return;
    if (q == NULL) L->pHead = p->link;
    else q->link = p->link;
    if (p == L->pTail) L->pTail = q;
    free(p);
    L->spt--;
}

void delete_ByTen(LList *L, char ten[]) {
    Node *p = L->pHead, *q = NULL;
    while (p != NULL && strcmp(p->infor.hoten, ten) != 0) { q = p; p = p->link; }
    if (p == NULL) return;
    if (q == NULL) L->pHead = p->link;
    else q->link = p->link;
    if (p == L->pTail) L->pTail = q;
    free(p);
    L->spt--;
}
/////////////////////////////////////
void sort_ByTen(LList *L) {
    Node *i, *j;
    Data t;
    for (i = L->pHead; i != NULL; i = i->link)
        for (j = i->link; j != NULL; j = j->link)
            if (strcmp(i->infor.hoten, j->infor.hoten) > 0) {
                t = i->infor; i->infor = j->infor; j->infor = t;
            }
}
/////////////////////////////////////
/* tach L thanh L1 (diem TB >= 5) va L2 (diem TB < 5) */
void tachDS(LList L, LList *L1, LList *L2) {
    Node *p = L.pHead;
    initList(L1);
    initList(L2);
    while (p != NULL) {
        if ((p->infor.d1 + p->infor.d2 + p->infor.d3) / 3 >= 5)
            insert_Tail(L1, p->infor);
        else
            insert_Tail(L2, p->infor);
        p = p->link;
    }
}
void ghepDS(LList *L1, LList L2) {
    Node *p = L2.pHead;
    while (p != NULL) {
        insert_Tail(L1, p->infor);
        p = p->link;
    }
}
///////////////////////////////////////
void nhap(Data *x) {
    printf("Nhap ma sv: ");
    scanf("%d", &(x->masv));
    if (x->masv > 0) {
        printf("Nhap ho ten: ");
        scanf(" %29[^\n]", x->hoten);
        printf("Nhap diem mon 1: ");
        scanf("%f", &(x->d1));
        printf("Nhap diem mon 2: ");
        scanf("%f", &(x->d2));
        printf("Nhap diem mon 3: ");
        scanf("%f", &(x->d3));
    }
}

void in(Data x) {
    printf("Ten: %s, Ma: %d, Diem 1: %.2f, Diem 2: %.2f, Diem 3: %.2f\n",
           x.hoten, x.masv, x.d1, x.d2, x.d3);
}

void processList(LList L) {
    Node *pp = L.pHead;
    while (pp != NULL) {
        in(pp->infor);
        pp = pp->link;
    }
}
/////////////////////////////////////////

int main() {
    LList L, L1, L2;
    int kt = 0, chon, ma;
    char ten[30];
    Data x;
    Node *p;
    initList(&L);
    initList(&L1);
    initList(&L2);
    do {
        printf("\nChuong trinh lam viec voi DSLK don SV\n");
        printf("\n1: Them nut vao dau danh sach");
        printf("\n2: Them nut vao cuoi danh sach");
        printf("\n3: Xoa theo ma");
        printf("\n4: Xoa theo ten");
        printf("\n5: Tim theo ma");
        printf("\n6: Tim theo ten");
        printf("\n7: Sap xep theo ten");
        printf("\n8: Tach ds (diem TB >= 5 / < 5)");
        printf("\n9: Duyet ds");
        printf("\n10: Ghep ds 2 vao ds 1 (sau khi tach)");
        printf("\n0: Thoat");
        printf("\nMoi ban chon: ");
        scanf("%d", &chon);
        switch (chon) {
        case 1:
            nhap(&x);
            if (x.masv > 0) insert_Head(&L, x);
            break;
        case 2:
            nhap(&x);
            if (x.masv > 0) insert_Tail(&L, x);
            break;
        case 3:
            printf("Nhap ma: ");
            scanf("%d", &ma);
            delete_ByMa(&L, ma);
            break;
        case 4:
            printf("Nhap ten: ");
            scanf(" %29[^\n]", ten);
            delete_ByTen(&L, ten);
            break;
        case 5:
            printf("Nhap ma: ");
            scanf("%d", &ma);
            p = search_ByMa(L, ma);
            if (p != NULL) in(p->infor);
            else printf("Khong thay\n");
            break;
        case 6:
            printf("Nhap ten: ");
            scanf(" %29[^\n]", ten);
            p = search_ByTen(L, ten);
            if (p != NULL) in(p->infor);
            else printf("Khong thay\n");
            break;
        case 7:
            sort_ByTen(&L);
            break;
        case 8:
            tachDS(L, &L1, &L2);
            printf("--- DS 1 (dat) ---\n");
            processList(L1);
            printf("--- DS 2 (khong dat) ---\n");
            processList(L2);
            break;
        case 9:
            processList(L);
            break;
        case 10:
            ghepDS(&L1, L2);
            printf("--- DS sau khi ghep ---\n");
            processList(L1);
            break;
        case 0:
            printf("Bye bye\n");
            kt = 1;
        }
    } while (kt == 0);
    return 0;
}
