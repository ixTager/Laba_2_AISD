#include "InsertionSort.h"
#include <algorithm>
#include "MergeSort.h"
#include "DynamicArray.h"
#include "Run.h"
#include "Stack.h"

class TimSort {
private:
	static int getMinRun(int n) {
		if (n < 64) return n;

		int r = 0;
		while (n >= 64) {
			r |= (n & 1);
			n >>= 1;
		}

		return n + r;
	}

    static Run findRun(const DynamicArray<double>& array, int start) {
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

    static void reverse(DynamicArray<double>& array, Run run) {
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

    static Run processRun(DynamicArray<double>& array, int start, int minRun) {
        Run run = findRun(array, start);

        if (run.descending) reverse(array, run);

        int targetLength = std::min(minRun, array.size() - start);

        if (run.length < targetLength) run.length = targetLength;

        InsertionSort::sortByIndexes(array, run.start, run.start + run.length);

        return run;
    }

    static void mergeAt(DynamicArray<double>& array, Stack<Run>& runStack, int index) {
        Run left = runStack.get(index);
        Run right = runStack.get(index + 1);

        int start = left.start;
        int mid = start + left.length - 1;
        int end = start + left.length + right.length - 1;

        MergeSort::mergeRuns(array, start, mid, end);

        Run mergedRun;
        mergedRun.start = start;
        mergedRun.length = left.length + right.length;
        mergedRun.descending = false;

        runStack.set(index, mergedRun);
        runStack.remove(index + 1);
    }

    static void mergeCollapse(DynamicArray<double>& array, Stack<Run>& runStack) {
        while (runStack.size() > 1) {
            int n = runStack.size();

            if (n >= 3) {
                Run A = runStack.get(n - 3);
                Run B = runStack.get(n - 2);
                Run C = runStack.get(n - 1);

                if (A.length <= B.length + C.length) {
                    if (A.length < C.length) {
                        mergeAt(array, runStack, n - 3);
                    }
                    else {
                        mergeAt(array, runStack, n - 2);
                    }
                }
                else if (B.length <= C.length) {
                    mergeAt(array, runStack, n - 2);
                }
                else break;
            }
            else {
                Run B = runStack.get(n - 2);
                Run C = runStack.get(n - 1);

                if (B.length <= C.length) {
                    mergeAt(array, runStack, n - 2);
                }
                else break;
            }
        }
    }

    static void mergeRemainingRuns(DynamicArray<double>& array, Stack<Run>& runStack) {
        while (runStack.size() > 1) {
            int n = runStack.size();
            
            if (n >= 3 && runStack.get(n - 3).length < runStack.get(n - 1).length) {
                mergeAt(array, runStack, n - 3);
            }
            else mergeAt(array, runStack, n - 2);
        }
    }

public:
    static void sort(DynamicArray<double>& array) {
        int n = array.size();

        if (n <= 1) return;

        int minRun = getMinRun(n);
        int current = 0;

        Stack<Run> runStack;

        while (current < n) {
            Run run = processRun(array, current, minRun);
            runStack.push(run);
            mergeCollapse(array, runStack);
            current += run.length;
        }

        mergeRemainingRuns(array, runStack);

    }

};