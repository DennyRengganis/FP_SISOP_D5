#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"
#include "fs.h"


char go[512];


char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}

void
mvstar(char *asal,char *tujuan,char *ext)
{
	char buf[512], *p;
	int fd;
	int ch;
	int lext=strlen(ext);
	struct dirent de;
	struct stat st;
	stat(asal,&st);
	fd=open(asal,O_RDONLY);
	ch=open(tujuan,O_RDONLY);
	if(st.type==T_DIR){
		strcpy(buf, asal);
		p = buf+strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
			continue;
			//char *test=(char*)malloc(sizeof(char*)*512);	
			
		memmove(p, de.name, DIRSIZ);
		p[DIRSIZ] = 0;
		//printf(1,"terjadi\n");
		if(stat(buf,&st)<0){
			printf(1,"mv *: file cannot be stats\n");
			continue;
		}
		if(st.type==1){
			if(fmtname(buf)[0]=='.')continue;
			printf(1,"dir terjadi\n");
			char baru[512];
			char res[512];
			strcpy(baru,asal);
			strcat(baru,"/");
			strcat(baru,p);
			strcpy(res,tujuan);
			strcat(res,"/");
			strcat(res,p);
			mkdir(res);
			mvstar(baru,res,ext);
			unlink(baru);		
		}
		else if(st.type>1){
			int a;
			char baru[512]; char res[512];
			if(lext==1){
				strcpy(baru,asal);
				strcat(baru,"/");
				strcat(baru,p);
				strcpy(res,tujuan);
				strcat(res,"/");
				strcat(res,p);
				int ex,as;
				printf(1,"file  %s terjadi\n",p);
				ex=open(res,O_CREATE | O_RDWR);			
				as=open(baru,O_RDONLY);
				while((a=read(as,go,sizeof(go)))>0)
				{
					write(ex,go,a);
				}
				close(as);
				close(ex);
				unlink(baru);
				}	
			else{
				char c[512],comp[512];
				strcpy(c,ext+1);
				strcpy(comp,p+(strlen(p)-strlen(c)));
				if(strcmp(c,comp)==0){
					strcpy(baru,asal);
					strcat(baru,"/");
					strcat(baru,p);
					strcpy(res,tujuan);
					strcat(res,"/");
					strcat(res,p);
					int ex,as;
					printf(1,"file terjadi\n");
					ex=open(res,O_CREATE | O_RDWR);			
					as=open(baru,O_RDONLY);
					while((a=read(as,go,sizeof(go)))>0)
					{
						write(ex,go,a);
					}
				close(as);
				close(ex);
				unlink(baru);
			}
		}
	}
	}
	}
	close(fd);
	close(ch);
}



int main(int argc, char *argv[]){
	//struct stat st;
	int fd0, fd1, n,fail=1;
	//int check;
	//int ch0,ch1;
	char sec[512];
	if(argc<=2){
		printf(1," Argumen kurang\n");
		exit();
	}
	if(argc==3 && argv[1][0]=='*'){
		int check;
		check=open(argv[2],O_WRONLY);
		if(check>=0){
			printf(1,"mv * : error, %s is not a directory\n",argv[2]);
			close(check);
			exit();		
		}
		close(check);		
		mvstar(".",argv[2],argv[1]);
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
		printf(1,"Cannot move directory to directory\n");
		close(fd0);
		close(fd1);
		exit();
	}
	else if(fd1<0 && fd0>=0){
		close(fd1);
		strcat(sec,"/");
		strcat(sec,argv[2]);
		strcat(sec,"/");
		strcat(sec,argv[1]);
		printf(1,"File %s terpindah ke %s\n",argv[1],sec);
		fd1=open(sec,O_CREATE | O_RDWR);
	}
	printf(1,"%s %s\n",argv[1],sec);
	while((n=read(fd0,go,sizeof(go)))>0) write(fd1,go,n);
	printf(1,"MV SUCCESS\n");
	close(fd0);
	close(fd1);
	unlink(argv[1]);
	exit();
}
