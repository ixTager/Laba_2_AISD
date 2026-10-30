#include <iostream>
#include "DynamicList.h"
#include <stdexcept>

class MergeSort {
private:
    static void merge(DynamicList<int>& list, int start, int mid, int end) {
        DynamicList<int> temp;
        int left = start;
        int right = mid + 1;

        while (left <= mid && right <= end) {
            if (list.get(left) <= list.get(right)) {
                temp.add(temp.size(), list.get(left));
                left++;
            }
            else {
                temp.add(temp.size(), list.get(right));
                right++;
            }
        }

        while (left <= mid) {
            temp.add(temp.size(), list.get(left));
            left++;
        }

        while (right <= end) {
            temp.add(temp.size(), list.get(right));
            right++;
        }

        for (int i = 0; i < temp.size(); i++) {
            list.remove(start + i);
            list.add(start + i, temp.get(i));
        }
    }

public:
    static void sort(DynamicList<int>& list) {
        if (list.size() <= 1) return;
        sort(list, 0, list.size() - 1);
    }

private:
    static void sort(DynamicList<int>& list, int start, int end) {
        if (start >= end) return;

        int mid = start + (end - start) / 2;
        sort(list, start, mid);
        sort(list, mid + 1, end);
        merge(list, start, mid, end);
    }
};