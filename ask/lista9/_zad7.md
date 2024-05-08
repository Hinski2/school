# zad 7

---

żeby dostać plik wpisałem ``LD_DEBUG=all /bin/sleep 1 > wynik.txt 2>&1
``
do poruszania się po pliku: ``less -N wynik.txt``
ewentualnie:
```
    211382:     symbol=__vdso_clock_gettime;  lookup in file=linux-vdso.so.1 [0]
    211382:     binding file linux-vdso.so.1 [0] to linux-vdso.so.1 [0]: normal symbol `__vdso_clock_gettime' [LINUX_2.6]
    211382:     symbol=__vdso_gettimeofday;  lookup in file=linux-vdso.so.1 [0]
    211382:     binding file linux-vdso.so.1 [0] to linux-vdso.so.1 [0]: normal symbol `__vdso_gettimeofday' [LINUX_2.6]
    211382:     symbol=__vdso_time;  lookup in file=linux-vdso.so.1 [0]
    211382:     binding file linux-vdso.so.1 [0] to linux-vdso.so.1 [0]: normal symbol `__vdso_time' [LINUX_2.6]
    211382:     symbol=__vdso_getcpu;  lookup in file=linux-vdso.so.1 [0]
    211382:     binding file linux-vdso.so.1 [0] to linux-vdso.so.1 [0]: normal symbol `__vdso_getcpu' [LINUX_2.6]
    211382:     symbol=__vdso_clock_getres;  lookup in file=linux-vdso.so.1 [0]
    211382:     binding file linux-vdso.so.1 [0] to linux-vdso.so.1 [0]: normal symbol `__vdso_clock_getres' [LINUX_2.6]
    211382:
    211382:     file=libc.so.6 [0];  needed by /bin/sleep [0]
    211382:     find library=libc.so.6 [0]; searching
    211382:      search cache=/etc/ld.so.cache
    211382:       trying file=/lib/x86_64-linux-gnu/libc.so.6
    211382:
    211382:     file=libc.so.6 [0];  generating link map
    211382:       dynamic: 0x00007f0a982cabc0  base: 0x00007f0a980b1000   size: 0x0000000000228e50
    211382:         entry: 0x00007f0a980daf50  phdr: 0x00007f0a980b1040  phnum:                 14
    211382:
    211382:     checking for version `GLIBC_2.3.4' in file /lib/x86_64-linux-gnu/libc.so.6 [0] required by file /bin/sleep [0]
    211382:     checking for version `GLIBC_2.4' in file /lib/x86_64-linux-gnu/libc.so.6 [0] required by file /bin/sleep [0]
    211382:     checking for version `GLIBC_2.3' in file /lib/x86_64-linux-gnu/libc.so.6 [0] required by file /bin/sleep [0]
    211382:     checking for version `GLIBC_2.34' in file /lib/x86_64-linux-gnu/libc.so.6 [0] required by file /bin/sleep [0]
    211382:     checking for version `GLIBC_2.2.5' in file /lib/x86_64-linux-gnu/libc.so.6 [0] required by file /bin/sleep [0]
    211382:     checking for version `GLIBC_2.2.5' in file /lib64/ld-linux-x86-64.so.2 [0] required by file /lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     checking for version `GLIBC_2.3' in file /lib64/ld-linux-x86-64.so.2 [0] required by file /lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     checking for version `GLIBC_PRIVATE' in file /lib64/ld-linux-x86-64.so.2 [0] required by file /lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:
    211382:     Initial object scopes
    211382:     object=/bin/sleep [0]
    211382:      scope 0: /bin/sleep /lib/x86_64-linux-gnu/libc.so.6 /lib64/ld-linux-x86-64.so.2
    211382:
    211382:     object=linux-vdso.so.1 [0]
    211382:      scope 0: /bin/sleep /lib/x86_64-linux-gnu/libc.so.6 /lib64/ld-linux-x86-64.so.2
    211382:      scope 1: linux-vdso.so.1
    211382:
    211382:     object=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:      scope 0: /bin/sleep /lib/x86_64-linux-gnu/libc.so.6 /lib64/ld-linux-x86-64.so.2
    211382:
    211382:     object=/lib64/ld-linux-x86-64.so.2 [0]
    211382:      no scope
    211382:
    211382:
    211382:     relocation processing: /lib/x86_64-linux-gnu/libc.so.6 (lazy)
    211382:     symbol=_res;  lookup in file=/bin/sleep [0]
    211382:     symbol=_res;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_res' [GLIBC_2.2.5]
    211382:     symbol=svc_max_pollfd;  lookup in file=/bin/sleep [0]
    211382:     symbol=svc_max_pollfd;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `svc_max_pollfd' [GLIBC_2.2.5]
    211382:     symbol=obstack_alloc_failed_handler;  lookup in file=/bin/sleep [0]
    211382:     symbol=obstack_alloc_failed_handler;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `obstack_alloc_failed_handler' [GLIBC_2.2.5]
    211382:     symbol=__ctype_toupper;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype_toupper;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype_toupper' [GLIBC_2.2.5]
    211382:     symbol=loc1;  lookup in file=/bin/sleep [0]
    211382:     symbol=loc1;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `loc1' [GLIBC_2.2.5]
    211382:     symbol=_dl_argv;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_argv;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_dl_argv;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_dl_argv' [GLIBC_PRIVATE]
    211382:     symbol=__libc_single_threaded;  lookup in file=/bin/sleep [0]
    211382:     symbol=__libc_single_threaded;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__libc_single_threaded' [GLIBC_2.32]
    211382:     symbol=free;  lookup in file=/bin/sleep [0]
    211382:     symbol=free;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `free' [GLIBC_2.2.5]
    211382:     symbol=re_syntax_options;  lookup in file=/bin/sleep [0]
    211382:     symbol=re_syntax_options;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `re_syntax_options' [GLIBC_2.2.5]
    211382:     symbol=rpc_createerr;  lookup in file=/bin/sleep [0]
    211382:     symbol=rpc_createerr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `rpc_createerr' [GLIBC_2.2.5]
    211382:     symbol=stdout;  lookup in file=/bin/sleep [0]
    211382:     symbol=stdout;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `stdout' [GLIBC_2.2.5]
    211382:     symbol=__ctype32_toupper;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype32_toupper;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype32_toupper' [GLIBC_2.2.5]
    211382:     symbol=opterr;  lookup in file=/bin/sleep [0]
    211382:     symbol=opterr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `opterr' [GLIBC_2.2.5]
    211382:     symbol=getdate_err;  lookup in file=/bin/sleep [0]
    211382:     symbol=getdate_err;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `getdate_err' [GLIBC_2.2.5]
    211382:     symbol=__curbrk;  lookup in file=/bin/sleep [0]
    211382:     symbol=__curbrk;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__curbrk' [GLIBC_2.2.5]
    211382:     symbol=loc2;  lookup in file=/bin/sleep [0]
    211382:     symbol=loc2;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `loc2' [GLIBC_2.2.5]
    211382:     symbol=program_invocation_name;  lookup in file=/bin/sleep [0]
    211382:     symbol=program_invocation_name;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `program_invocation_name' [GLIBC_2.2.5]
    211382:     symbol=__fpu_control;  lookup in file=/bin/sleep [0]
    211382:     symbol=__fpu_control;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__fpu_control' [GLIBC_2.2.5]
    211382:     symbol=__libc_enable_secure;  lookup in file=/bin/sleep [0]
    211382:     symbol=__libc_enable_secure;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__libc_enable_secure;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `__libc_enable_secure' [GLIBC_PRIVATE]
    211382:     symbol=_IO_2_1_stderr_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stderr_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stderr_' [GLIBC_2.2.5]
    211382:     symbol=_IO_2_1_stderr_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stderr_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stderr_' [GLIBC_2.2.5]
    211382:     symbol=__rcmd_errstr;  lookup in file=/bin/sleep [0]
    211382:     symbol=__rcmd_errstr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__rcmd_errstr' [GLIBC_2.2.5]
    211382:     symbol=__ctype_b;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype_b;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype_b' [GLIBC_2.2.5]
    211382:     symbol=error_print_progname;  lookup in file=/bin/sleep [0]
    211382:     symbol=error_print_progname;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `error_print_progname' [GLIBC_2.2.5]
    211382:     symbol=stderr;  lookup in file=/bin/sleep [0]
    211382:     symbol=stderr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `stderr' [GLIBC_2.2.5]
    211382:     symbol=obstack_exit_failure;  lookup in file=/bin/sleep [0]
    211382:     symbol=obstack_exit_failure;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `obstack_exit_failure' [GLIBC_2.2.5]
    211382:     symbol=__libc_stack_end;  lookup in file=/bin/sleep [0]
    211382:     symbol=__libc_stack_end;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__libc_stack_end;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `__libc_stack_end' [GLIBC_2.2.5]
    211382:     symbol=__key_encryptsession_pk_LOCAL;  lookup in file=/bin/sleep [0]
    211382:     symbol=__key_encryptsession_pk_LOCAL;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__key_encryptsession_pk_LOCAL' [GLIBC_2.2.5]
    211382:     symbol=_rtld_global_ro;  lookup in file=/bin/sleep [0]
    211382:     symbol=_rtld_global_ro;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_rtld_global_ro;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_rtld_global_ro' [GLIBC_PRIVATE]
    211382:     symbol=argp_program_version;  lookup in file=/bin/sleep [0]
    211382:     symbol=argp_program_version;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `argp_program_version' [GLIBC_2.2.5]
    211382:     symbol=svcauthdes_stats;  lookup in file=/bin/sleep [0]
    211382:     symbol=svcauthdes_stats;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `svcauthdes_stats' [GLIBC_2.2.5]
    211382:     symbol=__check_rhosts_file;  lookup in file=/bin/sleep [0]
    211382:     symbol=__check_rhosts_file;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__check_rhosts_file' [GLIBC_2.2.5]
    211382:     symbol=optind;  lookup in file=/bin/sleep [0]
    211382:     symbol=optind;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `optind' [GLIBC_2.2.5]
    211382:     symbol=_IO_2_1_stdin_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stdin_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stdin_' [GLIBC_2.2.5]
    211382:     symbol=_IO_2_1_stdin_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stdin_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stdin_' [GLIBC_2.2.5]
    211382:     symbol=program_invocation_short_name;  lookup in file=/bin/sleep [0]
    211382:     symbol=program_invocation_short_name;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `program_invocation_short_name' [GLIBC_2.2.5]
    211382:     symbol=__ctype32_tolower;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype32_tolower;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype32_tolower' [GLIBC_2.2.5]
    211382:     symbol=error_message_count;  lookup in file=/bin/sleep [0]
    211382:     symbol=error_message_count;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `error_message_count' [GLIBC_2.2.5]
    211382:     symbol=optopt;  lookup in file=/bin/sleep [0]
    211382:     symbol=optopt;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `optopt' [GLIBC_2.2.5]
    211382:     symbol=__ctype32_b;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype32_b;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype32_b' [GLIBC_2.2.5]
    211382:     symbol=_nl_msg_cat_cntr;  lookup in file=/bin/sleep [0]
    211382:     symbol=_nl_msg_cat_cntr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_nl_msg_cat_cntr' [GLIBC_2.2.5]
    211382:     symbol=__daylight;  lookup in file=/bin/sleep [0]
    211382:     symbol=__daylight;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__daylight' [GLIBC_2.2.5]
    211382:     symbol=_nl_domain_bindings;  lookup in file=/bin/sleep [0]
    211382:     symbol=_nl_domain_bindings;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_nl_domain_bindings' [GLIBC_2.2.5]
    211382:     symbol=argp_program_bug_address;  lookup in file=/bin/sleep [0]
    211382:     symbol=argp_program_bug_address;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `argp_program_bug_address' [GLIBC_2.2.5]
    211382:     symbol=_IO_funlockfile;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_funlockfile;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_funlockfile' [GLIBC_2.2.5]
    211382:     symbol=svc_fdset;  lookup in file=/bin/sleep [0]
    211382:     symbol=svc_fdset;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `svc_fdset' [GLIBC_2.2.5]
    211382:     symbol=__libc_dlerror_result;  lookup in file=/bin/sleep [0]
    211382:     symbol=__libc_dlerror_result;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__libc_dlerror_result' [GLIBC_PRIVATE]
    211382:     symbol=stdin;  lookup in file=/bin/sleep [0]
    211382:     symbol=stdin;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `stdin' [GLIBC_2.2.5]
    211382:     symbol=__timezone;  lookup in file=/bin/sleep [0]
    211382:     symbol=__timezone;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__timezone' [GLIBC_2.2.5]
    211382:     symbol=__ctype_tolower;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype_tolower;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype_tolower' [GLIBC_2.2.5]
    211382:     symbol=_IO_2_1_stdout_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stdout_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stdout_' [GLIBC_2.2.5]
    211382:     symbol=_IO_2_1_stdout_;  lookup in file=/bin/sleep [0]
    211382:     symbol=_IO_2_1_stdout_;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_IO_2_1_stdout_' [GLIBC_2.2.5]
    211382:     symbol=__tzname;  lookup in file=/bin/sleep [0]
    211382:     symbol=__tzname;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__tzname' [GLIBC_2.2.5]
    211382:     symbol=error_one_per_line;  lookup in file=/bin/sleep [0]
    211382:     symbol=error_one_per_line;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `error_one_per_line' [GLIBC_2.2.5]
    211382:     symbol=_res_hconf;  lookup in file=/bin/sleep [0]
    211382:     symbol=_res_hconf;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_res_hconf' [GLIBC_2.2.5]
    211382:     symbol=__key_decryptsession_pk_LOCAL;  lookup in file=/bin/sleep [0]
    211382:     symbol=__key_decryptsession_pk_LOCAL;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__key_decryptsession_pk_LOCAL' [GLIBC_2.2.5]
    211382:     symbol=_rtld_global;  lookup in file=/bin/sleep [0]
    211382:     symbol=_rtld_global;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_rtld_global;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_rtld_global' [GLIBC_PRIVATE]
    211382:     symbol=_rtld_global;  lookup in file=/bin/sleep [0]
    211382:     symbol=_rtld_global;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_rtld_global;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_rtld_global' [GLIBC_PRIVATE]
    211382:     symbol=__progname;  lookup in file=/bin/sleep [0]
    211382:     symbol=__progname;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__progname' [GLIBC_2.2.5]
    211382:     symbol=h_errlist;  lookup in file=/bin/sleep [0]
    211382:     symbol=h_errlist;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `h_errlist' [GLIBC_2.2.5]
    211382:     symbol=__environ;  lookup in file=/bin/sleep [0]
    211382:     symbol=__environ;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__environ' [GLIBC_2.2.5]
    211382:     symbol=argp_err_exit_status;  lookup in file=/bin/sleep [0]
    211382:     symbol=argp_err_exit_status;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `argp_err_exit_status' [GLIBC_2.2.5]
    211382:     symbol=svc_pollfd;  lookup in file=/bin/sleep [0]
    211382:     symbol=svc_pollfd;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `svc_pollfd' [GLIBC_2.2.5]
    211382:     symbol=__progname_full;  lookup in file=/bin/sleep [0]
    211382:     symbol=__progname_full;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__progname_full' [GLIBC_2.2.5]
    211382:     symbol=argp_program_version_hook;  lookup in file=/bin/sleep [0]
    211382:     symbol=argp_program_version_hook;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `argp_program_version_hook' [GLIBC_2.2.5]
    211382:     symbol=optarg;  lookup in file=/bin/sleep [0]
    211382:     symbol=optarg;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `optarg' [GLIBC_2.2.5]
    211382:     symbol=malloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=malloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `malloc' [GLIBC_2.2.5]
    211382:
    211382:     relocation processing: /bin/sleep
    211382:     symbol=__libc_start_main;  lookup in file=/bin/sleep [0]
    211382:     symbol=__libc_start_main;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__libc_start_main' [GLIBC_2.34]
    211382:     symbol=_ITM_deregisterTMCloneTable;  lookup in file=/bin/sleep [0]
    211382:     symbol=_ITM_deregisterTMCloneTable;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_ITM_deregisterTMCloneTable;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     symbol=stdout;  lookup in file=/bin/sleep [0]
    211382:     symbol=stdout;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `stdout' [GLIBC_2.2.5]
    211382:     symbol=optind;  lookup in file=/bin/sleep [0]
    211382:     symbol=optind;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `optind' [GLIBC_2.2.5]
    211382:     symbol=__gmon_start__;  lookup in file=/bin/sleep [0]
    211382:     symbol=__gmon_start__;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__gmon_start__;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     symbol=program_invocation_name;  lookup in file=/bin/sleep [0]
    211382:     symbol=program_invocation_name;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `program_invocation_name' [GLIBC_2.2.5]
    211382:     symbol=_ITM_registerTMCloneTable;  lookup in file=/bin/sleep [0]
    211382:     symbol=_ITM_registerTMCloneTable;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_ITM_registerTMCloneTable;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     symbol=program_invocation_short_name;  lookup in file=/bin/sleep [0]
    211382:     symbol=program_invocation_short_name;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `program_invocation_short_name' [GLIBC_2.2.5]
    211382:     symbol=__cxa_finalize;  lookup in file=/bin/sleep [0]
    211382:     symbol=__cxa_finalize;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__cxa_finalize' [GLIBC_2.2.5]
    211382:     symbol=opterr;  lookup in file=/bin/sleep [0]
    211382:     symbol=opterr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `opterr' [GLIBC_2.2.5]
    211382:     symbol=stderr;  lookup in file=/bin/sleep [0]
    211382:     symbol=stderr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `stderr' [GLIBC_2.2.5]
    211382:     symbol=free;  lookup in file=/bin/sleep [0]
    211382:     symbol=free;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `free' [GLIBC_2.2.5]
    211382:     symbol=abort;  lookup in file=/bin/sleep [0]
    211382:     symbol=abort;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `abort' [GLIBC_2.2.5]
    211382:     symbol=__errno_location;  lookup in file=/bin/sleep [0]
    211382:     symbol=__errno_location;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__errno_location' [GLIBC_2.2.5]
    211382:     symbol=strncmp;  lookup in file=/bin/sleep [0]
    211382:     symbol=strncmp;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strncmp' [GLIBC_2.2.5]
    211382:     symbol=_exit;  lookup in file=/bin/sleep [0]
    211382:     symbol=_exit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_exit' [GLIBC_2.2.5]
    211382:     symbol=__fpending;  lookup in file=/bin/sleep [0]
    211382:     symbol=__fpending;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__fpending' [GLIBC_2.2.5]
    211382:     symbol=strtod;  lookup in file=/bin/sleep [0]
    211382:     symbol=strtod;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strtod' [GLIBC_2.2.5]
    211382:     symbol=textdomain;  lookup in file=/bin/sleep [0]
    211382:     symbol=textdomain;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `textdomain' [GLIBC_2.2.5]
    211382:     symbol=strtod_l;  lookup in file=/bin/sleep [0]
    211382:     symbol=strtod_l;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strtod_l' [GLIBC_2.3]
    211382:     symbol=fclose;  lookup in file=/bin/sleep [0]
    211382:     symbol=fclose;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fclose' [GLIBC_2.2.5]
    211382:     symbol=bindtextdomain;  lookup in file=/bin/sleep [0]
    211382:     symbol=bindtextdomain;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `bindtextdomain' [GLIBC_2.2.5]
    211382:     symbol=dcgettext;  lookup in file=/bin/sleep [0]
    211382:     symbol=dcgettext;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `dcgettext' [GLIBC_2.2.5]
    211382:     symbol=__ctype_get_mb_cur_max;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype_get_mb_cur_max;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype_get_mb_cur_max' [GLIBC_2.2.5]
    211382:     symbol=strlen;  lookup in file=/bin/sleep [0]
    211382:     symbol=strlen;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strlen' [GLIBC_2.2.5]
    211382:     symbol=__stack_chk_fail;  lookup in file=/bin/sleep [0]
    211382:     symbol=__stack_chk_fail;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__stack_chk_fail' [GLIBC_2.4]
    211382:     symbol=getopt_long;  lookup in file=/bin/sleep [0]
    211382:     symbol=getopt_long;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `getopt_long' [GLIBC_2.2.5]
    211382:     symbol=mbrtowc;  lookup in file=/bin/sleep [0]
    211382:     symbol=mbrtowc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `mbrtowc' [GLIBC_2.2.5]
    211382:     symbol=newlocale;  lookup in file=/bin/sleep [0]
    211382:     symbol=newlocale;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `newlocale' [GLIBC_2.3]
    211382:     symbol=nanosleep;  lookup in file=/bin/sleep [0]
    211382:     symbol=nanosleep;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `nanosleep' [GLIBC_2.2.5]
    211382:     symbol=strrchr;  lookup in file=/bin/sleep [0]
    211382:     symbol=strrchr;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strrchr' [GLIBC_2.2.5]
    211382:     symbol=lseek;  lookup in file=/bin/sleep [0]
    211382:     symbol=lseek;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `lseek' [GLIBC_2.2.5]
    211382:     symbol=memset;  lookup in file=/bin/sleep [0]
    211382:     symbol=memset;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `memset' [GLIBC_2.2.5]
    211382:     symbol=memcmp;  lookup in file=/bin/sleep [0]
    211382:     symbol=memcmp;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `memcmp' [GLIBC_2.2.5]
    211382:     symbol=fputs_unlocked;  lookup in file=/bin/sleep [0]
    211382:     symbol=fputs_unlocked;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fputs_unlocked' [GLIBC_2.2.5]
    211382:     symbol=strcmp;  lookup in file=/bin/sleep [0]
    211382:     symbol=strcmp;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `strcmp' [GLIBC_2.2.5]
    211382:     symbol=fputc_unlocked;  lookup in file=/bin/sleep [0]
    211382:     symbol=fputc_unlocked;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fputc_unlocked' [GLIBC_2.2.5]
    211382:     symbol=__memcpy_chk;  lookup in file=/bin/sleep [0]
    211382:     symbol=__memcpy_chk;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__memcpy_chk' [GLIBC_2.3.4]
    211382:     symbol=fileno;  lookup in file=/bin/sleep [0]
    211382:     symbol=fileno;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fileno' [GLIBC_2.2.5]
    211382:     symbol=pause;  lookup in file=/bin/sleep [0]
    211382:     symbol=pause;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `pause' [GLIBC_2.2.5]
    211382:     symbol=malloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=malloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `malloc' [GLIBC_2.2.5]
    211382:     symbol=fflush;  lookup in file=/bin/sleep [0]
    211382:     symbol=fflush;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fflush' [GLIBC_2.2.5]
    211382:     symbol=nl_langinfo;  lookup in file=/bin/sleep [0]
    211382:     symbol=nl_langinfo;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `nl_langinfo' [GLIBC_2.2.5]
    211382:     symbol=__freading;  lookup in file=/bin/sleep [0]
    211382:     symbol=__freading;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__freading' [GLIBC_2.2.5]
    211382:     symbol=realloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=realloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `realloc' [GLIBC_2.2.5]
    211382:     symbol=setlocale;  lookup in file=/bin/sleep [0]
    211382:     symbol=setlocale;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `setlocale' [GLIBC_2.2.5]
    211382:     symbol=__printf_chk;  lookup in file=/bin/sleep [0]
    211382:     symbol=__printf_chk;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__printf_chk' [GLIBC_2.3.4]
    211382:     symbol=error;  lookup in file=/bin/sleep [0]
    211382:     symbol=error;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `error' [GLIBC_2.2.5]
    211382:     symbol=fseeko;  lookup in file=/bin/sleep [0]
    211382:     symbol=fseeko;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fseeko' [GLIBC_2.2.5]
    211382:     symbol=__cxa_atexit;  lookup in file=/bin/sleep [0]
    211382:     symbol=__cxa_atexit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__cxa_atexit' [GLIBC_2.2.5]
    211382:     symbol=exit;  lookup in file=/bin/sleep [0]
    211382:     symbol=exit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `exit' [GLIBC_2.2.5]
    211382:     symbol=fwrite;  lookup in file=/bin/sleep [0]
    211382:     symbol=fwrite;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `fwrite' [GLIBC_2.2.5]
    211382:     symbol=__fprintf_chk;  lookup in file=/bin/sleep [0]
    211382:     symbol=__fprintf_chk;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__fprintf_chk' [GLIBC_2.3.4]
    211382:     symbol=mbsinit;  lookup in file=/bin/sleep [0]
    211382:     symbol=mbsinit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `mbsinit' [GLIBC_2.2.5]
    211382:     symbol=iswprint;  lookup in file=/bin/sleep [0]
    211382:     symbol=iswprint;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `iswprint' [GLIBC_2.2.5]
    211382:     symbol=__ctype_b_loc;  lookup in file=/bin/sleep [0]
    211382:     symbol=__ctype_b_loc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__ctype_b_loc' [GLIBC_2.3]
    211382:     symbol=calloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=calloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `calloc' [GLIBC_2.2.5]
    211382:     symbol=free;  lookup in file=/bin/sleep [0]
    211382:     symbol=free;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `free' [GLIBC_2.2.5]
    211382:     symbol=malloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=malloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `malloc' [GLIBC_2.2.5]
    211382:     symbol=realloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=realloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `realloc' [GLIBC_2.2.5]
    211382:
    211382:     relocation processing: /lib64/ld-linux-x86-64.so.2
    211382:     symbol=__rseq_offset;  lookup in file=/bin/sleep [0]
    211382:     symbol=__rseq_offset;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__rseq_offset;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `__rseq_offset' [GLIBC_2.35]
    211382:     symbol=__rseq_size;  lookup in file=/bin/sleep [0]
    211382:     symbol=__rseq_size;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__rseq_size;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `__rseq_size' [GLIBC_2.35]
    211382:     symbol=_dl_catch_exception;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_catch_exception;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_dl_catch_exception' [GLIBC_PRIVATE]
    211382:     symbol=_dl_signal_exception;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_signal_exception;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_dl_signal_exception' [GLIBC_PRIVATE]
    211382:     symbol=_dl_signal_error;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_signal_error;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_dl_signal_error' [GLIBC_PRIVATE]
    211382:     symbol=_dl_catch_error;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_catch_error;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib64/ld-linux-x86-64.so.2 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `_dl_catch_error' [GLIBC_PRIVATE]
    211382:     symbol=__tunable_get_val;  lookup in file=/bin/sleep [0]
    211382:     symbol=__tunable_get_val;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=__tunable_get_val;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `__tunable_get_val' [GLIBC_PRIVATE]
    211382:
    211382:     calling init: /lib64/ld-linux-x86-64.so.2
    211382:
    211382:
    211382:     calling init: /lib/x86_64-linux-gnu/libc.so.6
    211382:
    211382:
    211382:     initialize program: /bin/sleep
    211382:
    211382:     symbol=_dl_audit_preinit;  lookup in file=/bin/sleep [0]
    211382:     symbol=_dl_audit_preinit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     symbol=_dl_audit_preinit;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_dl_audit_preinit' [GLIBC_PRIVATE]
    211382:
    211382:     transferring control: /bin/sleep
    211382:
    211382:     symbol=realloc;  lookup in file=/bin/sleep [0]
    211382:     symbol=realloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
    211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `realloc' [GLIBC_2.2.5]
```
---

