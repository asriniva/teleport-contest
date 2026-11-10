// Terminal storage and native dependencies remain C-owned; this adapter only
// supplies their addresses and the compiler-selected POSIX constants.
export function createIoctlEnvironment(services, layout) {
    if (layout.pointerSize !== 8 || layout.intSize !== 4
        || !layout.POSIX_TYPES || !layout.SUSPEND || !layout.SYSCF
        || layout.USE_WIN_IOCTL)
        throw new Error('Review changed ioctl ABI or terminal configuration');
    return {
        ...services,
        ...layout,
        SIG_DFL: BigInt(layout.SIG_DFL),
        SIG_IGN: BigInt(layout.SIG_IGN),
        get HEAP8() { return services.signedHeap(); },
        get HEAPU8() { return services.heap(); },
        get termio() { return Number(services.termio()); },
        get stdin() { return Number(services.stdin()); },
        sysopt: { get shellers() { return Number(services.shellers()); } },
    };
}
