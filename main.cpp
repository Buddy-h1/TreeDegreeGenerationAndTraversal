#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h>

using namespace std;

class Tree {
public:
	Tree() {
		root = nullptr;
		size = 0;
	}
	Tree(int num) {
		root = new Node;
		root->key = num;
		size = 1;
		temp.push_back(root);
	}

	int size;

private:
	class Node {
	public:
		Node() {
			key = 0;
			leftRoot = nullptr;
			rightRoot_1 = nullptr;
			rightRoot_2 = nullptr;
			rightRoot_3 = nullptr;
		}

		int key;
		Node* leftRoot;
		Node* rightRoot_1;
		Node* rightRoot_2;
		Node* rightRoot_3;
	};

	void Shift_links_to_the_left(Node* node = nullptr) {
		if (node != nullptr) {
			if (node->leftRoot == nullptr) {
				node->leftRoot = node->rightRoot_1;
				node->rightRoot_1 = node->rightRoot_2;
				node->rightRoot_2 = node->rightRoot_3;
				node->rightRoot_3 = nullptr;
			}
			else if (node->rightRoot_1 == nullptr) {
				node->rightRoot_1 = node->rightRoot_2;
				node->rightRoot_2 = node->rightRoot_3;
				node->rightRoot_3 = nullptr;
			}
			else if (node->rightRoot_2 == nullptr) {
				node->rightRoot_2 = node->rightRoot_3;
				node->rightRoot_3 = nullptr;
			}
			else { return; }
		}
		else { return; }
	}

	void Detour_private(Node* node) {
		if (node == nullptr) { return; }
		cout << node->key << " ";
		Detour_private(node->leftRoot);
		Detour_private(node->rightRoot_1);
		Detour_private(node->rightRoot_2);
		Detour_private(node->rightRoot_3);
	}

	void PrintTree_private(Node* node, int level) {
		if (node) {
			PrintTree_private(node->leftRoot, level + 1);
			for (int i = 0; i < level; i++) { cout << "    "; }
			cout << node->key << endl;
			PrintTree_private(node->rightRoot_1, level + 1);
			PrintTree_private(node->rightRoot_2, level + 1);
			PrintTree_private(node->rightRoot_3, level + 1);
		}
	}

	void additionElements(vector<Node*>& vec1, vector<Node*>& vec2) {
		for (int i = 0; i < vec1.size(); ++i) {
			Sleep(300);
			srand(time(0));
			int count_daughter_element = rand() % 4 + 1;
			if (count_daughter_element == 1) {
				vec1[i]->leftRoot = new Node;
				size++;
				vec1[i]->leftRoot->key = size;
				vec2.push_back(vec1[i]->leftRoot);
			}
			else if (count_daughter_element == 2) {
				vec1[i]->leftRoot = new Node;
				size++;
				vec1[i]->leftRoot->key = size;
				vec2.push_back(vec1[i]->leftRoot);
				vec1[i]->rightRoot_1 = new Node;
				size++;
				vec1[i]->rightRoot_1->key = size;
				vec2.push_back(vec1[i]->rightRoot_1);
			}
			else if (count_daughter_element == 3) {
				vec1[i]->leftRoot = new Node;
				size++;
				vec1[i]->leftRoot->key = size;
				vec2.push_back(vec1[i]->leftRoot);
				vec1[i]->rightRoot_1 = new Node;
				size++;
				vec1[i]->rightRoot_1->key = size;
				vec2.push_back(vec1[i]->rightRoot_1);
				vec1[i]->rightRoot_2 = new Node;
				size++;
				vec1[i]->rightRoot_2->key = size;
				vec2.push_back(vec1[i]->rightRoot_2);
			}
			else if (count_daughter_element == 4) {
				vec1[i]->leftRoot = new Node;
				size++;
				vec1[i]->leftRoot->key = size;
				vec2.push_back(vec1[i]->leftRoot);
				vec1[i]->rightRoot_1 = new Node;
				size++;
				vec1[i]->rightRoot_1->key = size;
				vec2.push_back(vec1[i]->rightRoot_1);
				vec1[i]->rightRoot_2 = new Node;
				size++;
				vec1[i]->rightRoot_2->key = size;
				vec2.push_back(vec1[i]->rightRoot_2);
				vec1[i]->rightRoot_3 = new Node;
				size++;
				vec1[i]->rightRoot_3->key = size;
				vec2.push_back(vec1[i]->rightRoot_3);
			}
		}
		vec1.clear();
	}

