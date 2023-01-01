#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <time.h>
#include <WinSock2.h>
#include <iostream>
#include <thread>
#include <windows.h>
#include "data_config.h"

int main()
{
    using std::cout;
    using std::endl;
	LARGE_INTEGER start, end;
    float *arr = new float [2 * DATANUM + 1];
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

/* communicate */
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0)
    {
        MessageBoxA(NULL, "Winsock startup error", "Error", MB_OK | MB_ICONERROR);
        exit(1);
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_family = AF_INET; //IPv4 Socket
    addr.sin_addr.s_addr = inet_addr(ADDR_SRV); //Addres = localhost
    addr.sin_port = htons(8083); //Port = 1111

    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //Connection
    {
        MessageBoxA(NULL, "Bad Connection", "Error", MB_OK | MB_ICONERROR);
        return 0;
    }

    cout << "begin communication" << endl;
    //srand(time(NULL));

    arr[2 * DATANUM] = 0.0;
    while (1) //不等于0 循环
    {
        recv(Connection, (char*)(arr + DATANUM), sizeof(float)* (DATANUM + 1), NULL);
        if (arr[2 * DATANUM] - (-1.0f) < 1e-6)
            break;
    }

    float finish = -2.0f;
    send(Connection, (char*)&finish, sizeof(float), NULL);

    cout << "buffer:" << endl;
    for (int i = 0; i < DATANUM; i += 1000000)
        cout << arr[DATANUM + i] << ' ';
    cout << endl;
    closesocket(Connection);
    WSACleanup();
    return 0;
}
