#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Fun.h"
using namespace std;
struct buf {
		long mtype; // required
		char message[50]; // mesg content
	};
int main(){
	struct timeval t;
	int qid = msgget(ftok(".",'u'), 0);
	if(qid >=0)
	{	
		cout << "didn't clear message queue. Clearing and creating new one" <<endl;
		msgctl (qid, IPC_RMID, NULL);
		qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
	}
	else if (qid <0)
	{
		cout << "message queue is empty, creating a new one " <<endl;
		qid = msgget(ftok(".",'u'), IPC_EXCL|IPC_CREAT|0600);
	}
	
	
	buf msg;
	
	int rc;
	int size = sizeof(msg)-sizeof(long);
	
	int number =0;
	int counter = 0;
	bool con = true;
	
	while(con){
		fWait(1);
		char message[] = "S997";

		sendTo(123, message) ;

		sendTo(333, message) ;
		cout << getpid() << ": sending messege to receivers" << endl;
		cout << "message: " << message << endl;
		
		

		receiveFrom(997, (struct msgbuf *)&msg);
				

		cout << getpid() << ": gets reply" << endl;
		cout << "reply: " << msg.message << endl;
		number= mToNumber(msg.message);
		
		if(number <100)
		{
			char message[] = "exit";

			sendTo(123, message);

			sendTo(333, message);
			cout<< "the random number is less than 100, Terminating..."<< endl;
			exit(0);
		}
		receiveFrom(997, (struct msgbuf *)&msg);		
		cout << getpid() << ": gets reply" << endl;
		cout << "reply: " << msg.message << endl;
		number= mToNumber(msg.message);
	
		if(number <100){
			char message[] = "exit";
			sendTo(123, message);
			sendTo(333, message);
			cout<< "the random number is less than 100, Terminating..."<< endl;
			exit(0);
		}

	}
}
