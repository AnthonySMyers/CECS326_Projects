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

	buff msg;
	int size = sizeof(msg)-sizeof(long);

	msgrcv(qid, (struct msgbuf *)&msg, size, 0, 0);
	cout << "pid:  " <<getpid() <<" mtype: "<< msg.mtype << ": gets message" << endl;
	cout << "message: " << msg.message << endl;
	cout << getpid() << ": sends reply" << endl;
	strcpy(msg.message, "120");
	msg.mtype = 123;
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);



	exit(0);
}

