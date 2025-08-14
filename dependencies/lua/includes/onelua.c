/*
** Lua core, libraries, and interpreter in a single file.
** Compiling just this file generates a complete Lua stand-alone
** program:
**
** $ gcc -O2 -std=c99 -o lua onelua.c -lm
**
** or
**
** $ gcc -O2 -std=c89 -DLUA_USE_C89 -o lua onelua.c -lm
**
*/

/* default is to build the full interpreter */
#ifndef MAKE_LIB
#ifndef MAKE_LUAC
#ifndef MAKE_LUA
#define MAKE_LUA
#endif
#endif
#endif


/*
** Choose suitable platform-specific features. Default is no
** platform-specific features. Some of these options may need extra
** libraries such as -ldl -lreadline -lncurses
*/
#if 0
#define LUA_USE_LINUX
#define LUA_USE_MACOSX
#define LUA_USE_POSIX
#define LUA_ANSI
#endif


/* no need to change anything below this line ----------------------------- */

#include "../core/lprefix.h"

#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* setup for luaconf.h */
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c
#include "luaconf.h"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

/* core -- used by all */
#include "../core/io/lzio.c"
#include "../parser/lctype.c"
#include "../parser/lopcodes.c"
#include "../core/memory/lmem.c"
#include "../core/io/lundump.c"
#include "../core/io/ldump.c"
#include "../core/state/lstate.c"
#include "../core/memory/lgc.c"
#include "../parser/llex.c"
#include "../parser/lcode.c"
#include "../parser/lparser.c"
#include "../core/debug/ldebug.c"
#include "../core/objects/lfunc.c"
#include "../core/objects/lobject.c"
#include "../core/objects/ltm.c"
#include "../lib/lstring.c"
#include "../lib/ltable.c"
#include "../core/vm/ldo.c"
#include "../core/vm/lvm.c"
#include "../core/state/lapi.c"

/* auxiliary library -- used by all */
#include "lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "../lib/lbaselib.c"
#include "../lib/lcorolib.c"
#include "../lib/ldblib.c"
#include "../lib/liolib.c"
#include "../lib/lmathlib.c"
#include "../lib/loadlib.c"
#include "../lib/loslib.c"
#include "../lib/lstrlib.c"
#include "../lib/ltablib.c"
#include "../lib/lutf8lib.c"
#include "../lib/linit.c"
#endif

/* lua */
#ifdef MAKE_LUA
#include "lua.c"
#endif

/* luac */
#ifdef MAKE_LUAC
#include "luac.c"
#endif
