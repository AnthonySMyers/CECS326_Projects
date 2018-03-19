void fWait(int x);
int getQ();
int sendTo(long mtype, char* newMessage);
int mToNumber(char* message);
int receiveFrom(long mtype, struct msgbuf * msg);
