#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>

#include "BoeBotControl.h"

#define match(a,b) (!strcmp(a,b)) // could be improved by more sophisticated matching

void usa (char *ibuf, char *obuf) // translation to 7bit code for Slovak language
{
  char *c, *d;
  for (c=ibuf, d=obuf; *c; c++) {
    if (*c > ' ' || (*c == ' ' && d == obuf)) {
      //printf("%d <%c>\n",*c,*c);
      if (*c == 196 && *(c+1) == 190) { *d = 'l'; c++; }
      else if (*c == 195 && *(c+1) == 161) { *d = 'a'; c++; }
      else if (*c == 195 && *(c+1) == 169) { *d = 'e'; c++; }
      else if (*c == 195 && *(c+1) == 173) { *d = 'i'; c++; }
      else if (*c == 195 && *(c+1) == 179) { *d = 'o'; c++; }
      else if (*c == 195 && *(c+1) == 180) { *d = 'o'; c++; }
      else if (*c == 195 && *(c+1) == 186) { *d = 'u'; c++; }
      else if (*c == 195 && *(c+1) == 189) { *d = 'y'; c++; }
      else if (*c == 196 && *(c+1) == 141) { *d = 'c'; c++; }
      else if (*c == 196 && *(c+1) == 143) { *d = 'd'; c++; }
      else if (*c == 196 && *(c+1) == 190) { *d = 'l'; c++; }
      else if (*c == 197 && *(c+1) == 136) { *d = 'n'; c++; }
      else if (*c == 197 && *(c+1) == 161) { *d = 's'; c++; }
      else if (*c == 197 && *(c+1) == 165) { *d = 't'; c++; }
      else if (*c == 197 && *(c+1) == 190) { *d = 'z'; c++; }
      else *d = *c;
      d++;
    }
	else if (*c == ' ') {*d = ' '; d++; }
    else if (*c == 13 || *c == 10) break;
  }
  *d = 0;
}

char obuf[1024], buf[1024];

int main(int argc, char *argv[])
{
  int port = (argc == 1) ? 7000 : atoi(argv[1]);
  char *lang = (argc <= 2) ? (char *) "sk" : argv[2];

  BoeBotControl boebot("/dev/ttyUSB0");
  if (port > 0) {
    boebot.forward();
    sleep(1);
  }
  boebot.stop();
  if (port == 0) return 0;
  
  char nerozumiem[120];
  sprintf(nerozumiem,"espeak -v%s \"%s\"",lang,!strcmp(lang,"sk")? "Nerozumiem" : "I don't understand");
  
  int sock, length;
  struct sockaddr_in server;
  int msgsock;
  int rval, go;
  char *logfile = NULL;
  
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
      perror("opening stream socket");
      exit(1);
  }
  
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(port);
  if (bind(sock, (struct sockaddr *)&server, sizeof(server))) {
    perror("binding stream socket");
    exit(1);
  }
  length = sizeof(server);
  if (getsockname(sock, (struct sockaddr *)&server, (socklen_t *) &length)) {
    perror("getting socket name");
    exit(1);
  }
  printf("Socket has port #%d\n", ntohs(server.sin_port));
  
  listen(sock, 5);
  do {
    msgsock = accept(sock, 0, 0);
    if (msgsock == -1) {f
        perror("on accept");
        exit(1);
    }
  	fcntl(msgsock, F_SETFL, O_NONBLOCK);
    printf("client connected\n");
    
    for (go=1;go>0;) {
      memset(obuf, 0, sizeof(obuf));
      rval  = recv(msgsock, obuf,  1024, 0);
      if (rval > 0) {
        usa(obuf,buf);
        printf("<%s>\n",buf);
        if (match(buf,"connect"));
		/* ------------ to be designed by students ------------- */
        else if (match(buf,"dolava") || match(buf,"vlavo") || match(buf,"lavo") || match(buf,"zlava") || match(buf,"zdravo") || match(buf,"vyhlada")  || match(buf,"left")) boebot.rotateLeft();
        else if (match(buf,"doprava") || match(buf,"vpravo") || match(buf,"pravo") || match(buf,"strava") || match(buf,"sprava") || match(buf,"spravu") || match(buf,"dolina") || match(buf,"right")) boebot.rotateRight();
        else if (match(buf,"dopredu") || match(buf,"vpred") || match(buf,"pred") || match(buf,"chod") || match(buf,"forward")) boebot.forward();
        else if (match(buf,"dozadu") || match(buf,"vzad") || match(buf,"zott") || match(buf,"cuvaj") || match(buf,"backward")) boebot.backward();
        else if (match(buf,"stop") || match(buf,"dost") || match(buf,"stat") || match(buf,"spravat") || match(buf,"starat") || match(buf,"stoj")) boebot.stop();
        else if (match(buf,"umna") || match(buf,"kumne") || match(buf,"ku mne"));
		else if (!strncmp(obuf,"povedz",6) || !strncmp(obuf,"Povedz",6) || !strncmp(obuf,"say",3) || !strncmp(obuf,"Say",3)) {
			char *ch = strchr(obuf,' ');
			if (ch != NULL && *(ch+1) != 0) {
				char command[124];
				sprintf(command,"espeak -v%s \"%s\"",lang,ch+1);
				system(command);
			}
			else system(nerozumiem);
		}
        else if (strlen(buf) > 2) system(nerozumiem);
		/* ----------------------------------------------------- */
      }
      else {
        if (rval == 0) go = 0;
        errno = 0;
      }
    }
    printf("\nclosing socket\n");
  	close(msgsock);
  } while (go >= 0);
  close(sock);
  
  return 0;
}