	vector<Node*> temp;
	vector<Node*> temp2;

	void RandomGeneration_private(int level) {
		if (temp.size() == 0) {
			temp.push_back(root);
		}
		for (int k = 0; k < level - 1; ++k) {
			if (temp.size() != 0) {
				additionElements(temp, temp2);
			}
			else if (temp2.size() != 0) {
				additionElements(temp2, temp);
			}
		}
	}

	Node* temp_link = nullptr;
	void MoveToElement(int index, Node* node) {
		if (node == nullptr) { return; }
		if (index == node->key) {
			temp_link = node;
			return;
		}
		MoveToElement(index, node->leftRoot);
		MoveToElement(index, node->rightRoot_1);
		MoveToElement(index, node->rightRoot_2);
		MoveToElement(index, node->rightRoot_3);
	}

	Node* temp_link_back = nullptr;
	void MoveToElementBack(Node* node) {
		if (node == nullptr) { return; }
		if ((node->leftRoot == temp_link) || (node->rightRoot_1 == temp_link) ||
			(node->rightRoot_2 == temp_link) || (node->rightRoot_3 == temp_link)) {
			temp_link_back = node;
			return;
		}
		MoveToElementBack(node->leftRoot);
		MoveToElementBack(node->rightRoot_1);
		MoveToElementBack(node->rightRoot_2);
		MoveToElementBack(node->rightRoot_3);
	}

	Node* GoLeaf(Node* node) {
		if ((node->leftRoot == nullptr) && (node->rightRoot_1 == nullptr) &&
			(node->rightRoot_2 == nullptr) && (node->rightRoot_3 == nullptr)) {
			return node;
		}
		GoLeaf(node->leftRoot);
	}

	Node* root;

public:

	//Вывод дерева
	void PrintTree() {
		PrintTree_private(root, 0);
	}

	//Прямой обход дерева
	void Detour() {
		Detour_private(root);
	}

	//Рандомная генерация дерева
	void RandomGeneration(int level) {
		delete root;
		root = new Node;
		root->key = 1;
		size = 1;
		temp.clear();
		temp2.clear();
		RandomGeneration_private(level);
	}

	//Добавление элемента
	void Add(int index, int element) {
		MoveToElement(index, root);
		if (temp_link->leftRoot == nullptr) {
			temp_link->leftRoot = new Node;
			size++;
			temp_link->leftRoot->key = element;
		}
		else if (temp_link->rightRoot_1 == nullptr) {
			temp_link->rightRoot_1 = new Node;
			size++;
			temp_link->rightRoot_1->key = element;
		}
		else if (temp_link->rightRoot_2 == nullptr) {
			temp_link->rightRoot_2 = new Node;
			size++;
			temp_link->rightRoot_2->key = element;
		}
		else if (temp_link->rightRoot_3 == nullptr) {
			temp_link->rightRoot_3 = new Node;
			size++;
			temp_link->rightRoot_3->key = element;
		}
		else {
			cout << "Нет места" << endl << endl;
			return;
		}
	}

