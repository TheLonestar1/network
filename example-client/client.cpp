#include <iostream>
#include <signal.h>
#include "TCPClient.h"
#include <thread>
#include <string.h>
TCPClient tcp;

void sig_exit(int s)
{
	tcp.exit();
	exit(0);
}
void * received(void * m)
{
	while(1)
	{
		string rec = tcp.receive();
		if(rec != "")
		{
			cout << "server: " << rec << endl;
		}
		sleep(1);
	}
	

}



int main(int argc, char *argv[])
{
	if(argc != 3) {
		cerr << "Usage: ./client ip port message" << endl;
		return 0;
	}
	signal(SIGINT, sig_exit);
	pthread_t msg;
	tcp.setup(argv[1],atoi(argv[2]));
	pthread_create(&msg, NULL, received, (void *)0);
	while(1)
	{
		string data;
		std::getline(cin,data);
		tcp.Send(data);
		sleep(1);
	}
	return 0;
}
