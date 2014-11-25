#include <iostream>

using namespace std;

void print(int iarray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << iarray[i] << ' ';
	}
	cout << endl;
}

void swap(int iarray[], int from, int to) {
	int tmp = iarray[from];
	iarray[from] = iarray[to];
	iarray[to] = tmp;
}

int partition(int iarray[], int left, int right) {
	int pivot = left - 1;
	int pivot_value = iarray[right];
	for (int i = left; i < right; i++) {
		if (iarray[i] < pivot_value) {
			pivot++;
			swap(iarray, pivot, i);
		}
	}
	pivot++;
	swap(iarray, pivot, right);
	return pivot;
}

void _quicksort(int iarray[], int left, int right) {
	if (left >= right) {
		return;
	}

	int pivot = partition(iarray, left, right);
	_quicksort(iarray, left, pivot - 1);
	_quicksort(iarray, pivot + 1, right);
}

void quicksort(int iarray[], int size) {
	_quicksort(iarray, 0, size - 1);
}

int main() {
	int ia[] = {13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
	int size = sizeof(ia) / sizeof(ia[0]);
	quicksort(ia, size);
	print(ia, size);
	return 0;
}
