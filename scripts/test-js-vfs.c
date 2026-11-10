/* Native filesystem oracle only. Run inside a unique test directory; no game
 * files are accessed. Its named errno results avoid host/WASI number confusion.
 * The same source can provide an Emscripten MEMFS test module without callMain. */
#define _DARWIN_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>

static const char *error_name(int code) {
    switch (code) {
    case EACCES:return "EACCES"; case EBADF:return "EBADF";
    case EBUSY:return "EBUSY"; case EEXIST:return "EEXIST";
    case EFBIG:return "EFBIG"; case EINVAL:return "EINVAL";
    case EIO:return "EIO"; case EISDIR:return "EISDIR";
    case EMFILE:return "EMFILE"; case ENAMETOOLONG:return "ENAMETOOLONG";
    case ENOENT:return "ENOENT"; case ENOMEM:return "ENOMEM";
    case ENOSPC:return "ENOSPC"; case ENOTDIR:return "ENOTDIR";
    case ENOTEMPTY:return "ENOTEMPTY"; case ENOTSUP:return "ENOTSUP";
    case EPERM:return "EPERM"; case EROFS:return "EROFS"; case ESPIPE:return "ESPIPE";
    default:return "UNKNOWN";
    }
}
static int flags(int value) {
    int result=(value&3)==2?O_RDWR:(value&3)==1?O_WRONLY:O_RDONLY;
    if(value&64)result|=O_CREAT; if(value&128)result|=O_EXCL;
    if(value&512)result|=O_TRUNC; if(value&1024)result|=O_APPEND;
    if(value&65536)result|=O_DIRECTORY;
    return result;
}
static unsigned char *unhex(const char *s,size_t *length) {
    *length=strlen(s+1)/2; unsigned char *bytes=calloc(*length+1,1);
    for(size_t i=0;i<*length;i++){unsigned c;sscanf(s+1+2*i,"%2x",&c);bytes[i]=c;}
    return bytes;
}
static void hex(const unsigned char *bytes,size_t length) {
    for(size_t i=0;i<length;i++)printf("%02x",bytes[i]);
}
static int compare(const void *a,const void *b){return strcmp(*(char *const *)a,*(char *const *)b);}
int main(int argc,char **argv) {
    if(argc!=2||chdir(argv[1]))return 2;
    char base[PATH_MAX];if(!getcwd(base,sizeof base))return 3;
    char *line=NULL;size_t capacity=0;
    while(getline(&line,&capacity,stdin)>0){
        char *op=strtok(line," \r\n"),*a=strtok(NULL," \r\n"),*b=strtok(NULL," \r\n"),*c=strtok(NULL," \r\n");
        if(!op)continue;
        int result=0;errno=0;
        if(!strcmp(op,"MK"))result=mkdir(a,0777);
        else if(!strcmp(op,"OPEN"))result=open(a,flags(atoi(b)),0666);
        else if(!strcmp(op,"CLOSE"))result=close(atoi(a));
        else if(!strcmp(op,"UNLINK"))result=unlink(a);
        else if(!strcmp(op,"RENAME"))result=rename(a,b);
        else if(!strcmp(op,"RMDIR"))result=rmdir(a);
        else if(!strcmp(op,"CD"))result=chdir(a);
        else if(!strcmp(op,"SEEK")){
            /* Only the configured SET/CUR/END namespace is under test; host
               values3/4 can mean SEEK_DATA/SEEK_HOLE extensions. */
            int whence=atoi(c);if(whence<0||whence>2)whence=INT_MAX;
            off_t position=lseek(atoi(a),(off_t)strtoll(b,NULL,10),whence);
            if(position<0)printf("ERR %s\n",error_name(errno));else printf("OK %lld\n",(long long)position);
            continue;
        }else if(!strcmp(op,"READ")){
            size_t length=strtoul(b,NULL,10);unsigned char *bytes=calloc(length+1,1);
            ssize_t count=!strcmp(c,"-")?read(atoi(a),bytes,length):pread(atoi(a),bytes,length,(off_t)strtoll(c,NULL,10));
            if(count<0)printf("ERR %s\n",error_name(errno));else{printf("OK %zd ",count);hex(bytes,count);puts("");}
            free(bytes);continue;
        }else if(!strcmp(op,"WRITE")){
            size_t length;unsigned char *bytes=unhex(b,&length);
            ssize_t count=!strcmp(c,"-")?write(atoi(a),bytes,length):pwrite(atoi(a),bytes,length,(off_t)strtoll(c,NULL,10));
            if(count<0)printf("ERR %s\n",error_name(errno));else printf("OK %zd\n",count);
            free(bytes);continue;
        }else if(!strcmp(op,"STAT")||!strcmp(op,"FSTAT")){
            struct stat st;result=!strcmp(op,"STAT")?stat(a,&st):fstat(atoi(a),&st);
            if(result<0)printf("ERR %s\n",error_name(errno));
            else printf("OK %s %lld\n",S_ISDIR(st.st_mode)?"dir":"file",S_ISDIR(st.st_mode)?4096:(long long)st.st_size);
            continue;
        }else if(!strcmp(op,"SAME")){
            struct stat x,y;result=fstat(atoi(a),&x);if(!result)result=fstat(atoi(b),&y);
            if(result<0)printf("ERR %s\n",error_name(errno));else printf("OK %d\n",x.st_ino==y.st_ino&&x.st_dev==y.st_dev);
            continue;
        }else if(!strcmp(op,"LS")){
            DIR *dir=opendir(a);if(!dir){printf("ERR %s\n",error_name(errno));continue;}
            char *names[1024];size_t n=0;struct dirent *entry;
            while((entry=readdir(dir))&&n<1024)names[n++]=strdup(entry->d_name);
            closedir(dir);qsort(names,n,sizeof(*names),compare);printf("OK ");
            for(size_t i=0;i<n;i++){if(i)putchar(',');fputs(names[i],stdout);free(names[i]);}puts("");continue;
        }else if(!strcmp(op,"PWD")){
            char cwd[PATH_MAX];if(!getcwd(cwd,sizeof cwd))result=-1;
            else {printf("OK %s\n",cwd[strlen(base)]?cwd+strlen(base):"/");continue;}
        }else return 4;
        if(result<0)printf("ERR %s\n",error_name(errno));else printf("OK %d\n",result);
    }
    free(line);return 0;
}
