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
	msg.mtype = 117;
	strcpy(msg.killing, "changing"); //creating a new string adding to char killing
	msgsnd(qid, (struct msgbuf *)&msg, size, 0); //send message
	cout << getpid() << ": sending to patch64" << endl;
	msgrcv(qid, (struct msgbuf *)&msg, size, 117, 0); // read message
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.killing << endl;
	msg.mtype =117;
	strcat(msg.killing, " mtype is 117 now"); //add more stuff to the original string
	msgsnd(qid, (struct msgbuf *)&msg, size, 0);
	cout << getpid() << ": now exits" << endl;

	msgrcv(qid, (struct msgbuf *)&msg, size, 117, 0); // read message 
	cout << getpid() << ": gets message" << endl;
	cout << "message: " << msg.killing << endl;
	exit(0);
}
