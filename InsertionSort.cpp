#include "DynamicList.h"

class InsertionSort {
private:
	static void insertionSort(DynamicList<int> &list) {
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
public:
	static void sort(DynamicList<int> &list) {
		if (list.size() <= 1) return;
		insertionSort(list);
	}
};