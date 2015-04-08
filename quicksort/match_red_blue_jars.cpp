#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>

using namespace std;

void swap(int ia[], int from, int to) {
	if (from == to) return;
	int temp = ia[from];
	ia[from] = ia[to];
	ia[to] = temp;
}

void generate_random(int ia[], int size) {
	for (int i = 0; i < size; i++) {
		ia[i] = i + 1;
	}
	srand(time(NULL));
	sleep(1);
	for (int i = 0; i < size; i++) {
		int index = rand() % size;
		if (index == 0) {
			swap(ia, 0, size - 1);
		} else {
			swap(ia, 0, index);
		}
	}
}

void print(int ia[], int size) {
	for (int i = 0; i < size; i++) {
		cout << ia[i] << ' ';
	}
	cout << endl;
}

int partition(int red_jars[], int blue_jars[], int left, int right) {
	int red_pivot = red_jars[right];

	for (int i = left; i <= right; i++) {
		if (red_pivot == blue_jars[i]) {
			swap(blue_jars, i, right);
			break;
		}
	}

	int blue_pivot_index = left;
	for (int i = left; i < right; i++) {
		if (blue_jars[i] < red_pivot) {
			swap(blue_jars, blue_pivot_index, i);
			blue_pivot_index++;
		}
	}
	swap(blue_jars, blue_pivot_index, right);
	int blue_pivot = blue_jars[blue_pivot_index];

	int red_pivot_index = left;
	for (int i = left; i < right; i++) {
		if (red_jars[i] < blue_pivot) {
			swap(red_jars, red_pivot_index, i);
			red_pivot_index++;
		}
	}
	swap(red_jars, red_pivot_index, right);

	return blue_pivot_index;
}

void quick_pair(int red_jars[], int blue_jars[], int left, int right) {
	if (left >= right) {
		return;
	}
	int pivot = partition(red_jars, blue_jars, left, right);
	quick_pair(red_jars, blue_jars, left, pivot - 1);
	quick_pair(red_jars, blue_jars, pivot + 1, right);
}

void match_red_blue_jars(int red_jars[], int blue_jars[], int size) {
	quick_pair(red_jars, blue_jars, 0, size-1);
}

// http://clrs.skanev.com/08/problems/04.html
int main() {
	int size = 7;
	int red_jars[size];
	int blue_jars[size];
	generate_random(red_jars, size);
	generate_random(blue_jars, size);
	cout << "red jars: ";
	print(red_jars, size);
	cout << "blue jars: ";
	print(blue_jars, size);

	match_red_blue_jars(red_jars, blue_jars, size);

	cout << "red jars: ";
	print(red_jars, size);
	cout << "blue jars: ";
	print(blue_jars, size);
}
