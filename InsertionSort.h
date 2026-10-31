#include "DynamicArray.h";

class InsertionSort {
private:
	static void insertionSort(DynamicArray<double> &list) {
		int start = 0;
		int end = 1;
		while (end != list.size()) {
			for (int i = end; i > 0; i--) {
				if (list.get(i) < list.get(i - 1)) {
					int current_val = list.get(i);
					int prev_val = list.get(i - 1);
					list.remove(i);
					list.remove(i - 1);

					list.add(i - 1, current_val);
					list.add(i, prev_val);
				}
				else break;
			}
			end++;
		}
	}

	static void insertionSortByIndexes(DynamicArray<double>& list, int start, int end) {
		for (int i = start + 1; i < end; i++) {
			int key = list.get(i);
			int j = i - 1;

			while (j >= start && list.get(j) > key) {
				list.set(j + 1, list.get(j));
				j--;
			}

			list.set(j + 1, key);
		}
	}
public:
	static void sort(DynamicArray<double>& list) {
		if (list.size() <= 1) return;
		insertionSort(list);
	}

	static void sortByIndexes(DynamicArray<double>& list, int start, int end) {
		if (list.size() <= 1) return;
		insertionSortByIndexes(list, start, end);
	}
};