#include "get_info.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <sstream>
using namespace std;
int main(){
	int qid = msgget(ftok(".",'u'), 0);
	struct buf {
		long mtype; // required
		char message[50]; // mesg content
	};
	buf msg;
	int size = sizeof(msg)-sizeof(long);
	int number =0;
	int counter = 0;
	bool con = true;
	while(con){
		number = 0;
		msg.mtype = 997;
		strcpy(msg.message, "from Sender997");
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		msgsnd(qid, (struct msgbuf *)&msg, size, 0);
		cout << getpid() << ": sending messege to receivers" << endl;
		cout << "message: " << msg.message << endl;
		
		
		msgrcv(qid, (struct msgbuf *)&msg, size, 333, 0);
		cout << getpid() << ": gets reply" << endl;
		cout << "reply: " << msg.message << endl;
		string str(msg.message);
		stringstream convertToNumber(str);
		convertToNumber >> number;
		cout<< number << endl;
		if(number <100)
		{
			cout<< "the random number is less than 100, Terminating..."<< endl;
			exit(0);
		}
		msgrcv(qid, (struct msgbuf *)&msg, size, 123, 0);
		cout << getpid() << ": gets reply" << endl;
		cout << "reply: " << msg.message << endl;
		string str2(msg.message);
		stringstream convertToNumber2(str2);
		convertToNumber2 >> number;
		cout<< number << endl;
		if(number <100){
			cout<< "the random number is less than 100, Terminating..."<< endl;
			exit(0);
		}

	}
}
