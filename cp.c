#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

char buf[1000];
char sec[1000];
int main(int argc, char *argv[]){
	//struct stat st;
	int fd0, fd1, n,fail=1;
	//int check;
	char *slash;
  	slash=(char*)malloc(sizeof(char)*1000);
 	slash="/";
	//int ch0,ch1;
	if(argc<=2){
		printf(1," Argumen kurang\n");
		exit();
	}
	fd0=open(argv[1],O_RDWR);
	fd1=open(argv[2],O_RDWR);
	if(fd1>=0)fail=0;
	close(fd1);
	fd1=open(argv[2],O_RDWR | O_CREATE);
	printf(1,"%s %s\n",argv[1],argv[2]);
	if(fd0<0 && fd1>=0){
		printf(1,"%s does not exist or is a directory\n",argv[1]);
		if(fail)unlink(argv[2]);
		close(fd0);
		close(fd1);
		exit();
	}
	else if(fd0<0 && fd1<0){
		printf(1,"Cannot copy directory to directory\n");
		close(fd0);
		close(fd1);
		exit();
	}
	else if(fd1<0 && fd0>=0){
		close(fd1);
		strcat(sec,slash);
		strcat(sec,argv[2]);
		strcat(sec,slash);
		strcat(sec,argv[1]);
		printf(1,"File %s tercopy ke %s\n",argv[1],sec);
		fd1=open(sec,O_CREATE | O_RDWR);
	}
	while((n=read(fd0,buf,sizeof(buf)))>0) write(fd1,buf,sizeof(buf));
	printf(1,"CP SUCCESS\n");
	close(fd0);
	close(fd1);
	exit();
}
