#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
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

    /********************** initial data **************/
    LARGE_INTEGER start, end;
    float* arr = new float[DATANUM];
    float sum_res;
    float max_res;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;

    cout << endl;

    /************************ communicate **********************/

    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0)
    {
        // MessageBoxA(NULL, "Winsock startup error", "Error", MB_OK | MB_ICONERROR);
        cout << ">>> Winsock startup error." << endl;
        return 0;
    }

    SOCKADDR_IN addr;
    int sizeofaddr = sizeof(addr);
    addr.sin_family = AF_INET;                  // IPv4 Socket
    addr.sin_addr.s_addr = inet_addr(ADDR_SRV); // Addres = localhost
    addr.sin_port = htons(8083);                // Port = 1111
    SOCKET Connection = socket(AF_INET, SOCK_STREAM, NULL);
    if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) // Connection
    {
        // MessageBoxA(NULL, "Bad Connection", "Error", MB_OK | MB_ICONERROR);
        cout << ">>> Bad Connection." << endl;
        return 0;
    }
    cout << ">>> Connection Estabished with " << ADDR_SRV << "." << endl;
    char flag = '+';


    /*********************** sum ***************************/
    cout << "--------------------------------" << endl;
    cout << "SUM" << endl;
    QueryPerformanceCounter(&start);
    cascade::sum(arr, 0, DATANUM - 1, &sum_res);
    QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl
         << "time: " << (end.QuadPart - start.QuadPart) << endl;

    QueryPerformanceCounter(&start);
    parallel::sum(arr, 0, HALF_NUM - 1, &sum_res, 0, 0);

    float linux_sum;
    recv(
        Connection,
        (char*)&linux_sum,
        sizeof(float),
        NULL
    );
    send(
        Connection,
        &flag,
        sizeof(flag),
        NULL);
    sum_res += linux_sum;


    QueryPerformanceCounter(&end);
    cout << "PARALLEL" << endl;
    cout << "result: " << sum_res << endl
        << "time: " << (end.QuadPart - start.QuadPart) << endl;
    cout << "--------------------------------" << endl;

    


    /*********************** max ***************************/
    cout << "--------------------------------" << endl;
    cout << "MAX" << endl;
    QueryPerformanceCounter(&start);
    cascade::mymax(arr, 0, DATANUM - 1, &max_res);
    QueryPerformanceCounter(&end);
    cout << "CASCADE" << endl;
    cout << "result: " << max_res << endl
        << "time: " << (end.QuadPart - start.QuadPart) << endl;


    QueryPerformanceCounter(&start);
    parallel::mymax(arr, 0, HALF_NUM - 1, &max_res, 0, 0);
    float linux_max;
    recv(
        Connection,
        (char*)&linux_max,
        sizeof(float),
        NULL
    );
    send(
        Connection,
        &flag,
        sizeof(flag),
        NULL);
    if (linux_max > max_res)
        max_res = linux_max;




    QueryPerformanceCounter(&end);
    cout << "PARALLEL" << endl;
    cout << "result: " << max_res << endl
        << "time: " << (end.QuadPart - start.QuadPart) << endl;
    cout << "--------------------------------" << endl;






    /*********************** sort ***************************/
    cout << "--------------------------------" << endl;
    cout << "SORT" << endl;
    QueryPerformanceCounter(&start);
    cascade::merge_sort(arr, 0, DATANUM - 1);
    QueryPerformanceCounter(&end);
    cout << (end.QuadPart - start.QuadPart) << endl;
    for (int i = 0; i < DATANUM; i += DATANUM / 128)
        cout << arr[i] << '\t';
    cout << endl;


    /* initial data again */
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;


    QueryPerformanceCounter(&start);
    parallel::merge_sort(arr, 0, HALF_NUM - 1, 0, 0);
    

    

    for (int i = 0; i < HALF_NUM / BUF_SIZE; i++)
    {
        recv(
            Connection,
            (char*)(arr + HALF_NUM + i * BUF_SIZE),
            sizeof(float) * (BUF_SIZE),
            NULL
        );
        if (0 == (i % ANSWER_SEP))
        {
            send(
                Connection,
                &flag,
                sizeof(flag),
                NULL);
        }
        //cout << i << ": " << *(arr + DATANUM + i * BUF_SIZE) << endl;
    }
    cout << ">>> Recv data finished!" << endl;
    //send(
    //    Connection,
    //    &flag,
    //    sizeof(flag),
    //    NULL
    //);
    parallel::merge(arr, 0, HALF_NUM - 1, DATANUM - 1);




    QueryPerformanceCounter(&end);
    cout << (end.QuadPart - start.QuadPart) << endl;
    for (int i = 0; i < DATANUM; i += DATANUM / 128)
        cout << arr[i] << ' ';
    cout << endl;


    closesocket(Connection);
    WSACleanup();
    return 0;
}