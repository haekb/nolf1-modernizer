//////////////////////////////////////////////////////////////////////////////
// Debug handler for new & delete to get more information out of our memory allocation

#ifndef __DEBUGNEW_H__
#define __DEBUGNEW_H__

#ifdef _DEBUG


// Enable floating point exceptions
#include <float.h>

// Using this define will clear any fp exceptions, and then look for the next one. Lithtech.exe seems ripe with 'em, so use this carefully.
#define _START_STRICT_FP _clearfp(); _controlfp(_EM_INEXACT | _EM_UNDERFLOW | _EM_OVERFLOW, _MCW_EM);
#define _END_STRICT_FP _clearfp(); _controlfp(_EM_INEXACT | _EM_UNDERFLOW | _EM_OVERFLOW | _EM_INVALID | _EM_ZERODIVIDE, _MCW_EM);

// Use this macro in the place of "new"  
#define debug_new(type) debug_new_fn<type >(); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
// Use this macro in the place of "new[]"  (Or "new[]")
#define debug_newa(type, count) debug_new_fna<type >(count); dump_debug_info_new(__FILE__,__LINE__, sizeof(type) * (count))
// Use this macro in the place of "new CType(Param)"
#define debug_new1(type, param1) debug_new_fn_param<type >(param1); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
// Use this macro in the place of "new CType(Param1, Param2)"
#define debug_new2(type, param1, param2) debug_new_fn_param<type >(param1, param2); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))
// Use this macro in the place of "new CType(Param1, Param2, Param3)"
#define debug_new3(type, param1, param2, param3) debug_new_fn_param<type >(param1, param2, param3); dump_debug_info_new(__FILE__,__LINE__, sizeof(type))


// Use this macro in the place of "delete"
#define debug_delete(ptr) debug_delete_fn(ptr); dump_debug_info_delete(__FILE__,__LINE__)
// Use this macro in the place of "delete[]"
#define debug_deletea(ptr) debug_delete_fna(ptr); dump_debug_info_delete(__FILE__,__LINE__)

#else // _DEBUG

#define _START_STRICT_FP
#define _END_STRICT_FP

#define debug_new(type) debug_new_fn<type >()
#define debug_newa(type, count) debug_new_fna<type >(count)
#define debug_new1(type, param1) debug_new_fn_param<type >(param1)
#define debug_new2(type, param1, param2) debug_new_fn_param<type >(param1, param2)
#define debug_new3(type, param1, param2, param3) debug_new_fn_param<type >(param1, param2, param3)

#define debug_delete(ptr) debug_delete_fn(ptr)
#define debug_deletea(ptr) debug_delete_fna(ptr)

#endif // _DEBUG

#include "DebugNew_impl.h"

#endif //__DEBUGNEW_H__