#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

//#define _POSIX_SOURCE 1 /* POSIX compliant source */

int openLine (const char *serialPort)
{
  int fd = open(serialPort, O_RDWR | O_NOCTTY |O_NDELAY );
  if (fd < 0) return fd;
  printf("line %s opened\n",serialPort);
  fcntl(fd,F_SETFL,0);
  struct termios newtp;
  memset(&newtp, 0, sizeof(newtp));
  newtp.c_cflag = B9600 | CRTSCTS | CS8 | CLOCAL | CREAD;
  newtp.c_iflag = IGNPAR | ICRNL;
  newtp.c_oflag = 0;
  newtp.c_lflag = ICANON;
  newtp.c_cc[VINTR]    = 0;     /* Ctrl-c */
  newtp.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
  newtp.c_cc[VERASE]   = 0;     /* del */
  newtp.c_cc[VKILL]    = 0;     /* @ */
  //newtp.c_cc[VEOF]     = 4;     /* Ctrl-d */
  newtp.c_cc[VEOF]     = 0;     /* Ctrl-d */
  newtp.c_cc[VTIME]    = 0;     /* inter-character timer unused */
  newtp.c_cc[VMIN]     = 1;     /* blocking read until 1 character arrives */
  newtp.c_cc[VSWTC]    = 0;     /* '\0' */
  newtp.c_cc[VSTART]   = 0;     /* Ctrl-q */
  newtp.c_cc[VSTOP]    = 0;     /* Ctrl-s */
  newtp.c_cc[VSUSP]    = 0;     /* Ctrl-z */
  newtp.c_cc[VEOL]     = 0;     /* '\0' */
  newtp.c_cc[VREPRINT] = 0;     /* Ctrl-r */
  newtp.c_cc[VDISCARD] = 0;     /* Ctrl-u */
  newtp.c_cc[VWERASE]  = 0;     /* Ctrl-w */
  newtp.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
  newtp.c_cc[VEOL2]    = 0;     /* '\0' */
	tcsetattr(fd,TCSANOW,&newtp);
  tcflush(fd, TCIFLUSH);
  printf("line %s set\n",serialPort);
  return fd;
}

int writeToLine (int fd, const char *data, int len)
{
  return write(fd, data, len);
}

void closeLine (int fd) 
{
  if (fd >= 0) close(fd);
  fd = -1;
}  
