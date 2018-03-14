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
		char killing[50]; // mesg content
	};

	buff msgg;
	int size = sizeof(msgg)-sizeof(long);

	msgrcv(qid, (struct msgbuf *)&msgg, size, 257, 0); // read mesg
						// don't read "fake" mesg
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msgg.killing << endl;




	exit(0);
}