### co robi konsolidator dynamiczny
**Ładowanie współdzielonych obiektów**: Na początku, gdy uruchamiany jest binarny plik z dynamicznym łączeniem, konsolidator dynamiczny ładuje wszystkie wymagane współdzielone obiekty (biblioteki) do przestrzeni adresowej procesu. Używa do tego informacji zawartych w sekcjach dynamicznych plików ELF, które określają, jakie współdzielone obiekty są potrzebne (wpisy DT_NEEDED).
**Rozwiązywanie zależności**: Konsolidator dynamiczny rozwiązuje zewnętrzne referencje między głównym programem a załadowanymi współdzielonymi obiektami. Obejmuje to lokalizowanie i dopasowywanie symboli eksportowanych przez biblioteki do tych, które są wymagane przez program lub inne biblioteki.
**Wykonywanie relokacji**: Przed przekazaniem kontroli do programu, konsolidator dynamiczny przeprowadza wszystkie niezbędne relokacje adresów, co jest kluczowe dla poprawnego odwoływania się do zmiennych i funkcji. Relokacje te są określone w tabelach relokacji (DT_RELA dla jawnych addendów lub DT_REL dla domyślnych).
**Inicjalizacja i terminacja**: Konsolidator dynamiczny zarządza wywoływaniem funkcji inicjalizacyjnych i terminacyjnych dla załadowanych obiektów (DT_INIT, DT_FINI oraz tablice DT_INIT_ARRAY i DT_FINI_ARRAY). Dzięki temu każdy współdzielony obiekt może wykonać potrzebne ustawienia przed rozpoczęciem działania programu oraz odpowiednie operacje czyszczące po jego zakończeniu.
**Obsługa środowiska wykonania**: Konsolidator obsługuje również różne zmienne środowiskowe, takie jak LD_LIBRARY_PATH, LD_PRELOAD, czy LD_BIND_NOW, które mogą modyfikować sposób działania łączenia (np. przez wymuszenie natychmiastowego wiązania lub określenie niestandardowych ścieżek do bibliotek).
**Bezpieczeństwo**: W celu ochrony przed potencjalnymi atakami, konsolidator dynamiczny nie honoruje niektórych zmiennych środowiskowych (np. LD_LIBRARY_PATH, LD_PRELOAD) w środowiskach o podwyższonych uprawnieniach (set-user-ID, set-group-ID), aby zapobiec nieautoryzowanej manipulacji zależnościami lub symbolami.

