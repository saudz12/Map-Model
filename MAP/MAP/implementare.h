#pragma once
#include <iostream>
#include <queue>

template<class K, class D, class Compare = std::less<K>>class Dict {
public:
	using dictType = Dict<K, D, Compare>;

	class node {
	public:
		node* _NIL;
		char col;
		K key;
		D data;
		node* p, * st, * dr;
		node() {
			col = 'R';
			st = nullptr;
			dr = nullptr;
			p = nullptr;
			_NIL = nullptr;
			key = K();
			data = D();
		}
		node*& operator=(node* nod) {
			col = nod->col;
			key = nod->key;
			data = nod->data;
			_NIL = nod->_NIL;

			return (*this);
		}
		node* operator=(D data) {
			this->data = data;
			return this;
		}
	};

	void insert(K, D);
	void Construct(std::vector<std::pair<K, D>>& vec) {
		Clear();
		for (int i = 0; i < vec.size(); i++) {
			K key = vec[i].first;
			D data = vec[i].second;
			insert(key, data);
		}
	}
	void Clear();

	friend class std::queue<node*>;

	Dict& operator=(dictType& toCopy);

	Dict<K, D, Compare>::node*& operator[](K key) {
		node* aux = root;
		while (aux) {
			if (condition(key, aux->key) == 1) {
				if (aux->st == NIL) {
					node* newN = new node;
					newN->p = aux;
					newN->st = NIL;
					newN->dr = NIL;
					newN->key = key;
					aux->st = newN;
					balansare(newN);
					return newN;
				}
				else
					aux = aux->st;
			}
			else if (key == aux->key) {
				return aux;
			}
			else {
				if (aux->dr == NIL) {
					node* newN = new node;
					newN->p = aux;
					newN->st = NIL;
					newN->dr = NIL;
					newN->key = key;
					aux->dr = newN;
					balansare(newN);
					return newN;
				}
				else
					aux = aux->dr;
			}
		}
	}

private:
	node* root, * NIL;
	node* start, * finish;

	Compare condition;

	void insert(node*);

	node* minim(node* nod) {
		node* aux = nod;
		while (aux->st != NIL && aux->st) aux = aux->st;
		return aux;
	}
	node* maxim(node* nod) {
		node* aux = nod;
		while (aux->dr != NIL && aux->dr) aux = aux->dr;
		return aux;
	}

	void rotatieST(node*);
	void rotatieDR(node*);
	void balansare(node*);

public:
	node* succesor(node* nod) {
		if (nod == nullptr || nod == NIL)
			return nullptr;
		if (nod->dr != nullptr && nod->dr != NIL)
			return minim(nod->dr);
		if (nod == root)
			return nullptr;
		node* parent = nod->p, * aux = nod;
		while (parent->st != nod && parent != root) {
			aux = parent;
			parent = aux->p;
			if (parent->st == nod && parent == root)
				return parent;
		}
		if (parent->st == aux)
			return parent;
		if (parent == root)
			return nullptr;
		return parent;
	}
	node* predecesor(node* nod) {
		if (nod == nullptr || nod == NIL)
			return nullptr;
		if (nod->st != nullptr && nod->st != NIL)
			return maxim(nod->st);
		if (nod == root)
			return nullptr;
		node* parent = nod->p, * aux = nod;
		while (parent->dr != nod && parent != root) {
			aux = parent;
			parent = aux->p;
			if (parent->dr == aux && parent == root)
				return parent;
		}
		if (parent->dr == aux)
			return parent;
		if (parent == root)
			return nullptr;
		return parent;
	}
	node* find(K key) {
		node* aux = root;
		while (aux != NIL && aux != nullptr) {
			if (aux->key == key)
				return aux;
			if (condition(aux->key, key) == 1)
				if (aux->dr != NIL && aux->dr != nullptr)
					aux = aux->dr;
				else
					return nullptr;
			else
				if (aux->st != NIL && aux->st != nullptr)
					aux = aux->st;
				else
					return nullptr;
		}
		return nullptr;
	}

	node* begin() {
		return start;
	}
	node* end() {
		return finish;
	}


	class iterator {
		node* nod, * _NIL;
		Compare comp;

	public:
		iterator() {
			nod = nullptr;
			_NIL = nullptr;
		}

		iterator(node* nod) {
			this->nod = nod;
			this->_NIL = nod->_NIL;
		}

		iterator(iterator& it) {
			nod = it->nod;
			_NIL = it->_NIL;
			comp = it->comp;
		}


		iterator& operator++(int) {
			node* _root = nod;
			while (_root->p != _NIL)
				_root = _root->p;

			if (nod == nullptr || nod == _NIL) {
				nod = _NIL;
				return (*this);
			}
			if (nod->dr != nullptr && nod->dr != _NIL) {
				node* aux = nod->dr;
				while (aux->st != _NIL && aux->st) aux = aux->st;
				nod = aux;
				return (*this);
			}
			if (nod == _root) {
				nod = _NIL;
				return (*this);
			}
			node* parent = nod->p, * aux = nod;
			while (parent->st != nod && parent != _root) {
				aux = parent;
				parent = aux->p;
				if (parent->st == nod && parent == _root) {
					nod = parent;
					return (*this);
				}
			}
			if (parent->st == aux) {
				nod = parent;
				return (*this);
			}
			if (parent == _root) {
				nod = _NIL;
				return (*this);
			}

			return (*this);
		}

		iterator& operator=(node*& nod) {
			this->nod = nod;
			return (*this);
		}

		iterator& operator=(iterator& it) {
			this->nod = it->nod;
			return (*this);
		}

		bool operator==(node* nod) {
			return this->nod == nod;
		}

		bool operator==(iterator& it) {
			return nod == it.nod;
		}

		bool operator!=(node* nod) {
			return this->nod != nod;
		}

		bool operator!=(iterator& it) {
			return nod != it.nod;
		}

		K getKey() {
			return nod->key;
		}

		D getData() {
			return nod->data;
		}
	};

	void RSD(node* curr) {
		std::cout << curr->col << ": (" << curr->key << ", " << curr->data << ")\n";
		if (curr->st != NIL && curr->st != nullptr) RSD(curr->st);
		if (curr->dr != NIL && curr->dr != nullptr) RSD(curr->dr);
	}
	void SRD(node* curr) {
		if (curr->st != NIL && curr->st != nullptr) SRD(curr->st);
		std::cout << curr->col << ": (" << curr->key << ", " << curr->data << ")\n";
		if (curr->dr != NIL && curr->dr != nullptr) SRD(curr->dr);
	}
	void SDR(node* curr) {
		if (curr->st != NIL && curr->st != nullptr) RSD(curr->st);
		if (curr->dr != NIL && curr->dr != nullptr) RSD(curr->dr);
		std::cout << curr->col << ": (" << curr->key << ", " << curr->data << ")\n";
	}
	void Nivele() {
		node* aux = root;
		int nivel = 0, cur_lvl = 0, nxt_lvl = 0;
		std::queue<node*> ord;
		if (aux != nullptr && aux != NIL) {
			ord.push(aux);
			std::cout << "Nivel 0: ";
			cur_lvl++;
		}
		while (!ord.empty()) {
			if (cur_lvl == 0) {
				cur_lvl = nxt_lvl;
				nxt_lvl = 0;
				nivel++;
				std::cout << "\nNivel " << nivel << ":";
			}

			aux = ord.front();

			if (aux != nullptr && aux != NIL)
				std::cout << aux->col << ": (" << aux->key << ", " << aux->data << ") | ";

			if (aux->st != nullptr && aux->st != NIL) {
				ord.push(aux->st);
				nxt_lvl++;
			}

			if (aux->dr != nullptr && aux->dr != NIL) {
				ord.push(aux->dr);
				nxt_lvl++;
			}
			cur_lvl--;

			ord.pop();
		}
	}

	void afisare(int care) {
		if (root == nullptr || root == NIL) {
			std::cout << "The tree is empty!\n";
			return;
		}
		switch (care)
		{
		case 1: {
			RSD(root);
			break;
		}
		case 2: {
			SRD(root);
			break;
		}
		case 3: {
			SDR(root);
			break;
		}
		case 4: {
			Nivele();
		}
		default:
			break;
		}
	}

	Dict();
	Dict(const dictType&);
	~Dict();
};

