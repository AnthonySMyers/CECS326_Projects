#include<iostream>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/time.h>
#include "Fun.h"
#include "stdlib.h"
#include <string.h>
#include <stdio.h>
#include <sstream>
struct timeval t;
using namespace std;
void fWait(int x)
{
	cout<< "Delaying " <<x << " second(s)" <<endl;
	t.tv_sec = x;
	t.tv_usec =0;
	select(8, NULL, NULL, NULL, &t);
}
int getQ()
{
	int qid = msgget(ftok(".",'u'), 0);
	if(qid <0)
	{
		perror("msggest");
		exit(1);
	}
	return qid;
}
struct buf {
		long mtype; // required
		char message[50]; // mesg content
	};
int sendTo(long mtype, char* newMessage)
{
	int rc;
	buf msg;
	strcpy(msg.message, newMessage);
	msg.mtype =mtype;
	int size = sizeof(msg)-sizeof(long);
	rc=msgsnd(getQ(), (struct msgbuf *)&msg, size, 0);
	if(rc<0)
	{
		perror("msgsnd");
		exit(1);
	}

	return rc;
}
int receiveFrom(long mtype, struct msgbuf * msg)
{
	int size = sizeof( buf)-sizeof(long);
	int rc= msgrcv(getQ(), msg, size, mtype, 0);
	if(rc<0)
	{
		perror("msgrcv");
		exit(1);
	}
	return 1;
}
int mToNumber(char* message)
{
	int number;
	string str(message);
	stringstream convertToNumber(str);
	convertToNumber >> number;

	return number;
}