---

### Wiązania Symboli

Wiązania symboli w kontekście programowania i zarządzania systemami operacyjnymi odnoszą się do procesu rozwiązywania odniesień do zmiennych i funkcji, które są używane w różnych modułach programu, ale nie są zdefiniowane wewnątrz tych modułów. Proces ten jest kluczowy w dynamicznym łączeniu, które pozwala programom wykorzystywać kod i dane z bibliotek współdzielonych w czasie wykonania programu. Oto główne aspekty wiązań symboli:

##### Definicja Symbolu
Symbol w kontekście wiązań może być nazwą funkcji lub zmiennej. Symbol jest "zdefiniowany" w jednym module (na przykład w bibliotece współdzielonej), gdzie jest przypisany do konkretnej lokacji w pamięci lub do konkretnej implementacji.

##### Używanie Symboli
Inne moduły mogą "używać" te symbole, odwołując się do nich przez nazwy, nie znając ich fizycznej lokalizacji w pamięci przed wykonaniem programu. Na przykład, program może wywoływać funkcję, która jest zaimplementowana w załadowanej bibliotece współdzielonej.

##### Wiązanie Statyczne vs. Dynamiczne
**Wiązanie statyczne** zachodzi w czasie kompilacji i łączenia programu, kiedy to wszystkie referencje do symboli są rozwiązywane, a odpowiedni kod i dane są włączane bezpośrednio do wykonywalnego pliku programu.