	//Удаление элемента
	void Delete(int index) {
		MoveToElement(index, root); //temp_link - текущий элемент
		if (temp_link == root) { //Если удаляется корень дерева
			if ((root->leftRoot == nullptr) && (root->rightRoot_1 == nullptr) //Если в дереве только корень
				&& (root->rightRoot_2 == nullptr) && (root->rightRoot_3 == nullptr)) {
				root = nullptr;
				delete temp_link;
				size--;
			}
			else {
				Node* deleteNode = root;
				root = root->leftRoot;
				Node* leaf = GoLeaf(root);
				leaf->leftRoot = deleteNode->rightRoot_1;
				leaf->rightRoot_1 = deleteNode->rightRoot_2;
				leaf->rightRoot_2 = deleteNode->rightRoot_3;
				delete deleteNode;
				size--;
			}
		}
		else if (temp_link->leftRoot == nullptr) { /*Если самый левый
			элемент пустой, значит остальные тоже пустые,
			а значит это ЛИСТ дерева*/
			MoveToElementBack(root); //temp_link_back - родитель элемента temp_link

			if (temp_link_back->leftRoot == temp_link) { temp_link_back->leftRoot = nullptr; }
			else if (temp_link_back->rightRoot_1 == temp_link) { temp_link_back->rightRoot_1 = nullptr; }
			else if (temp_link_back->rightRoot_2 == temp_link) { temp_link_back->rightRoot_2 = nullptr; }
			else if (temp_link_back->rightRoot_3 == temp_link) { temp_link_back->rightRoot_3 = nullptr; }

			Shift_links_to_the_left(temp_link_back);
			delete temp_link;
			size--;
		}
		else { //Иначе это НЕ ЛИСТ дерева
			MoveToElementBack(root);
			Node* deleteNode = temp_link;
			if (temp_link_back->leftRoot == temp_link) { temp_link_back->leftRoot = temp_link->leftRoot; }
			else if (temp_link_back->rightRoot_1 == temp_link) { temp_link_back->rightRoot_1 = temp_link->leftRoot; }
			else if (temp_link_back->rightRoot_2 == temp_link) { temp_link_back->rightRoot_2 = temp_link->leftRoot; }
			else if (temp_link_back->rightRoot_3 == temp_link) { temp_link_back->rightRoot_3 = temp_link->leftRoot; }
			Node* leaf = GoLeaf(temp_link);
			leaf->leftRoot = deleteNode->rightRoot_1;
			leaf->rightRoot_1 = deleteNode->rightRoot_2;
			leaf->rightRoot_2 = deleteNode->rightRoot_3;
			delete deleteNode;
			size--;
		}
	}

	//Количество элементов в дереве
	int GetSize() {
		return size;
	}
};

void PrintMenu() {
	cout << "Выберите команду:" << endl;
	cout << "[1] - Сгенерировать случайное дерево" << endl;
	cout << "[2] - Вывод дерева" << endl;
	cout << "[3] - Прямой обход дерева" << endl;
	cout << "[4] - Добавить элемент" << endl;
	cout << "[5] - Удалить элемент" << endl;
	cout << "[6] - Количество элементов в дереве" << endl;
}

int main() {
	setlocale(LC_ALL, "Russian");
	Tree tree = 1;
	int command = 0;
	PrintMenu();
	while (cin >> command) {
		if (command == 1) {
			int level;
			cout << "Введите уровень дерева: ";
			cin >> level;
			cout << endl;
			tree.RandomGeneration(level);
		}
		else if (command == 2) {
			cout << endl;
			tree.PrintTree();
		}
		else if (command == 3) {
			cout << endl;
			tree.Detour();
			cout << endl << endl;
		}
		else if (command == 4) {
			int index;
			cout << "Введите позицию: ";
			cin >> index;
			int element;
			cout << "Введите элемент: ";
			cin >> element;
			cout << endl;
			tree.Add(index, element);
		}
		else if (command == 5) {
			int index;
			cout << "Введите элемент: ";
			cin >> index;
			cout << endl;
			tree.Delete(index);
		}
		else if (command == 6) {
			cout << endl << "Размер дерева: " << tree.GetSize() << endl << endl;
		}
		PrintMenu();
	}
}