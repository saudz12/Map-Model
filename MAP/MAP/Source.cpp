#include "implementare.h"

int main() {
	Dict<int, int> d;
	Dict<int, int>::node* a,* b, *c;
	d.insert(1, 2);
	d.insert(4, 2);
	d.insert(5, 2);
	a = d.find(4);

	if (a != d.end()) {
		b = d.succesor(a);
		if (b != d.end())
			std::cout << b->key << '\n';
		c = d.predecesor(a);
		if (c != d.end())
			std::cout << c->key << '\n';
	}	

	*d[1] = 10;
	*d[2] = 20;

	for (Dict<int, int>::iterator it = d.begin(); it != d.end(); it++) {
		std::cout << it.getKey() << " " << it.getData() << "\n";
	}

	while (true) {
		std::cout << "1. insert\n2. clear\n3. build\n4. print\n";
		int x;
		std::cin >> x;
		switch (x)
		{
		case 1: {
			int k, l;
			std::cin >> k >> l;
			d.insert(k, l);
			break;
		}
		case 2: {
			d.Clear();
			break;
		}
		case 3: {
			std::vector<std::pair<int, int>> v;
			int n;
			std::cin >> n;
			d.Clear();
			for (int i = 0; i < n; i++) {
				int k, l;
				std::cin >> k >> l;
				v.emplace_back(k, l);
			}
			d.Construct(v);
			break;
		}
		case 4: {
			std::cout << "1. RSD\n2. SRD\n3. SDR\n4. Nivele\n";
			std::cin >> x;
			d.afisare(x);
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	}

	return 0;
}