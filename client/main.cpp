#include "Client.h"

using namespace std;

int main(int argc, char* argv[])
{
    const char* short_options = "t:u";

    const struct option long_options[] = {
        { "TCP", 0, 0, 't' },
        { "UDP", 0, 0, 'u' },
        { 0, 0, 0, 0 }
    };

    int c;

    IClient* client;

    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch (c)
        {
            case 't':

                client = new Client(c);
                client->readString();

                break;

            case 'u':

                client = new Client(c);
                client->readString();

                break;
        }
    }

	return 0;
}