/* Emscripten ABI transport only. The Lua implementation is supplied per
 * module by js/services/wasm-lua-runtime.js; no interpreter is linked here. */
addToLibrary({
  $teleportLuaServices__deps: ['malloc', 'realloc', 'free', '$FS', '$ENV', '$getWasmTableEntry', 'teleport_lua_callback', 'teleport_lua_debug_layout', 'teleport_lua_hook', 'teleport_lua_string_header', 'teleport_lua_userdata_header', 'teleport_lua_memory_layout', 'teleport_lua_sort_clock', 'teleport_lua_sort_time', 'teleport_lua_os_clock_rate', 'teleport_lua_os_difftime', 'teleport_lua_os_calendar', 'teleport_lua_os_mktime', 'teleport_lua_os_strftime', 'teleport_lua_os_remove', 'teleport_lua_os_rename', 'teleport_lua_os_errno', 'teleport_lua_os_error_message', 'teleport_lua_os_tm_layout'],
  $teleportLuaServices: function() {
    return Module['teleportLuaServices'] || (Module['teleportLuaServices'] = {
      heap: () => HEAPU8,
      malloc: size => Number(_malloc(BigInt(size))),
      realloc: (pointer, size) => Number(_realloc(BigInt(pointer), BigInt(size))),
      free: pointer => _free(BigInt(pointer)),
      callback: pointer => getWasmTableEntry(Number(pointer)),
      call: (pointer, state) => _teleport_lua_callback(BigInt(pointer), BigInt(state)),
      hook: (pointer, state, info) => _teleport_lua_hook(BigInt(pointer), BigInt(state), BigInt(info)),
      debugLayout: field => Number(_teleport_lua_debug_layout(field)),
      stringHeader: () => Number(_teleport_lua_string_header()),
      userdataHeader: count => Number(_teleport_lua_userdata_header(count)),
      sortClock: () => _teleport_lua_sort_clock(),
      sortTime: () => _teleport_lua_sort_time(),
      osClockRate: () => _teleport_lua_os_clock_rate(),
      osDifftime: (a,b) => _teleport_lua_os_difftime(a,b),
      osCalendar: (time,utc,pointer) => _teleport_lua_os_calendar(time,utc,BigInt(pointer)),
      osMakeTime: pointer => _teleport_lua_os_mktime(BigInt(pointer)),
      osStrftime: (out,size,format,value) => _teleport_lua_os_strftime(BigInt(out),BigInt(size),BigInt(format),BigInt(value)),
      osRemove: pointer => _teleport_lua_os_remove(BigInt(pointer)),
      osRename: (from,to) => _teleport_lua_os_rename(BigInt(from),BigInt(to)),
      osErrno: () => _teleport_lua_os_errno(),
      osErrorMessage: error => _teleport_lua_os_error_message(error),
      osTMLayout: field => Number(_teleport_lua_os_tm_layout(field)),
      osTimezone: () => ENV['TZ'] === undefined ? Intl.DateTimeFormat().resolvedOptions().timeZone : ENV['TZ'],
      memoryLayout: () => Object.fromEntries(['table','node','value','string','proto','lclosure','cclosure','upvalue','thread','global','callinfo','userdata0','userdata'].map((name, i) => [name, Number(_teleport_lua_memory_layout(i))])),
      readFile: path => {
        var stream = FS.open(path, 'r'), chunks = [], length = 0, buffer = new Uint8Array(8192), count;
        try {
          while ((count = FS.read(stream, buffer, 0, buffer.length))) { chunks.push(buffer.slice(0, count)); length += count; }
          var bytes = new Uint8Array(length), offset = 0;
          for (var chunk of chunks) { bytes.set(chunk, offset); offset += chunk.length; }
          return bytes;
        } catch (error) { error.luaOperation = 'read'; throw error; }
        finally { FS.close(stream); }
      },
      readStdin: () => {
        var chunks = [], length = 0, stream = FS.getStream(0), buffer = new Uint8Array(8192), count;
        while ((count = FS.read(stream, buffer, 0, buffer.length))) { chunks.push(buffer.slice(0, count)); length += count; }
        var bytes = new Uint8Array(length), offset = 0;
        for (var chunk of chunks) { bytes.set(chunk, offset); offset += chunk.length; }
        return bytes;
      },
    });
  },
  teleport_lua_dispatch__deps: ['$teleportLuaServices'],
  teleport_lua_dispatch__sig: 'jppjjjjj',
  teleport_lua_dispatch: function(state, operation, a, b, c, d, e) {
    return Module['nethackLua'].dispatch(teleportLuaServices(), state, operation, a, b, c, d, e);
  },
  teleport_lua_failed__deps: ['$teleportLuaServices'],
  teleport_lua_failed__sig: 'ip',
  teleport_lua_failed: function(state) { return Module['nethackLua'].failed(state); },
  teleport_lua_unprotected__deps: ['$teleportLuaServices'],
  teleport_lua_unprotected__sig: 'vp',
  teleport_lua_unprotected: function(state) { Module['nethackLua'].unprotected(teleportLuaServices(), state); },
});
