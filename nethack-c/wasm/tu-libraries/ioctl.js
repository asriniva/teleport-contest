// Terminal and signal ABI only; configured policy/control flow lives in JS.
addToLibrary({
  $teleportIoctlServices__deps: ['teleport_ioctl_termio', 'teleport_ioctl_stdin', 'teleport_ioctl_shellers', 'teleport_ioctl_fileno', 'teleport_ioctl_getattr', 'teleport_ioctl_setattr', 'teleport_ioctl_signal', 'teleport_ioctl_kill', 'teleport_ioctl_suspend', 'teleport_ioctl_resume', 'teleport_ioctl_norep', 'teleport_ioctl_pline', 'check_user_string', '$stringToUTF8OnStack'],
  $teleportIoctlServices: function() {
    return {
      heap: () => HEAPU8,
      signedHeap: () => HEAP8,
      termio: () => Number(_teleport_ioctl_termio()),
      stdin: () => Number(_teleport_ioctl_stdin()),
      shellers: () => Number(_teleport_ioctl_shellers()),
      fileno: stream => _teleport_ioctl_fileno(BigInt(stream)),
      tcgetattr: (fd, state) => _teleport_ioctl_getattr(fd, BigInt(state)),
      tcsetattr: (fd, action, state) => _teleport_ioctl_setattr(fd, action, BigInt(state)),
      signal: (sig, handler) => BigInt.asUintN(64, _teleport_ioctl_signal(sig, BigInt.asUintN(64, handler))),
      kill: (pid, sig) => _teleport_ioctl_kill(pid, sig),
      check_user_string: pointer => _check_user_string(BigInt(pointer)),
      suspend_nhwindows: message => _teleport_ioctl_suspend(BigInt(message)),
      resume_nhwindows: () => _teleport_ioctl_resume(),
      Norep: message => _teleport_ioctl_norep(BigInt(stringToUTF8OnStack(message))),
      pline: message => _teleport_ioctl_pline(BigInt(stringToUTF8OnStack(message))),
    };
  },
  $teleportIoctlCall__deps: ['$teleportIoctlServices', '$stackSave', '$stackRestore'],
  $teleportIoctlCall: function(name) {
    var stack = stackSave();
    try { return Module['nethackPorted'].ioctl(teleportIoctlServices(), name); }
    finally { stackRestore(stack); }
  },
  getwindowsz__deps: ['$teleportIoctlCall'], getwindowsz__sig: 'v',
  getwindowsz: function() { teleportIoctlCall('getwindowsz'); },
  getioctls__deps: ['$teleportIoctlCall'], getioctls__sig: 'v',
  getioctls: function() { teleportIoctlCall('getioctls'); },
  setioctls__deps: ['$teleportIoctlCall'], setioctls__sig: 'v',
  setioctls: function() { teleportIoctlCall('setioctls'); },
  dosuspend__deps: ['$teleportIoctlCall'], dosuspend__sig: 'i',
  dosuspend: function() { return teleportIoctlCall('dosuspend'); },
});
