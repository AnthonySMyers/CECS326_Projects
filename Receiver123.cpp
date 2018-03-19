#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Fun.h"
using namespace std;
struct buff {
	long mtype; // required
	char message[50]; // mesg content
};
buff msg;
int counter,rc = 0;
int main() {

	// create my msgQ with key value from ftok()
	int qid = getQ();
	// declare my message buffer
	cout<< "hello: " << getpid()<<endl;
	int size = sizeof(msg)-sizeof(long);
	bool keepGoing = true;
	string sExit = "exit";
	
	
	while(keepGoing){
		receiveFrom(123, (struct msgbuf *)&msg);

		cout << "pid:  " <<getpid() <<" mtype: "<< msg.mtype << ": gets message" 			<< endl;
		cout << "message: " << msg.message << endl;
		string str(msg.message);
		
		if(str.compare(sExit)==0){
			cout << "Got a terminating message from sender "<< msg.mtype << endl;
			counter++;	
			cout << "Current number of terminating message that was received:" << 		counter << endl;
			
		}
		else if(str.compare("S997")==0)
		{
			cout << "sending ack reply to 997 "<<endl;
			cout << getpid() << ": sends reply '120'" << endl;

			char message[] = "120";
			sendTo(997, message);

			
		}
		keepGoing = (counter ==2)? false:true;
	}
	cout << "Receiver 123 received 2 terminating message from sender 997 and sender 251, terminating and clear the queue"<<endl;
	msgctl (qid, IPC_RMID, NULL);
	exit(0);

	
}


