#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#ifndef NO_X
#include <X11/Xlib.h>
#endif

#include "rootblocks.h"

#include "config.h"

#define STATUSLENGTH (LENGTH(blocks) * CMDLENGTH + 1)

static char statusbar[LENGTH(blocks)][CMDLENGTH] = { 0 };
static char statusstr[2][STATUSLENGTH]; // current and previous status string
static int  statusContinue = 1;

// opens process for block's command and stores output in *output
void getcmd(const Block* block, char* output) {
  FILE* cmdf = popen(block->command, "r");
  if (!cmdf)
    return;
  fgets(output, CMDLENGTH - LENGTH(delim), cmdf);
  long i = strlen(output);
  if (i == 0) {
    //return if block and command output are both empty
    pclose(cmdf);
    return;
  }
  //only chop off newline if one is present at the end
  i = output[i - 1] == '\n' ? i - 1 : i;
  if (LENGTH(delim) != 1)
    strncpy(output + i, delim, LENGTH(delim));
  else
    output[i++] = '\0';
  pclose(cmdf);
}

// update blocks in their time
void getcmds(int time) {
  const Block* current;
  for (unsigned int i = 0; i < LENGTH(blocks); i++) {
    current = blocks + i;
    if ((current->interval != 0 && time % current->interval == 0) || time == -1)
      getcmd(current, statusbar[i]);
  }
}

// update blocks in their sigkills
void getsigcmds(unsigned int signal) {
  const Block* current;
  for (unsigned int i = 0; i < LENGTH(blocks); i++) {
    current = blocks + i;
    if (current->signal == signal)
      getcmd(current, statusbar[i]);
  }
}

// setup signal handler
void setupsighandler() {
  // initialize all real time signals with dummy handler
  for (int i = SIGRTMIN; i <= SIGRTMAX; i++)
    signal(i, dummysighandler);

  for (unsigned int i = 0; i < LENGTH(blocks); i++) {
    if (blocks[i].signal > 0)
      signal(SIGMINUS + blocks[i].signal, sighandler);
  }
}

// compare prev to cur status
int statusupd(char* str, char* last) {
  strcpy(last, str);
  str[0] = '\0';
  for (unsigned int i = 0; i < LENGTH(blocks); i++)
    strcat(str, statusbar[i]);
  str[strlen(str) - strlen(delim)] = '\0';
  return strcmp(str, last); // 0 if they are the same
}

#ifndef NO_X
// set root window name to status
void setroot() {
  if (!statusupd(statusstr[0], statusstr[1])) //Only set root if text has changed.
    return;
  XStoreName(dpy, root, statusstr[0]);
  XFlush(dpy);
}

// setup it on x display
int setupX() {
  dpy = XOpenDisplay(NULL);
  if (!dpy) {
    fprintf(stderr, "rootblocks: Failed to open display\n");
    return 0;
  }
  screen = DefaultScreen(dpy);
  root   = RootWindow(dpy, screen);
  return 1;
}
#endif

// print status out in console
void pstdout() {
  if (!statusupd(statusstr[0], statusstr[1])) //Only write out if text has changed.
    return;
  printf("%s\n", statusstr[0]);
  fflush(stdout);
}

// da loop !!
void statusloop() {
  setupsighandler();
  int i = 0;
  getcmds(-1);
  while (1) {
    getcmds(i++);
    writestatus();
    if (!statusContinue)
      break;
    sleep(1);
  }
}

// this signal handler should do nothing
void dummysighandler(int signum) {
  return;
}

// signal handler
void sighandler(int signum) {
  getsigcmds(signum - SIGPLUS);
  writestatus();
}

// terminate handler
void termhandler() {
  statusContinue = 0;
}

int main(int argc, char** argv) {
  if (argc > 1) {
    if (!strcmp("-p", argv[1]))
      writestatus = pstdout;
    else if (!strcmp("-v", argv[1]) || !strcmp("-V", argv[1])) {
      printf("v1.0");
      return 0;
    } else if (!strcmp("-h", argv[1]) || !strcmp("--help", argv[1])) {
      printf("-v for version, -p for console output mode. That's it.");
      return 0;
    } else {
      printf("Unknown option, try -h for help");
      return 1;
    }
  }

#ifndef NO_X
  if (!setupX())
    return 1;
#endif
  signal(SIGTERM, termhandler);
  signal(SIGINT, termhandler);
  statusloop();
#ifndef NO_X
  XCloseDisplay(dpy);
#endif
  return 0;
}