**Wiązanie dynamiczne** pozwala odłożyć rozwiązanie referencji do czasu wykonania programu. Program wykonywalny zawiera informacje o tym, jakie symbole są potrzebne, ale faktyczne adresy tych symboli są rozwiązywane dopiero podczas ładowania programu do pamięci lub nawet później, kiedy to konkretny symbol jest po raz pierwszy używany (wiązanie leniwe).

##### Procedura Linkage Table (PLT) i Global Offset Table (GOT)
W systemach używających formatu ELF (Executable and Linkable Format), proces dynamicznego wiązania symboli często korzysta z dwóch struktur danych: PLT i GOT.

- **PLT (Procedura Linkage Table)** pomaga zarządzać wywołaniami funkcji do zewnętrznych bibliotek współdzielonych. Przy pierwszym wywołaniu funkcji, PLT kieruje do kodu, który wywołuje odpowiednią procedurę w dynamicznym ładowaczu do rozwiązania adresu funkcji. Po rozwiązaniu, adres funkcji jest zapisywany, a kolejne wywołania funkcji mogą korzystać z tego adresu bezpośrednio.

- **GOT (Global Offset Table)** używana jest do przechowywania adresów zmiennych i funkcji, które mogą być zmieniane podczas wykonania. GOT pozwala na modyfikacje adresów bez zmiany oryginalnego kodu programu, co jest kluczowe dla współdzielenia kodu między różnymi procesami.

