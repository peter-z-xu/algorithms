#include <iostream>

using namespace std;

void print(int ia[], int size) {
	for (int i = 0; i < size; i++) {
		cout << ia[i] << ' ';
	}
	cout << endl;
}

int get_number_digits(int number) {
	int digits = 1;
	int temp = number / 10;
	while (temp > 0) {
		digits++;
		temp = temp / 10;
	}
	return digits;
}

void partition_numbers(int ia[], int size, int group[], int group_size) {
	int count[group_size];
	int temp[size];
	for (int i = 0; i < group_size; i++) {
		group[i] = 0;
		count[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		temp[i] = ia[i];
		group[get_number_digits(ia[i])]++;
	}
	for (int i = 1; i < group_size; i++) {
		group[i] += group[i-1];
		count[i] = group[i];
	}
	for (int i = size-1; i >= 0; i--) {
		ia[--count[get_number_digits(temp[i])]] = temp[i];
	}
}

int get_nth_digit(int number, int position) {
	int factor = 1;
	for (int i = 0; i < position; i++) {
		factor *= 10;
	}
	return number / factor % 10;
}

void counting_sort(int ia[], int left, int right, int position) {
	int size = right - left + 1;
	int count[10];
	int temp[size];
	for (int i = 0; i < 10; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		temp[i] = ia[left+i];
		count[get_nth_digit(ia[left+i], position)]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i-1];
	}
	for (int i = size-1; i >= 0; i--) {
		int index = --count[get_nth_digit(temp[i], position)];
		ia[left+index] = temp[i];
	}
}

void radix_sort(int ia[], int left, int right, int digits) {
	for (int i = 0; i < digits; i++) {
		counting_sort(ia, left, right, i);
	}
}

void sort_variable_digits(int ia[], int size) {
	int max = ia[0];
	for (int i = 1; i < size; i++) {
		if (ia[i] > max) {
			max = ia[i];
		}
	}
	int max_digits = get_number_digits(max);
	int groups[max_digits+1];
	partition_numbers(ia, size, groups, max_digits+1);
	for (int digits = 1; digits < max_digits+1; digits++) {
		radix_sort(ia, groups[digits-1], groups[digits]-1, digits);
	}
}

// http://clrs.skanev.com/08/problems/03.html
int main() {
//	int ia[] = {333, 5, 67, 344, 11, 9};
	int ia[] = {344, 333, 67, 11, 9, 5};
	int size = sizeof(ia) / sizeof(ia[0]);
	print(ia, size);
	sort_variable_digits(ia, size);
	print(ia, size);
}
