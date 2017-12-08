#include "types.h"
#include "stat.h"
#include "user.h"

char sim[1003];

int readint (char a[]) {
	int c = a[0], x = 0,counter=1; int neg=0;
	for (;(c<48||c>57)&&c!=45; c=a[counter++]);
	for (;(c>47&&c<58)||c==45; c=a[counter++]){
		if(c==45){ neg=1;continue; }
		x = (x<<1)+(x<<3)+c-48;
	}
	return neg ? x*(-1):x;
}

void
cat(int fd)
{
  int n;
  while((n = read(fd, sim, sizeof(sim))) > 0) {
    if (write(1, sim, n) != n)
      exit();
  }
  if(n < 0) //jika kosong
    exit();
}

void expand(int fd,int spasi)
{
  int n;
  int k,i;

  while((n = read(fd, sim, sizeof(sim))) > 0) {
    for(k=0;k<n;k++){
        if(sim[k]=='\t'){
            for(i=0;i<spasi;i++)
                printf(1," ");
        }
        else printf(1,"%c",sim[k]);
    }
  }
  if(n < 0)
    exit();
}

int
main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    cat(0);
    exit();
  }
  if(argc==2){
    if((fd = open(argv[1], 0)) < 0) //jika tidak ada file
      exit();
    cat(fd);
    close(fd);
  }
  else{
    if((fd = open(argv[2], 0)) < 0)
      exit();
    char arr[1000];
    strcpy(arr,argv[1]);
    i=readint(arr);
    expand(fd,i);
    close(fd);
  }
  exit();
}
