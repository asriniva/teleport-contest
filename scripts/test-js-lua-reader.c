/* Native Lua 5.4.8 source-loader allocator oracle; test-only. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
typedef struct Block {void *p;size_t n;unsigned id;struct Block *next;} Block;
typedef struct Mem {Block *blocks;size_t bytes,attempt,fail;unsigned nextid;int log;size_t limit;lua_State*L;} Mem;
static void *alloc(void *ud,void *p,size_t old,size_t n){
 Mem*m=ud;Block **at=&m->blocks,*b=NULL;while(*at&&(*at)->p!=p)at=&(*at)->next;if(p){b=*at;if(!b||b->n!=old)abort();}
 if(n&&(++m->attempt>=m->fail||(m->limit&&m->L&&(size_t)(lua_gc(m->L,LUA_GCCOUNT)*1024+lua_gc(m->L,LUA_GCCOUNTB))>m->limit))){if(m->log)printf("{\"event\":\"refused\",\"attempt\":%zu,\"old\":%zu,\"size\":%zu,\"bytes\":%zu}\n",m->attempt,old,n,m->bytes);return NULL;}
 void*q=n?realloc(p,n):(free(p),(void*)NULL);if(n&&!q)abort();
 unsigned id=b?b->id:n?++m->nextid:0;size_t previous=b?b->n:0;m->bytes+=n-previous;
 if(!n){if(b){*at=b->next;free(b);}}else{if(!b){b=malloc(sizeof(*b));b->id=id;b->next=m->blocks;m->blocks=b;}b->p=q;b->n=n;}
 if(m->log)printf("{\"event\":\"alloc\",\"id\":%u,\"old\":%zu,\"size\":%zu,\"bytes\":%zu}\n",id,old,n,m->bytes);return q;
}
static void phase(Mem*m,const char*name,int status){printf("{\"phase\":\"%s\",\"status\":%d,\"bytes\":%zu,\"attempts\":%zu}\n",name,status,m->bytes,m->attempt);}
typedef struct Reader {char*data;size_t length,at,chunk;unsigned calls;} Reader;
static const char*reader(lua_State*L,void*ud,size_t*size){Reader*r=ud;printf("{\"event\":\"read\",\"call\":%u,\"bytes\":%d}\n",++r->calls,lua_gc(L,LUA_GCCOUNT)*1024+lua_gc(L,LUA_GCCOUNTB));if(r->at==r->length){*size=0;return NULL;}*size=r->length-r->at;if(*size>r->chunk)*size=r->chunk;const char*out=r->data+r->at;r->at+=*size;return out;}
int main(int argc,char**argv){
 if(argc<3)return 2;FILE*f=fopen(argv[1],"rb");if(!f)return 3;fseek(f,0,SEEK_END);size_t n=ftell(f);rewind(f);char*data=malloc(n?n:1);if(fread(data,1,n,f)!=n)return 4;fclose(f);
 Mem m={0};m.fail=argc>3?strtoull(argv[3],NULL,10):(size_t)-1;m.log=1;
 lua_State*L=lua_newstate(alloc,&m);phase(&m,"state",L?0:LUA_ERRMEM);if(!L){if(m.bytes||m.blocks)abort();free(data);return 0;}m.L=L;
 Reader r={data,n,0,strtoull(argv[2],NULL,10),0};int rc=lua_load(L,reader,&r,"@fixture.lua","bt");phase(&m,"load",rc);if(rc){const char*error=lua_tostring(L,-1);printf("{\"error\":\"");for(size_t i=0;i<lua_rawlen(L,-1);i++)printf("%02x",(unsigned char)error[i]);puts("\"}");}lua_close(L);phase(&m,"close",0);if(m.bytes||m.blocks)abort();free(data);return 0;
}
