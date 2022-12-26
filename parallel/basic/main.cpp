#include <iostream>
#include <windows.h>
#include "data_config.h"


int main()
{
    using std::cout;
    using std::endl;
    int *arr = new int [DATANUM];
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i;
    //cascade::merge_sort(arr, 0, 15);
    for (int i = 0; i < DATANUM; i+=1000000)
        cout << arr[i] << ' ';
    cout << endl;
	LARGE_INTEGER start, end;
    QueryPerformanceCounter(&start);//start  
    cascade::merge_sort(arr, 0, DATANUM - 1);
    QueryPerformanceCounter(&end);//end
    std::cout << "Time Consumed:" << (end.QuadPart - start.QuadPart) << endl;

    for (int i = 0; i < DATANUM; i+=1000000)
        cout << arr[i] << ' ';
    cout << endl;

    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i;

    QueryPerformanceCounter(&start);//start  
    parallel::merge_sort(arr, 0, DATANUM - 1, 0, 0);
    QueryPerformanceCounter(&end);//end
    std::cout << "Time Consumed:" << (end.QuadPart - start.QuadPart) << endl;

    for (int i = 0; i < DATANUM; i+=1000000)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}