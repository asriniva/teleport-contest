#include <dirent.h>
#include <stddef.h>
#include <errno.h>
#include <stdint.h>
#include "__dirent.h"
int sdk_dir_errno(int value){if(value>=0)errno=value;return errno;}
size_t sdk_dir_layout(int i){size_t values[]={sizeof(DIR),offsetof(DIR,tell),offsetof(DIR,fd),offsetof(DIR,buf_pos),offsetof(DIR,buf_end),offsetof(DIR,buf),sizeof(((DIR*)0)->buf),sizeof(struct dirent),offsetof(struct dirent,d_ino),offsetof(struct dirent,d_off),offsetof(struct dirent,d_reclen),offsetof(struct dirent,d_type),offsetof(struct dirent,d_name)};return i>=0&&i<13?values[i]:0;}
