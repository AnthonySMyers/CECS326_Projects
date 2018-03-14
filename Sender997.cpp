#include "get_info.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;
int main(){
	int qid = msgget(ftok(".",'u'), 0);
	struct buf {
		long mtype; // required
		char killing[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	msg.mtype = 257;
	strcpy(msg.killing, "257");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	cout << getpid() << ": sending to patch64" << endl;
	msg.mtype =997;
	strcpy(msg.killing, "997");
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	cout << getpid() << ": now exits" << endl;

	exit(0);
}
