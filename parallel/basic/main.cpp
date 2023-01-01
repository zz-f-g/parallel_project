#include <iostream>
#include <thread>
#include <windows.h>
#include "data_config.h"

int main()
{
    using std::cout;
    using std::endl;
	LARGE_INTEGER start, end;
    float *arr = new float [DATANUM];
    float sum_res;
    float max_res;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;

    cout << "--------------------------------" << endl;
    cout << "SUM" << endl;
	QueryPerformanceCounter(&start);
    cascade::sum(arr, 0, DATANUM - 1, &sum_res);
	QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl
         << "time: " << (end.QuadPart - start.QuadPart) << endl;
    QueryPerformanceCounter(&start);
    parallel::sum(arr, 0, DATANUM - 1, &sum_res, 0, 0);
	QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl
         << "time: " << (end.QuadPart - start.QuadPart) << endl;
    cout << "--------------------------------" << endl;

    cout << "--------------------------------" << endl;
    cout << "MAX" << endl;
	QueryPerformanceCounter(&start);
    cascade::mymax(arr, 0, DATANUM - 1, &sum_res);
	QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl
         << "time: " << (end.QuadPart - start.QuadPart) << endl;
    QueryPerformanceCounter(&start);
    parallel::mymax(arr, 0, DATANUM - 1, &sum_res, 0, 0);
	QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl
         << "time: " << (end.QuadPart - start.QuadPart) << endl;
    cout << "--------------------------------" << endl;

	QueryPerformanceCounter(&start);
    cascade::merge_sort(arr, 0, DATANUM - 1);
	QueryPerformanceCounter(&end);
	cout << (end.QuadPart - start.QuadPart) << endl;
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;
	QueryPerformanceCounter(&start);
    parallel::merge_sort(arr, 0, DATANUM - 1, 0, 0);
	QueryPerformanceCounter(&end);
	cout << (end.QuadPart - start.QuadPart) << endl;
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;
    return 0;
}
