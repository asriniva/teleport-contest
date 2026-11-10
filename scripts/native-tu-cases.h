/* Native/Wasm behavioral cases. This file is included AFTER the existing
 * isolated probe, so every case uses its actual C types and fixture callbacks.
 * Print values/content, never process addresses or host-specific struct padding.
 */
#include <stdio.h>
#include <stdint.h>
static void oracle_number(long long value) { printf("n:%lld\n", value); }
static void oracle_unsigned(unsigned long long value) { printf("u:%llu\n", value); }
static void oracle_text(const char *value) {
    if (!value) { puts("null"); return; }
    fputs("s:", stdout);
    for (; *value; ++value) printf("%02x", (unsigned char)*value);
    putchar('\n');
}
static void oracle_bytes(const void *data, size_t size) {
    const unsigned char *p = data;
    fputs("b:", stdout);
    for (size_t i = 0; i < size; ++i) printf("%02x", p[i]);
    putchar('\n');
}
void probe_native_oracle(void) {
#if ORACLE_ISAAC64
    isaac64_ctx ctx;
    unsigned char seed[256];
    for (int i=0;i<256;i++) seed[i]=(unsigned char)(i*37);
    for(int n=0;n<=256;n+=32) {
        probe_init(&ctx,seed,n);
        for(int i=0;i<600;i++) oracle_unsigned(probe_next(&ctx));
        probe_reseed(&ctx,seed,256-n);
        for(int i=1;i<200;i++) oracle_unsigned(probe_bounded(&ctx,(uint64_t)i*i*i+1));
    }
#elif ORACLE_NHMD4
    NHMD4_CTX ctx; unsigned char input[1024], digest[16];
    for(int i=0;i<1024;i++) input[i]=(unsigned char)(i*37);
    for(int n=0;n<=1024;n+=7) {
        probe_init(&ctx); probe_update(&ctx,input,n/2);probe_update(&ctx,input+n/2,n-n/2);
        probe_final(&ctx,digest); oracle_bytes(digest,16);
    }
#elif ORACLE_STRUTIL
    strbuf_t buffer; char input[1024];
    probe_init(&buffer);
    for(int n=0;n<1000;n+=31) {
        memset(input,'a'+n%26,n); input[n]=0;
        probe_append(&buffer,input); oracle_text(buffer.str); oracle_number(buffer.len);
    }
    probe_append(&buffer,"\nlast\n");probe_crlf(&buffer);oracle_text(buffer.str);probe_empty(&buffer);
    const char *patterns[]={"","*","?","a*","*b","a?b","**a**","*a*b*"};
    const char *texts[]={"","a","A","ab","aBc","aaab","xyz"};
    for(int p=0;p<8;p++)for(int t=0;t<7;t++)for(int ci=0;ci<2;ci++)oracle_number(probe_match(patterns[p],texts[t],ci));
#elif ORACLE_PLACEHOLDER
#error Native behavior case is required for every registered TU
#endif
}
#ifdef TELEPORT_NATIVE_ORACLE
int main(void) { probe_native_oracle(); return 0; }
#endif