##### Znaczenie Wiązań Symboli
Proces wiązania symboli jest fundamentalny dla systemów operacyjnych wspierających współdzielenie kodu (takie jak biblioteki współdzielone) i dla aplikacji wymagających modułowości i możliwości rozszerzania w czasie wykonania. Umożliwia to efektywne zarządzanie pamięcią, redukcję redundancji i zwiększoną elastyczność w rozwijaniu i aktualizowaniu oprogramowania.

---

#### 1. szukanie i ładowanie bibliotek współdzielonych
```
13     211382:     find library=libc.so.6 [0]; searching
14     211382:      search cache=/etc/ld.so.cache
15     211382:       trying file=/lib/x86_64-linux-gnu/libc.so.6
```

#### 2. proces relokacji
```
45     211382:     relocation processing: /lib/x86_64-linux-gnu/libc.so.6 (lazy)
254     211382:     relocation processing: /bin/sleep
436     211382:     relocation processing: /lib64/ld-linux-x86-64.so.2
```
relokacja dostosowuje odwoływanie symboli w programie do rzeczywistych adresów w pamięci komputera. aktualizuje tymczasowe adresy programu na te rzeczywiste
(lazy) wskazuje na odroczone relokacje, które są wykonane dopiero wtedy, gdy dany symbol jest faktycznie potrzebny.

