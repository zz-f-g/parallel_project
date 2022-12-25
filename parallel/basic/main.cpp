#include <iostream>
#include "data_config.h"


int main()
{
    using std::cout;
    using std::endl;
    int *arr = new int [DATANUM];
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i;
    //cascade::merge_sort(arr, 0, 15);
    for (int i = 0; i < DATANUM; i+=1000)
        cout << arr[i] << ' ';
    cout << endl;
    parallel::merge_sort(arr, 0, DATANUM - 1, 0, 0);
    for (int i = 0; i < DATANUM; i+=1000)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}