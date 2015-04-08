#include <iostream>
#include <string>

using namespace std;

void print(string sa[], int size) {
	for (int i = 0; i < size; i++) {
		cout << sa[i] << ' ';
	}
	cout << endl;
}

void partition_strings(string sa[], int size, int group[], int group_length) {
	int count[group_length];
	string *temp = new string[size];
	for (int i = 0; i < group_length; i++) {
		count[i] = 0;
		group[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		temp[i] = sa[i];
		count[sa[i].length()]++;
	}
	for (int i = 1; i < group_length; i++) {
		count[i] += count[i-1];
		group[i] = count[i];
	}
	for (int i = size-1; i >= 0; i--) {
		int index = --count[temp[i].length()];
		sa[index] = temp[i];
	}
	delete[] temp;
}

void counting_sort(string sa[], int left, int right, int index) {
	int size = right - left + 1;
	int count[26];
	string *temp = new string[size];
	for (int i = 0; i < 26; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < size; i++) {
		temp[i] = sa[left+i];
		count[sa[left+i].at(index)-'a']++;
	}
	for (int i = 1; i < 26; i++) {
		count[i] += count[i-1];
	}
	for (int i = size-1; i >= 0; i--) {
		int id = --count[temp[i].at(index)-'a'];
		sa[left+id] = temp[i];
	}
	delete[] temp;
}

void sort_strings(string sa[], int size) {
	int max_length = sa[0].length();
	for (int i = 1; i < size; i++) {
		if (sa[i].length() > max_length) {
			max_length = sa[i].length();
		}
	}
	int group[max_length+1];
	partition_strings(sa, size, group, max_length+1);
	for (int i = max_length; i >= 0; i--) {
		counting_sort(sa, group[i], size-1, sa[group[i]].length()-1);
		print(sa, size);
	}
}

int main() {
	string sa[] = {"a", "bc", "bac", "ca", "abc", "aa"};
	int size = sizeof(sa) / sizeof(sa[0]);
	cout << "size = " << size << endl;
	print(sa, size);
	sort_strings(sa, size);
	print(sa, size);
}
