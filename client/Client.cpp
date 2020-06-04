#include "Client.h"

Client::Client(char p)
{
    protokol = p;
}

Client::~Client()
{

}

/**
* Считывает строку из консоли
*/
void Client::readString()
{
    cout << "Input text: ";
    getline(cin, message);

	handle();
}

/**
* Печатает строку в консоль
*/
void Client::printString()
{
    cout << buffer << endl;
}

/**
* Обмен данными с сервером
*/
void Client::handle()
{
    if (protokol == 't')
        c_sock = socket(AF_INET, SOCK_STREAM, 0); // TCP
    else
        c_sock = socket(AF_INET, SOCK_DGRAM, 0); // UDP

    if (c_sock < 0) {
        perror("socket");
        exit(1);
    }

    c_addr.sin_family = AF_INET;
    c_addr.sin_port = htons(3425);
    c_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    if (connect(c_sock, (struct sockaddr*)&c_addr, sizeof(c_addr)) < 0) // устанавливаем соединение с сервером
    {
        perror("connect");
        exit(2);
    }

    send(c_sock, message.c_str(), message.size(), 0); // отправляем строку на сервер
        
    std::vector<char> buf(1024);
    recv(c_sock, &(buf[0]), 1024, 0); // получаем данные с сервера
    buffer.assign(&(buf[0]), buf.size()); // переводим полученные данные в строку
    
    printString(); // выводим строку в консоль

    close(c_sock);
}