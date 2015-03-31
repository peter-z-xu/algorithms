#include <iostream>

using namespace std;

void counting_sort(int ia[], int size, int max) {
	int range = max + 1;
	int count[range];
	int result[size];
	for (int i = 0; i < range; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		count[ia[i]]++;
	}
	for (int i = 1; i < range; i++) {
		count[i] += count[i-1];
	}
	for (int i = size - 1; i >= 0; i--) {
		result[--count[ia[i]]] = ia[i];
	}
	for (int i = 0; i < size; i++) {
		ia[i] = result[i];
	}
}

void print(int ia[], int size) {
	for (int i = 0; i < size; i++) {
		cout << ia[i] << ' ';
	}
	cout << endl;
}

int main() {
	int ia[] = {6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
	int size = sizeof(ia) / sizeof(ia[0]);
	int max = ia[0];
	for (int i = 1; i < size; i++) {
		if (max < ia[i]) {
			max = ia[i];
		}
	}
	print(ia, size);
	counting_sort(ia, size, max);
	print(ia, size);
}
