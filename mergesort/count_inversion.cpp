#include <iostream>

using namespace std;

void print(int iarray[], int size) {
	for (int i = 0; i < size; i++) {
		cout << iarray[i] << ' ';
	}
	cout << endl;
}

int _count_inversion(int iarray[], int result[], int left, int right) {
	if (left >= right) {
		return 0;
	}

	int mid = left + (right - left) / 2;
	int left_inversion = _count_inversion(iarray, result, left, mid);
	int right_inversion = _count_inversion(iarray, result, mid + 1, right);
	// merge
	int count = 0;
	int index = left;
	int index_left = left;
	int index_right = mid + 1;
	while (index_left <= mid && index_right <= right) {
		if (iarray[index_left] < iarray[index_right]) {
			result[index++] = iarray[index_left++];
		} else {
			count += (mid - index_left + 1);
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
	return left_inversion + right_inversion + count;
}

int count_inversion(int iarray[], int size) {
/*
	int count_inversion = 0;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (iarray[i] > iarray[j]) {
				count_inversion++;
			}
		}
	}
	return count_inversion;
*/
	int result[size];
	for (int i = 0; i < size; i++) {
		result[i] = 0;
	}
	return _count_inversion(iarray, result, 0, size - 1);
}

int main() {
	int ia[] = {1, 4, 5, 6, 2, 3};
	int size = sizeof(ia) / sizeof(ia[0]);
	cout << "number_inversion = " << count_inversion(ia, size) << endl;
	return 0;
}