template<class K, class D, class Compare>
void Dict<K, D, Compare>::rotatieST(node* nod)
{
	node* aux = nod->dr;
	nod->dr = aux->st;
	if (nod != root) {
		if (nod->p->st == nod) {
			nod->p->st = aux;
		}
		else {
			nod->p->dr = aux;
		}
	}
	else
		root = aux;
	aux->p = nod->p;
	aux->st = nod;
	nod->p = aux;
	return;
}

template<class K, class D, class Compare>
void Dict<K, D, Compare>::rotatieDR(node* nod)
{
	node* aux = nod->st;
	nod->st = aux->dr;
	if (nod != root && nod->p != nullptr) {
		if (nod->p->st == nod) {
			nod->p->st = aux;
		}
		else {
			nod->p->dr = aux;
		}
	}
	else
		root = aux;
	aux->p = nod->p;
	aux->dr = nod;
	nod->p = aux;
	return;
}

template<class K, class D, class Compare>
void Dict<K, D, Compare>::balansare(node* nod)
{
	node* aux = nod;
	while (aux->p->col == 'R' && aux->col == 'R') {
		node* parent = aux->p;
		if (parent == nullptr || parent == NIL)
			break;
		node* grandp = parent->p;
		if (grandp == nullptr || grandp == NIL)
			break;

		node* uncle;
		if (parent == grandp->st)
			uncle = grandp->dr;
		else
			uncle = grandp->st;

		if (uncle->col == 'R') {
			grandp->col = 'R';
			parent->col = 'N';
			uncle->col = 'N';
			aux = parent;
			continue;
		}
		else {
			if (aux == parent->dr && parent == grandp->st) {
				rotatieST(parent);
				aux = parent;
				continue;
			}
			if (aux == parent->st && parent == grandp->dr) {
				rotatieDR(parent);
				aux = parent;
				continue;
			}
			if (aux == parent->st && parent == grandp->st) {
				grandp->col = 'R';
				parent->col = 'N';
				rotatieDR(grandp);
				aux = parent;
				continue;
			}
			if (aux == parent->dr && parent == grandp->dr) {
				grandp->col = 'R';
				parent->col = 'N';
				rotatieST(grandp);
				aux = parent;
				continue;
			}
		}
	}
	aux = root;
	while (aux->p != NIL)
		aux = aux->p;
	root = aux;
	root->col = 'N';
}

