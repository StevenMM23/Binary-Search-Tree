//Steven Martinez
//Alex Bujosa
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

void Inorder(Node* p) // Muestra los numeros en orden ascendente
{
	if (p) // Si p es true (No es null)
	{
		
		Inorder(p->lchild); // Entra al nodo izquierdo hasta llegar a lo mas profundo 
		printf("%d\n", p->data); // Imprime el dato
		Inorder(p->rchild); // Comprueba si hay nodo Derecho
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
	int x, y; // Se crea dos variables (x) y (y)
	if (p == nullptr) return 0; // Si el nodo que se esta evaluando es NULL retorna 0
	x = Height(p->lchild); // Se evalua la altura por la izquierda
	y = Height(p->rchild); // Se evalua la altura por la derecha
	return x > y ? x + 1 : y + 1; // Retorna cual incrementa entre x y y (Izquierda y derecha)
}

Node* InPre(Node* p) // Busca el Sucesor en el lado derecho del arbol Binario...
{
	while (p && p->rchild != nullptr)
		p = p->rchild;
	return p;
}

Node* InSucc(Node* p) // Busca el Sucesor en el lado izquierdo del arbol Binario...
{
	while (p && p->lchild != nullptr)
		p = p->lchild;
	return p;
}

Node* Delete(Node* p, int key) //Se coge como parametro el Root y el numero a eliminar
{
	Node* q; // Se crea el nodo donde una vez eliminado el dato, este se posiciona donde le corresponde
	if (p == NULL) // Si el arbol no tiene nada...
		return NULL;
	if (p->lchild == nullptr && p->rchild == nullptr) // Si el hijo izquierdo y el hijo derecho son null entonces...
	{
		if (p == root) // Si el valor p es el root
			root = nullptr; 
		delete(p);
		return nullptr;
	}
	if (key < p->data) // Si el dato es menor al dato que se esta evaluando en el nodo p
		p->lchild = Delete(p->lchild, key); // p se movera al nodo izquierdo y usará recursividad para evaluar dicho nodo con el dato a eliminar
	else if (key > p->data) // Si el dato es mayor al nodo que se esta evaluando....
		p->rchild = Delete(p->rchild, key); // Se movera al nodo derecho y utilizará recursividad para evualar dicho nodo
	else
	{
		if (Height(p->lchild) > Height(p->rchild))
		{
			q = InPre(p->lchild); //Inorder Predecesor hace que el numero que se elija sea el numero de la rama izquierda
			p->data = q->data;
			p->lchild = Delete(p->lchild, q->data);
		}
		else
		{
			q = InSucc(p->rchild); // Inorder Succesor hace que el numero que se elija sea el numero de la rama derecha 
			p->data = q->data;
			p->rchild = Delete(p->rchild, q->data);
		}
	}
	return p;
}

int main()
{
	Node* temp; // El nodo temp es el nodo que tiene 
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
			Delete(root, number);
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
