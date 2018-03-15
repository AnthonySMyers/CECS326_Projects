#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main() {

	// create my msgQ with key value from ftok()
	int qid = msgget(ftok(".",'u'), 0);


	// declare my message buffer
	struct buff {
		long mtype; // required
		char message[50]; // mesg content
	};
	counter =0
	buff msg;
	int size = sizeof(msg)-sizeof(long);
	while(counter <10){

		msgrcv(qid, (struct msgbuf *)&msg, size, 0, 0);
		cout << "pid:  " <<getpid() <<" mtype: "<< msg.mtype << ": gets message" << endl;
		cout << "message: " << msg.message << endl;
		cout << getpid() << ": sends reply" << endl;
		if(msg.mtype == 997){
			msg.mtype = 333;
			strcpy(msg.message, "150");
			msgsnd(qid, (struct msgbuf *)&msg, size, 0);
			counter++;
		}
		if(msg.mtype == 257){
			counter++;
		}
	}
	cout << "Reciver 333 has received 5000 messages, sending terminating message and terminating" << endl;
	msg.mtype = 333;
	strcpy(msg.message, "20");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	msg.mtype = 257;
	strcpy(msg.message, "S");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	exit(0);
}

