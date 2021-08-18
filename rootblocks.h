#ifndef ROOTBLOCKS_H_

#define SIGPLUS  SIGRTMIN
#define SIGMINUS SIGRTMIN

#define LENGTH(X) (sizeof(X) / sizeof(X[0]))
#define MIN(a, b) ((a < b) ? a : b)

typedef struct {
  char*        command;
  unsigned int interval;
  unsigned int signal;
  char*        sub;
} Block;

void dummysighandler(int num);
void getcmds(int time);
void getsigcmds(unsigned int signal);
void setupsighandler();
void sighandler(int signum);
int  statusupd(char* str, char* last);
void statusloop();
void termhandler();
void pstdout();

#ifndef NO_X
void setroot();
static void (*writestatus)() = setroot;
static int      setupX();
static Display* dpy;
static int      screen;
static Window   root;
#else
static void (*writestatus)() = pstdout;
#endif

#endif // ROOTBLOCKS_H_
