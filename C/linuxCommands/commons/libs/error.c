#include <errno.h>
#include <stdarg.h>
#include "../include/apue.h"


static void err_doit(int,int, const char* , va_list);


void err_quit(const char* fmt, ...){
	va_list ap;
	va_start(ap, fmt);
	err_doit(0,0,fmt,ap);
	va_end(ap);
	exit(1);

}

void err_doit(int erronflag, int error, const char* fmt, va_list ap){
	char buf[MAXLINE];
	vsnprintf(buf, MAXLINE - 1, fmt, ap);
	if(erronflag)
		snprintf(buf+strlen(buf), MAXLINE - strlen(buf) -1 , " :%s", strerror(error));

	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}
