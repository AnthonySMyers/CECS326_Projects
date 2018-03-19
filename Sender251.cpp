#include "get_info.h"
#include <sys/msg.h>
#include <cstring>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>

using namespace std;
int main(){
	int qid = msgget(ftok(".",'u'), 0);
	if(qid <0)
	{
		perror("msgget");
		exit(1);
	}
	struct buf {
		long mtype; // required
		char message[50]; // mesg content
	};
	bool play = true;
	buf msg;
	buf lastMessage;
	lastMessage.mtype = 123;
	strcpy(lastMessage.message, "exit");
	msg.mtype = 123;
	strcpy(msg.message, "S251");
	int size = sizeof(msg)-sizeof(long);
	bool keepGoing = true;
	get_info(qid, (struct msgbuf *)&lastMessage, size, lastMessage.mtype);
	struct timeval t;
	while(true)
	{
		
		cout << getpid() << ": get message" << endl;
		cout << "message: " << msg.message << endl;
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		cout<< "Delaying " <<3 << " second(s) before sending next message" 			<<endl;
		t.tv_sec = 3;
		t.tv_usec =0;
		select(8, NULL, NULL, NULL, &t);
	}
	
	
}
