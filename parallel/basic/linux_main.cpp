#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include "data_config.h"

int main()
{
    using std::cout;
    using std::endl;
    float *arr = new float [DATANUM + 1];
    float sum_res;
    float max_res;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;

    cout << "--------------------------------" << endl;
    cout << "SUM" << endl;
    cascade::sum(arr, 0, DATANUM - 1, &sum_res);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl;
    parallel::sum(arr, 0, DATANUM - 1, &sum_res, 0, 0);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl;
    cout << "--------------------------------" << endl;

    cout << "--------------------------------" << endl;
    cout << "MAX" << endl;
    cascade::mymax(arr, 0, DATANUM - 1, &sum_res);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl;
    parallel::mymax(arr, 0, DATANUM - 1, &sum_res, 0, 0);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl;
    cout << "--------------------------------" << endl;

    cascade::merge_sort(arr, 0, DATANUM - 1);
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;
    parallel::merge_sort(arr, 0, DATANUM - 1, 0, 0);
    for (int i = 0; i < DATANUM; i+=100000)
        cout << arr[i] << ' ';
    cout << endl;

/* communication */
    arr[DATANUM] = -1.0f;
    std::cout << "begin" << std::endl;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        return 1;
    }

    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(8083);

    if (bind(sock, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0) {
        std::cerr << "Failed to bind socket" << std::endl;
        close(sock);
        return 1;
    }

    if (listen(sock, 5) < 0) {
        std::cerr << "Failed to listen on socket" << std::endl;
        close(sock);
        return 1;
    }

    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);
    int clientSock = accept(sock, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrLen);
    if (clientSock < 0) {
        std::cerr << "Failed to accept client connection" << std::endl;
        close(sock);
        return 1;
    }

    float finish = 0.0f;
    while (1)
    {
        send(clientSock, (char*)arr, sizeof(float) * (DATANUM + 1), 0);
        recv(clientSock, (char*)&finish, sizeof(float), 0);
        if (finish - (-2.0f) < 1e-6)
            break;
    }
    
    close(clientSock);
    close(sock);

    return 0;
}
