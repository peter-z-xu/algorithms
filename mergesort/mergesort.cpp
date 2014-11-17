#include <iostream>

using namespace std;

void print(int iarray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << iarray[i] << ' ';
	}
	cout << endl;
}

void _mergesort(int iarray[], int result[], int left, int right) {
	if (left >= right) {
		return;
	}

	int mid = left + (right - left) / 2;
	_mergesort(iarray, result, left, mid);
	_mergesort(iarray, result, mid + 1, right);
	// merge
	int index = left;
	int index_left = left;
	int index_right = mid + 1;
	while (index_left <= mid && index_right <= right) {
		if (iarray[index_left] < iarray[index_right]) {
			result[index++] = iarray[index_left++];
		} else {
			result[index++] = iarray[index_right++];
		}
	}
	while (index_left <= mid) {
		result[index++] = iarray[index_left++];
	}
	while (index_right <= right) {
		result[index++] = iarray[index_right++];
	}
	for (int i = left; i <= right; i++) {
		iarray[i] = result[i];
	}
}

void mergesort(int iarray[], int size) {
	int result[size];
	for (int i = 0; i < size; i++) {
		result[i] = 0;
	}
	_mergesort(iarray, result, 0, size - 1);
	print(result, size);
//	for (int i = 0; i < size; i++) {
//		iarray[i] = result[i];
//	}
}

int main() {
	int ia[] = {1, 4, 5, 6, 2, 3};
	int size = sizeof(ia) / sizeof(ia[0]);
//	print(ia, size);
	mergesort(ia, size);
//	print(ia, size);
	return 0;
}
