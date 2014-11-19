#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <float.h>

using namespace std;

typedef struct Point {
	int x;
	int y;
	Point() {
		cout << "**" << endl;
	}
} Point;

float distance(Point* p1, Point* p2) {
	return sqrt((p1->x - p2->x) * (p1->x - p2->x) + (p1->y - p2->y) * (p1->y - p2->y));
}

float brute_force(Point points[], int size) {
	float min = FLT_MAX;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			float d = distance(&points[i], &points[j]);
			if (d < min) {
				min = d;
			}
		}
	}
	return min;
}

int compareX(const void* p1, const void* p2) {
	return ((Point*)p1)->x - ((Point*)p2)->x;
}

int compareY(const void* p1, const void* p2) {
	return ((Point*)p1)->y - ((Point*)p2)->y;
}

void print_points(Point points[], int size) {
	for (int i = 0; i < size; i++) {
		cout << '{' << points[i].x << ", " << points[i].y << "} @ " << &points[i] << endl;
	}
	cout << "-------" << endl;
}

float min(float f1, float f2) {
	if (f1 < f2) {
		return f1;
	}
	return f2;
}

float strip_closest(Point strip[], int size, float d) {
	float min = d;
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size && strip[j].y - strip[i].y < d; j++) {
			if (distance(&strip[i], &strip[j]) < d) {
				min = d;
			}
		}
	}
	return min;
}

float closest_divide_conquer(Point px[], Point py[], int size) {
	if (size <= 3) {
		return brute_force(px, size);
	}
	int mid = (size - 1) / 2;
	Point midPoint = px[mid];
	Point* pyl = new Point[mid + 1];
	Point* pyr = new Point[size - mid - 1];
	int li = 0;
	int ri = 0;
	for (int i = 0; i < size; i++) {
		if (py[i].x < midPoint.x) {
			pyl[li++] = py[i];
		} else {
			pyr[ri++] = py[i];
		}
	}

	float dl = closest_divide_conquer(px, pyl, mid + 1);
	float dr = closest_divide_conquer(px + mid + 1, pyr, size - mid - 1);
	float d = min(dl, dr);

	Point* strip = new Point[size];
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (abs(py[i].x - midPoint.x) < d) {
			strip[count++] = py[i];
		}
	}
	d = min(d, strip_closest(strip, count, d));

	delete[] pyl;
	delete[] pyr;
	delete[] strip;
	return d;
}

float closest(Point points[], int size) {
	Point* PX = new Point[size];
	Point* PY = new Point[size];
	for (int i = 0; i < size; i++) {
		PX[i] = points[i];
		PY[i] = points[i];
	}
	print_points(points, size);
	qsort(PX, size, sizeof(Point), compareX);
	print_points(PX, size);
	qsort(PY, size, sizeof(Point), compareY);
	print_points(PY, size);
	float d = closest_divide_conquer(PX, PY, size);
	delete[] PX;
	delete[] PY;
	return d;
}

int main() {
	int X[] = {2, 12, 40, 5, 12, 3};
	int Y[] = {3, 30, 50, 1, 10, 4};
//	Point P[] = {{2, 3}, {12, 30}, {40, 50}, {5, 1}, {12, 10}, {3, 4}};
	Point P[6];
	for (int i = 0; i < 6; i++) {
		P[i].x = X[i];
		P[i].y = Y[i];
	}
	int size = sizeof(P) / sizeof(P[0]);
	
	cout << "closest distance of a pair of points = " << closest(P, size) << endl;
//	cout << "closest distance of a pair of points = " << brute_force(P, size) << endl;
	return 0;
}
