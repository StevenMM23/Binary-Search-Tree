// Binary Search Tree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

struct Node
{
	Node* lchild; //Hijo Izquierdo
	Node* rchild; //Hijo Derecho
	int data; // El dato del nodo;
}* root = nullptr;

void Insert(int key)
{
	// Insertar sin Recursividad

	Node* t = root;
	Node* r = nullptr;
	Node* p = nullptr;

	if (root == nullptr)
	{
		p = static_cast<Node*>(malloc(sizeof(Node)));
		p->data = key;
		p->lchild = p->rchild = nullptr;
		root = p;
		return;
	}
	while (t != nullptr)
	{
		r = t;
		if (key < t->data)
			t = t->lchild;
		else if (key > t->data)
			t = t->rchild;
		else
			return;
	}
	p = static_cast<Node*>(malloc(sizeof(Node)));
	p->data = key;
	p->lchild = p->rchild = nullptr;

	if (key < r->data) r->lchild = p;
	else r->rchild = p;
}

void Inorder(Node* p)
{
	if (p)
	{
		printf("Los elementos son:\n");
		Inorder(p->lchild);
		printf("%d\n", p->data);
		Inorder(p->rchild);
	}
}

Node* search(int key)
{
	Node* t = root;

	while (t != nullptr)
	{
		if (key == t->data)
			return t;
		if (key < t->data)
			t = t->lchild;
		else
			t = t->rchild;
	}
	return nullptr;
}

Node* RInsert(Node* p, int key)
{
	// Insertar Recursivo

	if (p == nullptr)
	{
		Node* t = nullptr;
		t = static_cast<Node*>(malloc(sizeof(Node)));
		t->data = key;
		t->lchild = t->rchild = nullptr;
		return t;
	}
	if (key < p->data)
		p->lchild = RInsert(p->lchild, key);
	else if (key > p->data)
		p->rchild = RInsert(p->rchild, key);
	return p;
}

int Height(Node* p)
{
	int x, y;
	if (p == nullptr) return 0;
	x = Height(p->lchild);
	y = Height(p->rchild);
	return x > y ? x + 1 : y + 1;
}

Node* InPre(Node* p)
{
	while (p && p->rchild != nullptr)
		p = p->rchild;
	return p;
}

Node* InSucc(Node* p)
{
	while (p && p->lchild != nullptr)
		p = p->lchild;
	return p;
}

Node* Delete(Node* p, int key)
{
	Node* q;
	if (p == nullptr)
		return nullptr;
	if (p->lchild == nullptr && p->rchild == nullptr)
	{
		if (p == root)
			root = nullptr;
		free(p);
		return nullptr;
	}
	if (key < p->data)
		p->lchild = Delete(p->lchild, key);
	else if (key > p->data)
		p->rchild = Delete(p->rchild, key);
	else
	{
		if (Height(p->lchild) > Height(p->rchild))
		{
			q = InPre(p->lchild);
			p->data = q->data;
			p->lchild = Delete(p->lchild, q->data);
		}
		else
		{
			q = InSucc(p->rchild);
			p->data = q->data;
			p->rchild = Delete(p->rchild, q->data);
		}
	}
	return p;
}

int main()
{
	Node* temp;
	int ans, number;
	do
	{
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
			if (Delete(root, number) != nullptr) printf("Se ha eliminado el valor %d", number);
			else printf("El valor %d no esta dentro del arbol", number);
			printf("");
			break;
		case 3:
			system("cls");
			printf("Introduzca el numero que desea Buscar: ");
			cin >> number;
			if (search(number) != nullptr)
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
		cout << "" << endl;
		system("pause");
	}
	while (ans != 5);
}
