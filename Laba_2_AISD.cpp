#include <iostream>
#include "MergeSort.cpp"
#include "InsertionSort.cpp"

int main()
{
    DynamicList<int> list_1;
    list_1.add(0, 1);
    list_1.add(1, 5);
    list_1.add(2, 2);
    list_1.add(3, 3);
    list_1.add(4, 9);

    MergeSort::sort(list_1);

    for (int i = 0; i < list_1.size(); i++) {
        std::cout << list_1.get(i) << " ";
    }

    std::cout << "\n";

    DynamicList<int> list_2;
    list_2.add(0, 1);
    list_2.add(1, 5);
    list_2.add(2, 2);
    list_2.add(3, 3);
    list_2.add(4, 9);

    InsertionSort::sort(list_2);

    for (int i = 0; i < list_2.size(); i++) {
        std::cout << list_2.get(i) << " ";
    }

    std::cout << "\n";

}