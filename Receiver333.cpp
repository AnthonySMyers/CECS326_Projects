#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Fun.h"
using namespace std;

int main() {
	struct timeval t;
	// create my msgQ with key value from ftok()
	int qid = getQ();

	// declare my message buffer
	struct buff {
		long mtype; // required
		char message[50]; // mesg content
	};
	int limit = 10;
	int eCounter = 0;
	int counter =0;
	buff msg;
	int size = sizeof(msg)-sizeof(long);
	int rc;
	while(counter <limit){
		

		receiveFrom(333,(struct msgbuf *)&msg);
		
		cout<< "Number of received messages: " << counter <<endl;


		cout << "pid:  " << getpid() << ": gets message" << endl;
		cout << "message: " << msg.message << endl;
		string str(msg.message);
		if ((counter+1) ==limit)
		{
			cout << "Reciver 333 has received 5000 messages, sending terminating 				message and terminating" << endl;
			char message[] = "0";
			sendTo(997, message);

			char message2[] = "exit";
			sendTo(257, message2);

			exit(0);
		}
		else if(str.compare("S997")==0){
			cout << "sending ack reply to 997 "<<endl;
			cout << getpid() << ": sends reply '120'" << endl;

			char message[] = "120";
			sendTo(997, message);			
			counter++;
		}
		
		else if(str.compare("S257")==0)
		{
			cout << "Tell Sender257 the message was received"<<endl;
			char message[] = "Got it!";		
			sendTo(257, message);
			counter++;
		}
		else{
			counter++;
		}
		
	}

}

