#include "Server.h"
#include "main.h"

Server::Server(char p)
{
	protokol = p;
}

Server::~Server()
{
	
}

/**
* Создание сокета и установка соединения
*/
void Server::startServer()
{
	if (protokol == 't')
		this_s = socket(AF_INET, SOCK_STREAM, 0); // TCP
	else
		this_s = socket(AF_INET, SOCK_DGRAM, 0); // UDP

	if (this_s < 0) {
		perror("socket");
        exit(1);
	}

	address.sin_family = AF_INET;
	address.sin_port = htons(3425);
	address.sin_addr.s_addr = htonl(INADDR_ANY);	

	if (bind(this_s, (struct sockaddr*)&address, sizeof(address)) < 0) // устанавливаем соединенние с клиентом
	{
		perror("bind");
        exit(2);
	}

	if (protokol == 't') {
		listen(this_s, 1); // слушаем сокет
		handle_TCP(); // обмениваемся данными с клиентом по протоколу TCP
	} else {
		handle_UDP(); // обмениваемся данными с клиентом по протоколу UDP
	}
}

/**
* Закрытие сокета
*/
void Server::closeServer()
{
	close(this_s);
}

/**
* Обработчик запросов от клиента по протоколу TCP
*/
void Server::handle_TCP()
{
	while(1)
    {
        int sock = accept(this_s, NULL, NULL); // пришел запрос от клиента

        if(sock < 0)
        {
            perror("accept");
            exit(3);
        }

		switch(fork())
        {
			case -1:
				perror("fork");
				break;
				
			case 0:
				closeServer();
				rec_send_mess(sock); // обмениваемся данными с клиентом
				close(sock);
				_exit(0);
				
			default:
				close(sock);
        }
    }

	closeServer();
}

/**
* Обработчик запросов от клиента по протоколу UDP
*/
void Server::handle_UDP()
{
	rec_send_mess(this_s); // обмениваемся данными с клиентом
}

/**
* Обмен данными с клиентом
* @param sc - дескриптор сокета
*/
void Server::rec_send_mess(int sc)
{
	std::vector<char> buf_vec(1024); // хранит данные от клиента

	string buf; // хранит строку от клиента
	int bytes_read;

	string numbers; // хранит найденные в строке числа, отправляемые обратно клиенту
	string sum_numbers; // хранит сумму найденных чисел, отправляемую обратно клиенту

	while(1)
	{
		bytes_read = recv(sc, &(buf_vec[0]), 1024, 0); // получаем данные с клиента

		if(bytes_read <= 0) break;

		buf.assign(&(buf_vec[0]), buf_vec.size()); // переводим полученные данные в строку

		get_numbers(numbers, sum_numbers, buf); // ищем числа в строке и вычисляем их сумму

		numbers += ('\n' + sum_numbers);

		send(sc, numbers.c_str(), numbers.size(), 0); // отправляем найденные числа и их сумму обратно клиенту
	}
}

/**
* Нахождение чисел в строке и подсчет их суммы
* @param result - строка, куда записываются найденные числа
* @param sum - строка, куда записывается сумма найденных чисел
* @param s - строка, в которой ищутся числа
*/
void Server::get_numbers(string &result, string &sum, const string &s)
{
	vector<int> num_tmp; // хранит все найденные числа

    bool found = false; // при чтении строки определяет была ли найдена цифра
    int number = 0; // хранит найденное число

    for (string::size_type i = 0; i < s.length(); i++) // проходим по строке
	{
        if (s[i] >= '0' && s[i] <= '9') // если встречаем цифру
		{
            const int digit = s[i] - '0';
            number = number*10 + digit; // запоминаем цифру

            found = true;
        }
        else {
            if (found) { // идущие подряд цифры закончились  
				num_tmp.push_back(number); // запоминаем полностью число            
                
                number = 0;
                found = false;
            }
        }
    }

    if (found)
	{
        num_tmp.push_back(number); // запоминаем последнее найденное число
    }

	std::sort(num_tmp.begin(), num_tmp.end(), std::less<int>()); // сортируем найденные числа в порядке возрастания

	int sm = 0;

	for(int n : num_tmp) // вычисляем сумму найденных чисел
	{
		sm += n;
		result += (std::to_string(n) + '\t'); // заносим найденные числа в строку
	}

	sum = std::to_string(sm); // заносим найденную сумму в строку

	cout << "SUM: " << sum << endl;
	cout << "RESULT: " << result << endl;
}