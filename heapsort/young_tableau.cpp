#include <iostream>
#include <climits>

using namespace std;

#define N 4

class HeapNode {
private:
public:
	static int constructor_count;
	static int copy_constructor_count;
	static int assign_constructor_count;
	int key;
	int row;
	int column;

	HeapNode() {
		constructor_count++;
	//	cout << "HeapNode constructor called " << constructor_count << endl;
	}

	HeapNode(const HeapNode& obj) {
		copy_constructor_count++;
	//	cout << "HeapNode copy_constructor called " << copy_constructor_count << endl;
		key = obj.key;
		row = obj.row;
		column = obj.column;
	}

	HeapNode& operator=(const HeapNode& obj) {
		assign_constructor_count++;
	//	cout << "HeapNode assign_constructor called " << assign_constructor_count << endl;
		key = obj.key;
		row = obj.row;
		column = obj.column;
		return *this;
	}
};

int HeapNode::constructor_count = 0;
int HeapNode::copy_constructor_count = 0;
int HeapNode::assign_constructor_count = 0;

class MinHeap {
private:
	HeapNode* heap;
	int size;

	int getLeft(int index) {
		return 2 * index + 1;
	}

	int getRight(int index) {
		return 2 * index + 2;
	}

	void swap(int from, int to) {
		HeapNode tmp = heap[from];
		heap[from] = heap[to];
		heap[to] = tmp;
	}

public:
	MinHeap(HeapNode* h, int s) : heap(h), size(s) {
	}

	HeapNode& getMin() {
		return heap[0];
	}

	void replaceRoot(HeapNode root) {
		heap[0] = root;
		heapify(0);
	}

	void heapify(int index);
};

void MinHeap::heapify(int index) {
	while (index < size) {
		int smallest = heap[index].key;
		int smallest_index = index;
		int left = getLeft(index);
		if (left < size && heap[left].key < smallest) {
			smallest = heap[left].key;
			smallest_index = left;
		}
		int right = getRight(index);
		if (right < size && heap[right].key < smallest) {
			smallest = heap[right].key;
			smallest_index = right;
		}
		if (smallest_index != index) {
			swap(smallest_index, index);
			index = smallest_index;
		} else {
			break;
		}
	}
}

void printSortedYoungTableau(int matrix[][N]) {
	HeapNode heap[N];
	for (int i = 0; i < N; i++) {
		heap[i].key = matrix[i][0];
		heap[i].row = i;
		heap[i].column = 0;
	}

	MinHeap minHeap(heap, N);

	for (int i = 0; i < N * N; i++) {
		HeapNode& minNode = minHeap.getMin();
		cout << minNode.key << ' ';

		if (minNode.column < N - 1) {
			minNode.key = matrix[minNode.row][minNode.column+1];
			minNode.column++;
		} else {
			minNode.key = INT_MAX;
		}

//		minHeap.replaceRoot(minNode);
		minHeap.heapify(0);
	}
	cout << endl;
}

int main() {
	int matrix[N][N] = {
		{10, 20, 30, 40},
		{15, 25, 35, 45},
		{27, 29, 37, 48},
		{32, 33, 39, 50}};

	printSortedYoungTableau(matrix);
	cout << "constructor count = " << HeapNode::constructor_count << endl;
	cout << "copy constructor count = " << HeapNode::copy_constructor_count << endl;
	cout << "assign constructor count = " << HeapNode::assign_constructor_count << endl;
	return 0;
}
