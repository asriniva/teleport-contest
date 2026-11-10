// A game process exits its module, not the host scoring process. Emscripten's
// default Node quit_ changes process.exitCode even when callMain catches it.
quit_ = (status, exception) => { throw exception; };
