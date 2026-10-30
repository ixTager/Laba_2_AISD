#include <iostream>
#include "MergeSort.cpp"

int main()
{
    DynamicList<int> list;
    list.add(0, 1);
    list.add(1, 5);
    list.add(2, 2);
    list.add(3, 3);
    list.add(4, 9);

    MergeSort::sort(list);

    for (int i = 0; i < list.size(); i++) {
        std::cout << list.get(i) << " ";
    }
}