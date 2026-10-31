#include "InsertionSort.h"
#include <algorithm>
#include "DynamicArray.h"
#include "Run.h"
#include "Stack.h"

class TimSort {
private:
    Stack<int> stack;

	static int getMinRun(int n) {
		if (n < 64) return n;

		int r = 0;
		while (n >= 64) {
			r |= (n & 1);
			n >>= 1;
		}

		return n + r;
	}

    static Run findRun(const DynamicArray<int>& array, int start) {
        int n = array.size();

        if (start >= n - 1) {
            return { start, 1, false };
        }

        int i = start + 1;
        bool descending = array.get(i) < array.get(start);

        if (descending) {
            while (i < n && array.get(i) < array.get(i - 1)) {
                i++;
            }
        }
        else {
            while (i < n && array.get(i) >= array.get(i - 1)) {
                i++;
            }
        }

        return { start, i - start, descending };
    }

    static void reverse(DynamicArray<int>& array, Run run) {
        int left = run.start;
        int right = run.start + run.length - 1;

        while (left < right) {
            int temp = array.get(left);

            array.set(left, array.get(right));
            array.set(right, temp);

            left++;
            right--;
        }
    }

    static Run processRun(DynamicArray<int>& array, int start, int minRun) {
        Run run = findRun(array, start);

        if (run.descending) reverse(array, run);

        int targetLength = std::min(minRun, array.size() - start);

        InsertionSort::sortByIndexes(array, run.start, run.start + run.length);

        return run;
    }

public:
    static void sort(DynamicArray<int>& array) {
        int n = array.size();

        if (n <= 1) return;

        int minRun = getMinRun(n);
        int current = 0;

        Stack<Run> runStack;

        while (current < n) {
            Run run = processRun(array, current, minRun);
            runStack.push(run);
            current += run.length;
        }
    }


};