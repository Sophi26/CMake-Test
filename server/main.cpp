#include "Server.h"

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

    IServer* server;

    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
    {
        switch (c)
        {
            case 't':

                server = new Server(c);
                server->startServer();

                break;

            case 'u':

                server = new Server(c);
                server->startServer();

                break;
        }
    }

	return 0;
}