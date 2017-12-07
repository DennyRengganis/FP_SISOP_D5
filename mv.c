#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

char buf[1000];

int main(int argc, char *argv[]){

	int fd0, fd1, n;
	if(argc<=2){
		printf(1," Argumen kurang\n");
		exit();
	}
	if((fd0=open(argv[1],O_RDONLY))<0){
		printf(1,"%s invalid\n",argv[1]);
		exit();
	}
	if((fd1=open(argv[2],O_CREATE | O_RDWR))<0){
                printf(1,"%s invalid\n",argv[2]);
                exit();
        }

	while((n=read(fd0,buf,sizeof(buf)))>0){
		write(fd1,buf,sizeof(buf));
	}
	close(fd0);
	close(fd1);
        unlink(argv[1]);
	exit();
}
