#include <iostream>
#include <climits>

using namespace std;

#define N 4

typedef struct HeapNode {
	int key;
	int row;
	int column;
} HeapNode;

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

	void heapify(int index);

public:
	MinHeap(HeapNode* h, int s) : heap(h), size(s) {
	}

	HeapNode getMin() {
		return heap[0];
	}

	void replaceRoot(HeapNode root) {
		heap[0] = root;
		heapify(0);
	}
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
		HeapNode minNode = minHeap.getMin();
		cout << minNode.key << ' ';

		if (minNode.column < N - 1) {
			minNode.key = matrix[minNode.row][minNode.column+1];
			minNode.column++;
		} else {
			minNode.key = INT_MAX;
		}

		minHeap.replaceRoot(minNode);
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
	return 0;
}