#### 3. wiązanie symboli w trakcie ładowania programu:
```
254    211382:	relocation processing: /bin/sleep
255    211382:	symbol=__libc_start_main;  lookup in file=/bin/sleep [0]
256    211382:	symbol=__libc_start_main;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
257    211382:	binding file /bin/sleep [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `__libc_start_main' [GLIBC_2.34]

```
tutaj widzimy że robimy relokacje na pliku /bin/sleep
przechodzimy się liście symboli i jeśli znajdziemy jakiś symbol w pliku to go bindujemy tak jak to się dzieje w linijkach 256 i 257

#### 4. Przeniesienie kontroli do programu
Po załadowaniu wszystkich wymaganych bibliotek, rozwiązaniu symboli i wykonaniu kodu inicjalizacyjnego, konsolidator przekazuje kontrolę do głównego punktu wejścia programu, rozpoczynając jego wykonanie.

#### 5. wiązanie symboli po jego uruchomieniu
```
462     211382:     calling init: /lib64/ld-linux-x86-64.so.2
463     211382:
464     211382:
465     211382:     calling init: /lib/x86_64-linux-gnu/libc.so.6
466     211382:
467     211382:
468     211382:     initialize program: /bin/sleep
469     211382:
470     211382:     symbol=_dl_audit_preinit;  lookup in file=/bin/sleep [0]
471     211382:     symbol=_dl_audit_preinit;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
472     211382:     symbol=_dl_audit_preinit;  lookup in file=/lib64/ld-linux-x86-64.so.2 [0]
473     211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib64/ld-linux-x86-64.so.2 [0]: normal symbol `_dl_audit_preinit' [GLIBC_PRIVAT    473 E]
474     211382:
475     211382:     transferring control: /bin/sleep
476     211382:
477     211382:     symbol=realloc;  lookup in file=/bin/sleep [0]
478     211382:     symbol=realloc;  lookup in file=/lib/x86_64-linux-gnu/libc.so.6 [0]
479     211382:     binding file /lib/x86_64-linux-gnu/libc.so.6 [0] to /lib/x86_64-linux-gnu/libc.so.6 [0]: normal symbol `realloc' [GLIBC_2.2.5]
```