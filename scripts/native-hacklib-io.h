/* Test-only device syscall ABI. Ordinary descriptors still use host libc. */
#pragma once
#include <errno.h>
#include <unistd.h>
#define NATIVE_HACKLIB_DEVICE_BASE 0x10000000
static napi_env native_hacklib_env;
static napi_ref native_hacklib_callback;
static napi_value native_hacklib_io_set(napi_env env, napi_callback_info info)
{
    napi_value args[1]; size_t argc=1;
    napi_get_cb_info(env,info,&argc,args,NULL,NULL);
    if(native_hacklib_callback) napi_delete_reference(env,native_hacklib_callback);
    native_hacklib_env=env;
    napi_create_reference(env,args[0],1,&native_hacklib_callback);
    return native_void(env);
}
static ssize_t native_hacklib_device_io(int writing,int fd,void *memory,size_t size)
{
    napi_env env=native_hacklib_env;
    napi_value callback,receiver,args[3],result,count,error;
    void *bytes; int32_t error_number=0; int64_t transferred=0;
    if(!native_hacklib_callback){errno=EBADF;return -1;}
    napi_get_reference_value(env,native_hacklib_callback,&callback);
    napi_get_undefined(env,&receiver);
    napi_create_string_utf8(env,writing?"write":"read",NAPI_AUTO_LENGTH,&args[0]);
    napi_create_int32(env,fd,&args[1]);
    napi_create_buffer_copy(env,size,memory,&bytes,&args[2]);
    if(napi_call_function(env,receiver,callback,3,args,&result)!=napi_ok){errno=EIO;return -1;}
    napi_get_named_property(env,result,"count",&count);
    napi_get_value_int64(env,count,&transferred);
    napi_get_named_property(env,result,"errno",&error);
    napi_get_value_int32(env,error,&error_number);
    if(transferred < -1 || (transferred>=0 && (uint64_t)transferred>size)) {
        napi_throw_range_error(env,NULL,"Invalid native HACKLIB device transfer count");
        errno=EIO;return -1;
    }
    if(!writing && transferred>0)memcpy(memory,bytes,(size_t)transferred);
    if(transferred<0)errno=error_number;
    return (ssize_t)transferred;
}
ssize_t teleport_native_hacklib_read(int fd,void *memory,size_t size)
{
    return fd>=NATIVE_HACKLIB_DEVICE_BASE
        ?native_hacklib_device_io(0,fd,memory,size):read(fd,memory,size);
}
ssize_t teleport_native_hacklib_write(int fd,const void *memory,size_t size)
{
    return fd>=NATIVE_HACKLIB_DEVICE_BASE
        ?native_hacklib_device_io(1,fd,(void *)memory,size):write(fd,memory,size);
}
