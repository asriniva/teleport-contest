// Test-only file/device API. C copy_bytes continues to issue its original syscalls.
import {writeFileSync,readFileSync,openSync,closeSync,unlinkSync} from 'node:fs';
import {join} from 'node:path';
export function createNativeHacklibFS(api,fsRoot) {
    const deviceBase=0x10000000;
    let nextDescriptor=deviceBase;
    const drivers=new Map(),nodes=new Map(),streams=new Map();
    const file=path=>join(fsRoot,path.replace(/^\/+/,''));
    class ErrnoError extends Error {
        constructor(errno) {super('Native test device errno '+errno);this.errno=errno;}
    }
    api._hacklib_set_io((operation,fd,buffer)=>{
        const stream=streams.get(fd);
        if(!stream) throw new Error('Unknown native test device descriptor '+fd);
        try {
            const count=stream.driver[operation](stream,buffer,0,buffer.length,stream.position);
            if(!Number.isSafeInteger(count)||count<0||count>buffer.length)
                throw new RangeError('Invalid native test device transfer count');
            stream.position+=count;
            return {count,errno:0};
        } catch(error) {
            // Preserve the explicitly requested device errno verbatim. Host OS
            // errno values for ordinary descriptors are never translated here.
            if(error instanceof ErrnoError)return {count:-1,errno:error.errno};
            throw error;
        }
    });
    return {
        ErrnoError,
        readFile:path=>readFileSync(file(path)),
        writeFile:(path,data)=>writeFileSync(file(path),data),
        open(path,flags) {
            if(!nodes.has(path))return {fd:openSync(file(path),flags)};
            const driver=drivers.get(nodes.get(path));
            if(!driver)throw new Error('Unregistered native test device '+path);
            const stream={fd:nextDescriptor++,path,position:0,driver};
            streams.set(stream.fd,stream);driver.open?.(stream);
            return stream;
        },
        close(stream) {
            if(streams.has(stream.fd)) {
                stream.driver.close?.(stream);streams.delete(stream.fd);
            } else closeSync(stream.fd);
        },
        unlink(path) {if(nodes.has(path))nodes.delete(path);else unlinkSync(file(path));},
        makedev:(major,minor)=>major*256+minor,
        registerDevice:(device,driver)=>drivers.set(device,driver),
        mkdev:(path,device)=>nodes.set(path,device),
    };
}
