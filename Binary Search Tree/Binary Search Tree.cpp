// Binary Search Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;
struct Node {

    struct Node* lchild; //Hijo Izquierdo
    struct Node* rchild; //Hijo Derecho
    int data; // El dato del nodo;
}* root = NULL;

void Insert(int key) { // Insertar sin Recursividad

    struct Node* t = root;
    struct Node* r = NULL;
    struct Node* p = NULL;

    if (root == NULL) {
        p = (struct Node*)malloc(sizeof(struct Node));
        p->data = key;
        p->lchild = p->rchild = NULL;
        root = p;
        return;
    }
    while (t != NULL) {
        r = t;
        if (key < t->data)
            t = t->lchild;
        else if (key > t->data)
            t = t->rchild;
        else
            return;
    }
    p = (struct Node*)malloc(sizeof(struct Node));
    p->data = key;
    p->lchild = p->rchild = NULL;

    if (key < r->data) r->lchild = p;
    else r->rchild = p;

}
void Inorder(struct Node* p) {
    
    if (p) {

        printf("Los elementos son:\n");
        Inorder(p->lchild);
        printf("%d\n", p->data);
        Inorder(p->rchild);
    }
}

struct Node* Search(int key) {
    struct Node* t = root;

    while (t != NULL) {
        if (key == t->data)
            return t;
        else if (key < t->data)
            t = t->lchild;
        else
            t = t->rchild;
    }
    return NULL;
}

struct Node* RInsert(struct Node* p, int key) { // Insertar Recursivo

    struct Node* t = NULL;
    if (p == NULL) {
        t = (struct Node *)malloc(sizeof(struct Node));
        t->data = key;
        t->lchild = t->rchild = NULL;
        return t;
    }
    if (key < p->data)
        p->lchild = RInsert(p->lchild, key);
    else if (key > p->data)
        p->rchild = RInsert(p->rchild, key);
    return p;

}
int Height(struct Node* p) {
    int x, y;;
    if (p == NULL) return 0;
    x = Height(p->lchild);
    y = Height(p->rchild);
    return x > y ? x + 1 : y + 1;
}

struct Node* InPre(struct Node* p) {
    while (p && p->rchild != NULL)
        p = p->rchild;
    return p;
}
struct Node* InSucc(struct Node* p) {
    while (p && p->lchild != NULL)
        p = p->lchild;
    return p;
}
struct Node* Delete(struct Node* p, int key) {

    struct Node* q;
    if (p == NULL)
        return NULL;
    if (p->lchild == NULL && p->rchild == NULL) {

        if (p == root)
            root = NULL;
        free(p);
        return NULL;
    }
    if (key < p->data)
        p-> lchild = Delete(p->lchild,key);
    else if (key > p->data)
        p-> rchild = Delete(p->rchild, key);
    else {
        if (Height(p->lchild) > Height(p->rchild)) {
            q = InPre(p->lchild);
            p->data = q->data;
            p->lchild = Delete(p->lchild, q->data);
        }
        else {
            q = InSucc(p->rchild);
            p->data = q->data;
            p->rchild = Delete(p->rchild, q->data);
        }
            
    }
    return p;
}
int main()
{
    struct Node* temp;
    int ans, number;
    do {
        system("cls");
        printf("Elija que desea hacer\n");
        printf("1 - Insertar Elementos\n");
        printf("2 - Eliminar Elementos\n");
        printf("3 - Buscar Elementos\n");
        printf("4 - Mostrar Arbol\n");
        printf("5 - Salir\n\nRespuesta: ");

        cin >> ans;

        switch (ans)
        {
        case 1:
            system("cls");
            printf("Introduzca el numero que desea Insertar: ");
            cin >> number;
            root = RInsert(root, number);
            break;
        case 2:
            system("cls");
            printf("Introduzca el numero que desea Eliminar: ");
            cin >> number;
            if (Delete(root, number) != NULL) printf("Se ha eliminado el valor %d", number);
            else printf("El valor %d no esta dentro del arbol", number);
            printf("");
            break;
        case 3:
            system("cls");
            printf("Introduzca el numero que desea Buscar: ");
            cin >> number;
            if (Search(number) != NULL) 
                cout << "El numero " << number << " se ha encontrado!";
            else 
                cout << "No se encuentra dicho numero";
            break;
        case 4:
            Inorder(root);
            break;

        default:
            cout << "No es una opcion!";
            
            break;
        }
        cout << ""<<endl;
        system("pause");
    } while (ans!=5);
}
