#include <sys/msg.h>
#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include "Fun.h"
struct buf {
	long mtype; // required
	char message[50]; // mesg content
};
buf msg;
int number,counter,rc =0;
bool con = true;
using namespace std;

int main(){
	
	int qid = getQ();

	int size = sizeof(msg)-sizeof(long);
	while(con){
		cout << getpid() << ": sending messege to Receiver333" << endl;
		cout << "message: " << msg.message << endl;
		char message[] ="S257";
		sendTo(333, message);
		receiveFrom(257, (struct msgbuf *)&msg);
		string str(msg.message);
		while(str.compare("exit") !=0)
		{
			
			cout<< "Receiver 333 hasn't terminate yet" <<endl;
			cout << getpid() << ": sending messege to Receiver333" << endl;
			cout << "message: " << msg.message << endl;

			char message[] ="S257";
			sendTo(333, message);
			fWait(1);
			
		
			receiveFrom(257,(struct msgbuf *)&msg);
			str = msg.message;
		}
		cout<< "Receiver 333 doesn't receive anymore message" <<endl;
		cout << "terminating the program" <<endl;
		
		exit(0);
		
	}
}
