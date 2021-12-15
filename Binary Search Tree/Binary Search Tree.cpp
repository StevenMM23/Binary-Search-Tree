//Steven Martinez
#include <iostream>

using namespace std;

struct Node
{
	Node* lchild; //Hijo Izquierdo
	Node* rchild; //Hijo Derecho
	int data; // El dato del nodo;
}* root = nullptr; // Declaracion de la raiz

void insert(int key)
{
	// Insertar sin Recursividad

	Node* temp = root; // Nodo Temporal
	Node* insertNode= nullptr; // Nodo que se va a insertar
	Node* p = nullptr; // Se usa para crear new Node()

	if (root == nullptr) // Si no hay nodos....
	{
		p = new Node(); // Se crea un nodo
		p->data = key; // Se le asigna el dato del parametro
		p->lchild = p->rchild = nullptr; // Sus hijos apuntan a nulo
		root = p; // Raiz ahora es p (El primer nodo)
		return;
	}
	while (temp != nullptr) // Mientras temp sea diferente de NULL (Recordando que se iguala a root)
	{
		insertNode = temp; // Nodo que se insertara se iguala a temp (Raiz)
		if (key < temp->data) // Si numero es menor al dato de temp
			temp = temp->lchild; 
		else if (key > temp->data) // SI el numero es mayor al dato de temp
			temp = temp->rchild;
		else
			return;
	} // Al finalizar el While, estaremos en la capa que se insertará el key (Nuevo valor)

	//Se crea un nuevo nodo y se le asigna a p el valor del parametro y sus hijos estaran apuntando a NULLPTR
	p = new Node();
	p->data = key; 
	p->lchild = p->rchild = nullptr;

	// Se determina si el valor introducido ira a la izquierda (Menores) o a la derecha (Mayores)
	if (key < insertNode->data) insertNode->lchild = p;
	else insertNode->rchild = p;
}

void Inorder(Node* p)
{
	if (p)
	{
		
		Inorder(p->lchild);
		printf("%d\n", p->data);
		Inorder(p->rchild);
	}
}

Node* search(int key) // Metodo para buscar un numero dentro del arbol
{
	Node* t = root; // Se crea un nodo t y se iguala a root (El inicio del arbol)

	while (t != nullptr) // Mientras el nodo t, no este aputando a NULL
	{
		if (key == t->data) // Si el key es igual al dato que guarda t....
			return t;
		if (key < t->data) // Si el key es menor al dato que guarda t muevete al hijo izquierdo
			t = t->lchild;
		else
			t = t->rchild; // SI el key es mayor al dato que guarda t mueve al hijo derecho
	}
	return nullptr; //Si no se encuentra nada retorname NULLPTR;
}

Node* RInsert(Node* p, int key) //Insertar Nodo con metodo Recursivo
{
	if (p == nullptr) // Si no hay ningun nodo introducido previamente...
	{
		Node* temp = nullptr; //No tiene porque apuntar a NULL pero es buena práctica
		temp = new Node(); // Se crea un Nodo (Espacio en la memoria)
		temp->data = key; // Se le asigna al nodo el valor key (Parametro) a data;
		temp->lchild = temp->rchild = nullptr; //Los hijos del Nodo temp apuntan a nulo
		return temp;
	}
	if (key < p->data) // Si no es nulo entonces...
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
			printf("Los elementos son:\n");
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
