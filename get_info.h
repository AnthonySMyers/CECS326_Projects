#include<iostream>
#include<signal.h>
#include<unistd.h>
#include <sys/types.h>

struct msgbuf{
	long mtype;
	char mtext[1];
};

void get_info(int qid, msgbuf *exitmsg, int size, long mtype);

