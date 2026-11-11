/* Development-only oracle. Links the pinned, unmodified musl qsort body. */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <time.h>
_Static_assert(sizeof(time_t)==8 && (time_t)-1<0,"time_t profile");
void __qsort_r(void *,size_t,size_t,int (*)(const void *,const void *,void *),void *);
static int *base;
static int cmp(const void *a,const void *b,void *arg) {
    printf("%td,%td;",(const int *)a-base,(const int *)b-base);
    int x=*(const int *)a,y=*(const int *)b;
    return (x>y)-(x<y);
}
static int scans(void) {
    int a=0,n=0;unsigned b=0;char word[32]={0};long l=0;unsigned long u=0;
    int result=sscanf(" -17 0xff word!","%d %x %4s%n",&a,&b,word,&n);
    printf("%d,%d,%u,%s,%d\n",result,a,b,word,n);
    a=n=0;word[0]=0;result=sscanf("abc123","%3[a-z]%d%n",word,&a,&n);
    printf("%d,%s,%d,%d\n",result,word,a,n);
    result=sscanf("-9223372036854775808 18446744073709551615","%ld %lu",&l,&u);
    printf("%d,%ld,%lu\n",result,l,u);
    a=19;result=sscanf("","%d",&a);printf("%d,%d\n",result,a);
    result=sscanf("x","%d",&a);printf("%d,%d\n",result,a);
    return 0;
}
static int bounded_copies(void) {
    const size_t lengths[]={0,1,2,3,7,16};
    for(size_t i=0;i<sizeof(lengths)/sizeof(lengths[0]);i++){
        unsigned char out[16];memset(out,0xa5,sizeof out);
        char *p=strncpy((char*)out,"ab",lengths[i]);
        printf("%zu:%d:",lengths[i],p==(char*)out);
        for(size_t j=0;j<sizeof out;j++)printf("%02x",out[j]);
        putchar('\n');
    }
    return 0;
}
int main(int argc,char **argv) {
    if(argc>2&&argv[1][0]=='c'){
        mode_t prior=umask(0);int fd=creat(argv[2],0640);if(fd<0)return 77;
        if(write(fd,"abc",3)!=3||close(fd))return 78;
        fd=creat(argv[2],0600);struct stat info;if(fd<0||fstat(fd,&info))return 79;
        char byte;int unreadable=read(fd,&byte,1)<0&&errno==EBADF;
        printf("%d,%lld,%o,%d\n",fd>=0,(long long)info.st_size,info.st_mode&0777,unreadable);close(fd);
        char absent[4096];snprintf(absent,sizeof absent,"%s.missing/file",argv[2]);errno=0;
        int bad=creat(absent,0600);printf("%d,%d\n",bad,errno==ENOENT);
        unlink(argv[2]);umask(prior);return 0;
    }
    if(argc>1&&argv[1][0]=='d'){long long end,start;while(scanf("%lld %lld",&end,&start)==2)printf("%.17g\n",difftime((time_t)end,(time_t)start));return 0;}
    if(argc>1&&argv[1][0]=='b')return bounded_copies();
    if(argc>1)return scans();
    int n;
    while(scanf("%d",&n)==1) {
        base=calloc(n?n:1,sizeof *base);
        for(int i=0;i<n;i++)if(scanf("%d",base+i)!=1)return 2;
        __qsort_r(base,n,sizeof *base,cmp,0);
        putchar('|');for(int i=0;i<n;i++)printf("%d,",base[i]);putchar('\n');free(base);
    }
    return 0;
}
