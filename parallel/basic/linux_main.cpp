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

   /********************** initial data **************/
    float* arr = new float[DATANUM];
    float sum_res;
    float max_res;
    for (int i = 0; i < DATANUM; i++)
        arr[i] = DATANUM - i + 0.1f;
    cout << endl;

    /*************** communication ****************/
    char buffer[BUF_SIZE];
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
    char flag;
    /********* SORT ********/
    parallel::merge_sort(arr, HALF_NUM, DATANUM - 1, 0, 0);
    for (int i = 0; i < HALF_NUM; i += 100000)
        cout << arr[i] << '\t';
    cout << endl;

    

    for (int i = 0; i < HALF_NUM / BUF_SIZE; i++)
    {
        send(
            clientSock,
            (char*)(arr + HALF_NUM + i * BUF_SIZE),
            sizeof(float) * (BUF_SIZE),
            0
        );
        if (0 == (i % ANSWER_SEP))
        {
            recv(
                clientSock,
                &flag,
                sizeof(flag),
                0);
        }
    }
    //recv(
    //    clientSock,
    //    &flag,
    //    sizeof(flag),
    //    0
    //);

    /********* SUM ********/
    cout << "--------------------------------" << endl;
    cout << "SUM" << endl;
    parallel::sum(arr, HALF_NUM, DATANUM - 1, &sum_res, 0, 0);
    cout << "CASCADE" << endl;
    cout << "result: " << sum_res << endl;
    cout << "--------------------------------" << endl;

    send(
        clientSock,
        (char*)(&sum_res),
        sizeof(float),
        0
    );
    recv(
        clientSock,
        &flag,
        sizeof(flag),
        0);

    /********* MAX ********/
    cout << "--------------------------------" << endl;
    cout << "MAX" << endl;
    parallel::mymax(arr, HALF_NUM, DATANUM - 1, &max_res, 0, 0);
    cout << "CASCADE" << endl;
    cout << "result: " << max_res << endl;
    cout << "--------------------------------" << endl;

    send(
        clientSock,
        (char*)(&max_res),
        sizeof(float),
        0
    );
    recv(
        clientSock,
        &flag,
        sizeof(flag),
        0);


    close(clientSock);
    close(sock);
    return 0;
}