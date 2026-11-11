from pathlib import Path
import struct,subprocess,json,hashlib
import argparse
p=argparse.ArgumentParser();p.add_argument('--out',required=True,type=Path);args=p.parse_args();w=args.out.resolve();f=w/'fixtures';f.mkdir(exist_ok=True);records=[]
# Independent system GIF encoder from known uncompressed BMP; no decoder algorithm or LZW stream copied from the port.
for name,x,y,pattern in [('solid',16,16,0),('two-across',32,16,1),('two-down',16,32,2),('four',32,32,3),('filler',16,16,4)]:
 rgb=lambda i,j:((0,128,255),(255,0,128),(17,240,0),(250,251,252))[0 if pattern==0 else(i//7+j//5)%4 if pattern in[1,2,3]else i%2]
 stride=(x*3+3)//4*4;raw=b''.join(b''.join(bytes(reversed(rgb(i,j)))for i in range(x))+b'\0'*(stride-x*3)for j in range(y-1,-1,-1));header=b'BM'+struct.pack('<IHHI',54+len(raw),0,0,54)+struct.pack('<IiiHHIIiiII',40,x,y,1,24,0,len(raw),2835,2835,0,0);bmp=f/(name+'.bmp');gif=f/(name+'.gif');bmp.write_bytes(header+raw);cmd=['/usr/bin/sips','-s','format','gif',str(bmp),'--out',str(gif)];p=subprocess.run(cmd,text=True,capture_output=True);assert p.returncode==0,p.stderr;records.append({'name':name,'args':cmd,'exit':p.returncode,'stdout':p.stdout,'stderr':p.stderr,'width':x,'height':y,'gifSha256':hashlib.sha256(gif.read_bytes()).hexdigest()})
(f/'encoder-commands.json').write_text(json.dumps(records,indent=2)+'\n')

# Standard GIF image-descriptor interlace-bit variant; compressed bytes remain the independent system encoder's output.
b=bytearray((f/'four.gif').read_bytes());pos=13+(3*(1<<((b[10]&7)+1))if b[10]&128 else 0)
while b[pos]==33:
 pos+=2
 while b[pos]:pos+=1+b[pos]
 pos+=1
assert b[pos]==44
b[pos+9]|=64;(f/'interlaced.gif').write_bytes(b)
(f/'interlace-variant.json').write_text(json.dumps({'source':'four.gif','descriptorOffset':pos,'changedByteOffset':pos+9,'operation':'OR0x40; validGIF interlacedrowinterpretation, compressedencoderbytesunchanged'},indent=2)+'\n')
