#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>
using namespace std;

//Sender 257

int main() {
	
	
	
	int qid = msgget(ftok(".",'u'), 0);
	

	int random = rand();
	//string s = to_string(random);
	//cout<< random<<endl;	

	struct buffer {
		long mtype; 
		char text[300]; 
	};
	buffer message;
	int size = sizeof(message)-sizeof(long);

	message.mtype = 257;
	strcpy(message.text,"test");

	msgsnd(257,(struct buffer *)&message,size,5);	

	cout<< getpid()<<" Sending random number: "<<message.text<<endl;
	
	return 0;
}
	