template<class K, class D, class Compare>
void Dict<K, D, Compare>::insert(K key, D data)
{
	node* newN = new node, * aux;
	newN->key = key;
	newN->data = data;
	newN->p = NIL;
	newN->dr = NIL;
	newN->st = NIL;
	newN->_NIL = NIL;


	if (root == nullptr) {
		root = newN;
		root->col = 'N';
		start = root;
		return;
	}

	aux = root;

	int ok = 1;

	while (true) {
		if (condition(key, aux->key) == 1) {
			if (aux->st != NIL)
				aux = aux->st;
			else {
				aux->st = newN;
				newN->p = aux;
				if (ok)
					start = newN;
				balansare(newN);
				return;
			}
		}
		else if (key == aux->key) {
			delete newN;
			return;
		}
		else {
			ok = 0;
			if (aux->dr != NIL)
				aux = aux->dr;
			else {
				aux->dr = newN;
				newN->p = aux;
				balansare(newN);
				return;
			}
		}
	}
}

template<class K, class D, class Compare>
void Dict<K, D, Compare>::insert(node* toCopy)
{
	node* newN = new node, * aux;
	newN->key = toCopy->key;
	newN->data = toCopy->data;
	newN->col = toCopy->col;
	newN->p = NIL;
	newN->dr = NIL;
	newN->st = NIL;
	newN->_NIL = NIL;

	if (root == nullptr) {
		root = newN;
		root->col = 'N';
		return;
	}

	aux = root;

	while (true) {
		if (condition(toCopy->key, aux->key) == 1) {
			if (aux->st != NIL)
				aux = aux->st;
			else {
				aux->st = newN;
				newN->p = aux;
				return;
			}
		}
		else if (toCopy->key == aux->key) {
			delete newN;
			return;
		}
		else {
			if (aux->dr != NIL)
				aux = aux->dr;
			else {
				aux->dr = newN;
				newN->p = aux;
				return;
			}
		}
	}
}

template<class K, class D, class Compare>
void Dict<K, D, Compare>::Clear()
{
	std::queue<node*> toDelete;
	node* aux;
	if (root != nullptr)
		toDelete.push(root);
	while (!toDelete.empty()) {
		aux = toDelete.front();
		if (aux->st != NIL)
			toDelete.push(aux->st);
		if (aux->dr != NIL)
			toDelete.push(aux->dr);
		toDelete.pop();
		delete aux;
	}
	root = nullptr;
}

template<class K, class D, class Compare>
Dict<K, D, Compare>& Dict<K, D, Compare>::operator=(dictType& toCopy)
{
	Clear();

	std::queue<node*> toInsert;
	node* aux;
	if (toCopy.root != nullptr)
		toInsert.push(root);
	while (!toInsert.empty()) {
		aux = toInsert.front();
		insert(aux);
		if (aux->st != NIL)
			toInsert.push(aux->st);
		if (aux->dr != NIL)
			toInsert.push(aux->dr);
		toInsert.pop();
	}

}

template<class K, class D, class Compare>
Dict<K, D, Compare>::Dict()
{
	root = nullptr;
	NIL = new node();
	NIL->col = 'N';
	NIL->p = NIL;
	NIL->dr = NIL;
	NIL->st = NIL;
	NIL->_NIL = NIL;
	finish = NIL;
	start = NIL;

	condition = Compare();
}

template<class K, class D, class Compare>
Dict<K, D, Compare>::Dict(const dictType& toCopy)
{
	root = nullptr;
	NIL = new node(K());
	NIL->p = NIL;
	NIL->dr = NIL;
	NIL->st = NIL;
	NIL->_NIL = NIL;

	std::queue<node*> toInsert;
	node* aux;
	if (toCopy.root != nullptr)
		toInsert.push(root);
	while (!toInsert.empty()) {
		aux = toInsert.front();
		this->insert(aux);
		if (aux->st != NIL)
			toInsert.push(aux->st);
		if (aux->dr != NIL)
			toInsert.push(aux->dr);
		toInsert.pop();
	}
}

template<class K, class D, class Compare>
Dict<K, D, Compare>::~Dict()
{
	Clear();
	delete NIL;
}