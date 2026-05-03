# 0 "User/lib/test/test_meter_register.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "User/lib/test/test_meter_register.c"
# 38 "User/lib/test/test_meter_register.c"
typedef void* TaskHandle_t;
typedef unsigned int UBaseType_t;
# 51 "User/lib/test/test_meter_register.c"
# 1 "build_x86/vendor/unity/src/unity.h" 1
# 22 "build_x86/vendor/unity/src/unity.h"
# 1 "build_x86/vendor/unity/src/unity_internals.h" 1
# 16 "build_x86/vendor/unity/src/unity_internals.h"
# 1 "/usr/include/setjmp.h" 1 3 4
# 25 "/usr/include/setjmp.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 392 "/usr/include/features.h" 3 4
# 1 "/usr/include/features-time64.h" 1 3 4
# 20 "/usr/include/features-time64.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 21 "/usr/include/features-time64.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 22 "/usr/include/features-time64.h" 2 3 4
# 393 "/usr/include/features.h" 2 3 4
# 489 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 1 3 4
# 561 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 562 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 563 "/usr/include/x86_64-linux-gnu/sys/cdefs.h" 2 3 4
# 490 "/usr/include/features.h" 2 3 4
# 513 "/usr/include/features.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/x86_64-linux-gnu/gnu/stubs.h" 2 3 4
# 514 "/usr/include/features.h" 2 3 4
# 26 "/usr/include/setjmp.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 2 3 4





# 31 "/usr/include/x86_64-linux-gnu/bits/setjmp.h" 3 4
typedef long int __jmp_buf[8];
# 30 "/usr/include/setjmp.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct___jmp_buf_tag.h" 1 3 4
# 23 "/usr/include/x86_64-linux-gnu/bits/types/struct___jmp_buf_tag.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__sigset_t.h" 1 3 4




typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
# 24 "/usr/include/x86_64-linux-gnu/bits/types/struct___jmp_buf_tag.h" 2 3 4


struct __jmp_buf_tag
  {




    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };
# 31 "/usr/include/setjmp.h" 2 3 4

typedef struct __jmp_buf_tag jmp_buf[1];



extern int setjmp (jmp_buf __env) __attribute__ ((__nothrow__));




extern int __sigsetjmp (struct __jmp_buf_tag __env[1], int __savemask) __attribute__ ((__nothrow__));



extern int _setjmp (struct __jmp_buf_tag __env[1]) __attribute__ ((__nothrow__));
# 54 "/usr/include/setjmp.h" 3 4
extern void longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));





extern void _longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));







typedef struct __jmp_buf_tag sigjmp_buf[1];
# 80 "/usr/include/setjmp.h" 3 4
extern void siglongjmp (sigjmp_buf __env, int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
# 90 "/usr/include/setjmp.h" 3 4

# 17 "build_x86/vendor/unity/src/unity_internals.h" 2



# 1 "/usr/include/math.h" 1 3 4
# 27 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/math.h" 2 3 4









# 1 "/usr/include/x86_64-linux-gnu/bits/types.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 1 3 4
# 19 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/timesize.h" 2 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;


typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;

typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;






typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;



typedef long int __quad_t;
typedef unsigned long int __u_quad_t;







typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
# 141 "/usr/include/x86_64-linux-gnu/bits/types.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/typesizes.h" 1 3 4
# 142 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/time64.h" 1 3 4
# 143 "/usr/include/x86_64-linux-gnu/bits/types.h" 2 3 4


typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;

typedef int __daddr_t;
typedef int __key_t;


typedef int __clockid_t;


typedef void * __timer_t;


typedef long int __blksize_t;




typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;


typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;


typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;


typedef long int __fsword_t;

typedef long int __ssize_t;


typedef long int __syscall_slong_t;

typedef unsigned long int __syscall_ulong_t;



typedef __off64_t __loff_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;




typedef int __sig_atomic_t;
# 38 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libm-simd-decl-stubs.h" 1 3 4
# 26 "/usr/include/x86_64-linux-gnu/bits/math-vector.h" 2 3 4
# 41 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 1 3 4
# 120 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/long-double.h" 1 3 4
# 25 "/usr/include/x86_64-linux-gnu/bits/floatn-common.h" 2 3 4
# 121 "/usr/include/x86_64-linux-gnu/bits/floatn.h" 2 3 4
# 44 "/usr/include/math.h" 2 3 4
# 152 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/flt-eval-method.h" 1 3 4
# 153 "/usr/include/math.h" 2 3 4
# 163 "/usr/include/math.h" 3 4
typedef float float_t;
typedef double double_t;
# 204 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/fp-logb.h" 1 3 4
# 205 "/usr/include/math.h" 2 3 4
# 247 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/fp-fast.h" 1 3 4
# 248 "/usr/include/math.h" 2 3 4
# 312 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsig (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignaling (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 313 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));




 extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));




 extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));



 extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));




 extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));





 extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
 extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));




extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));





extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));







extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 275 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));
# 293 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));
# 435 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
# 314 "/usr/include/math.h" 2 3 4
# 329 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 330 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));




 extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

 extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));





 extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




 extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


 extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));






 extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));



 extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));




 extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));





 extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
 extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));




extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));





extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));







extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 275 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));
# 293 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));
# 435 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));
# 331 "/usr/include/math.h" 2 3 4
# 398 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 399 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 1 3 4
# 53 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




 extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
# 85 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

 extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





 extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


 extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
# 119 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
 extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




 extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


 extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));






 extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



 extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




 extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 177 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));




extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__));
# 213 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));





extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));





 extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
 extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));




extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));







extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));






extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));
# 275 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
# 293 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));
# 435 "/usr/include/x86_64-linux-gnu/bits/mathcalls.h" 3 4
extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
# 400 "/usr/include/math.h" 2 3 4
# 481 "/usr/include/math.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 1 3 4
# 20 "/usr/include/x86_64-linux-gnu/bits/mathcalls-helper-functions.h" 3 4
extern int __fpclassifyf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern int __isinff128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __finitef128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __isnanf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__const__));


extern int __iseqsigf128 (_Float128 __x, _Float128 __y) __attribute__ ((__nothrow__ , __leaf__));


extern int __issignalingf128 (_Float128 __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));
# 482 "/usr/include/math.h" 2 3 4
# 854 "/usr/include/math.h" 3 4
extern int signgam;
# 934 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN =

      0,
    FP_INFINITE =

      1,
    FP_ZERO =

      2,
    FP_SUBNORMAL =

      3,
    FP_NORMAL =

      4
  };
# 1471 "/usr/include/math.h" 3 4

# 21 "build_x86/vendor/unity/src/unity_internals.h" 2



# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 1 3 4
# 145 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 214 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 329 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 3 4
typedef int wchar_t;
# 424 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 3 4
typedef struct {
  long long __max_align_ll __attribute__((__aligned__(__alignof__(long long))));
  long double __max_align_ld __attribute__((__aligned__(__alignof__(long double))));
# 435 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 3 4
} max_align_t;
# 25 "build_x86/vendor/unity/src/unity_internals.h" 2
# 37 "build_x86/vendor/unity/src/unity_internals.h"
# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdint.h" 1 3 4
# 9 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdint.h" 3 4
# 1 "/usr/include/stdint.h" 1 3 4
# 26 "/usr/include/stdint.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/stdint.h" 2 3 4

# 1 "/usr/include/x86_64-linux-gnu/bits/wchar.h" 1 3 4
# 29 "/usr/include/stdint.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 30 "/usr/include/stdint.h" 2 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-intn.h" 3 4
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
# 35 "/usr/include/stdint.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 1 3 4
# 24 "/usr/include/x86_64-linux-gnu/bits/stdint-uintn.h" 3 4
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
# 38 "/usr/include/stdint.h" 2 3 4





typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;


typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;





typedef signed char int_fast8_t;

typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
# 71 "/usr/include/stdint.h" 3 4
typedef unsigned char uint_fast8_t;

typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
# 87 "/usr/include/stdint.h" 3 4
typedef long int intptr_t;


typedef unsigned long int uintptr_t;
# 101 "/usr/include/stdint.h" 3 4
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
# 10 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdint.h" 2 3 4
# 38 "build_x86/vendor/unity/src/unity_internals.h" 2



# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 1 3 4
# 203 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 26 "/usr/include/limits.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/limits.h" 2 3 4
# 195 "/usr/include/limits.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/posix1_lim.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/posix1_lim.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/wordsize.h" 1 3 4
# 28 "/usr/include/x86_64-linux-gnu/bits/posix1_lim.h" 2 3 4
# 161 "/usr/include/x86_64-linux-gnu/bits/posix1_lim.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/local_lim.h" 1 3 4
# 38 "/usr/include/x86_64-linux-gnu/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 39 "/usr/include/x86_64-linux-gnu/bits/local_lim.h" 2 3 4
# 81 "/usr/include/x86_64-linux-gnu/bits/local_lim.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthread_stack_min-dynamic.h" 1 3 4
# 29 "/usr/include/x86_64-linux-gnu/bits/pthread_stack_min-dynamic.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/pthread_stack_min.h" 1 3 4
# 30 "/usr/include/x86_64-linux-gnu/bits/pthread_stack_min-dynamic.h" 2 3 4
# 82 "/usr/include/x86_64-linux-gnu/bits/local_lim.h" 2 3 4
# 162 "/usr/include/x86_64-linux-gnu/bits/posix1_lim.h" 2 3 4
# 196 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/x86_64-linux-gnu/bits/posix2_lim.h" 1 3 4
# 200 "/usr/include/limits.h" 2 3 4
# 204 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 2 3 4
# 8 "/usr/lib/gcc/x86_64-linux-gnu/12/include/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 2 3 4
# 42 "build_x86/vendor/unity/src/unity_internals.h" 2
# 156 "build_x86/vendor/unity/src/unity_internals.h"
    
# 156 "build_x86/vendor/unity/src/unity_internals.h"
   typedef unsigned char UNITY_UINT8;
    typedef unsigned short UNITY_UINT16;
    typedef unsigned int UNITY_UINT32;
    typedef signed char UNITY_INT8;
    typedef signed short UNITY_INT16;
    typedef signed int UNITY_INT32;
# 196 "build_x86/vendor/unity/src/unity_internals.h"
    typedef unsigned long UNITY_UINT64;
    typedef signed long UNITY_INT64;



    typedef UNITY_UINT64 UNITY_UINT;
    typedef UNITY_INT64 UNITY_INT;
# 256 "build_x86/vendor/unity/src/unity_internals.h"
typedef float UNITY_FLOAT;
# 299 "build_x86/vendor/unity/src/unity_internals.h"
  typedef UNITY_FLOAT UNITY_DOUBLE;
# 322 "build_x86/vendor/unity/src/unity_internals.h"
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 1 3 4
# 34 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdarg.h" 3 4

# 40 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 37 "/usr/include/stdio.h" 2 3 4


# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 1 3 4




# 1 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 1 3 4
# 13 "/usr/include/x86_64-linux-gnu/bits/types/__mbstate_t.h" 3 4
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
# 6 "/usr/include/x86_64-linux-gnu/bits/types/__fpos_t.h" 2 3 4




typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
# 40 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 1 3 4
# 10 "/usr/include/x86_64-linux-gnu/bits/types/__fpos64_t.h" 3 4
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
# 41 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__FILE.h" 1 3 4



struct _IO_FILE;
typedef struct _IO_FILE __FILE;
# 42 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/FILE.h" 1 3 4



struct _IO_FILE;


typedef struct _IO_FILE FILE;
# 43 "/usr/include/stdio.h" 2 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 1 3 4
# 35 "/usr/include/x86_64-linux-gnu/bits/types/struct_FILE.h" 3 4
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;




typedef void _IO_lock_t;





struct _IO_FILE
{
  int _flags;


  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;


  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;
  int _flags2;
  __off_t _old_offset;


  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];

  _IO_lock_t *_lock;







  __off64_t _offset;

  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  size_t __pad5;
  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];
};
# 44 "/usr/include/stdio.h" 2 3 4
# 52 "/usr/include/stdio.h" 3 4
typedef __gnuc_va_list va_list;
# 63 "/usr/include/stdio.h" 3 4
typedef __off_t off_t;
# 77 "/usr/include/stdio.h" 3 4
typedef __ssize_t ssize_t;






typedef __fpos_t fpos_t;
# 133 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/stdio_lim.h" 1 3 4
# 134 "/usr/include/stdio.h" 2 3 4
# 143 "/usr/include/stdio.h" 3 4
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;






extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));



extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
# 178 "/usr/include/stdio.h" 3 4
extern int fclose (FILE *__stream);
# 188 "/usr/include/stdio.h" 3 4
extern FILE *tmpfile (void)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 205 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;




extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
# 222 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));






extern int fflush (FILE *__stream);
# 239 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 258 "/usr/include/stdio.h" 3 4
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 293 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 308 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
# 328 "/usr/include/stdio.h" 3 4
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));




extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));







extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));



extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
# 403 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));







extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 434 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 459 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));





extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 513 "/usr/include/stdio.h" 3 4
extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);






extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 538 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);
# 549 "/usr/include/stdio.h" 3 4
extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);
# 565 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);







extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2)));
# 632 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) ;







extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);
# 702 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);







extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);
# 736 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 760 "/usr/include/stdio.h" 3 4
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 786 "/usr/include/stdio.h" 3 4
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;



extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;







extern void perror (const char *__s);




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 823 "/usr/include/stdio.h" 3 4
extern int pclose (FILE *__stream);





extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;






extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));
# 867 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 885 "/usr/include/stdio.h" 3 4
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);
# 909 "/usr/include/stdio.h" 3 4

# 323 "build_x86/vendor/unity/src/unity_internals.h" 2
# 444 "build_x86/vendor/unity/src/unity_internals.h"

# 444 "build_x86/vendor/unity/src/unity_internals.h"
typedef void (*UnityTestFunction)(void);






typedef enum
{
    UNITY_DISPLAY_STYLE_INT = ((32) / 8) + (0x10),
    UNITY_DISPLAY_STYLE_INT8 = 1 + (0x10),
    UNITY_DISPLAY_STYLE_INT16 = 2 + (0x10),
    UNITY_DISPLAY_STYLE_INT32 = 4 + (0x10),

    UNITY_DISPLAY_STYLE_INT64 = 8 + (0x10),


    UNITY_DISPLAY_STYLE_UINT = ((32) / 8) + (0x20),
    UNITY_DISPLAY_STYLE_UINT8 = 1 + (0x20),
    UNITY_DISPLAY_STYLE_UINT16 = 2 + (0x20),
    UNITY_DISPLAY_STYLE_UINT32 = 4 + (0x20),

    UNITY_DISPLAY_STYLE_UINT64 = 8 + (0x20),


    UNITY_DISPLAY_STYLE_HEX8 = 1 + (0x40),
    UNITY_DISPLAY_STYLE_HEX16 = 2 + (0x40),
    UNITY_DISPLAY_STYLE_HEX32 = 4 + (0x40),

    UNITY_DISPLAY_STYLE_HEX64 = 8 + (0x40),


    UNITY_DISPLAY_STYLE_CHAR = 1 + (0x80) + (0x10),

    UNITY_DISPLAY_STYLE_UNKNOWN
} UNITY_DISPLAY_STYLE_T;

typedef enum
{
    UNITY_WITHIN = 0x0,
    UNITY_EQUAL_TO = 0x1,
    UNITY_GREATER_THAN = 0x2,
    UNITY_GREATER_OR_EQUAL = 0x2 + UNITY_EQUAL_TO,
    UNITY_SMALLER_THAN = 0x4,
    UNITY_SMALLER_OR_EQUAL = 0x4 + UNITY_EQUAL_TO,
    UNITY_NOT_EQUAL = 0x0,
    UNITY_UNKNOWN
} UNITY_COMPARISON_T;


typedef enum UNITY_FLOAT_TRAIT
{
    UNITY_FLOAT_IS_NOT_INF = 0,
    UNITY_FLOAT_IS_INF,
    UNITY_FLOAT_IS_NOT_NEG_INF,
    UNITY_FLOAT_IS_NEG_INF,
    UNITY_FLOAT_IS_NOT_NAN,
    UNITY_FLOAT_IS_NAN,
    UNITY_FLOAT_IS_NOT_DET,
    UNITY_FLOAT_IS_DET,
    UNITY_FLOAT_INVALID_TRAIT
} UNITY_FLOAT_TRAIT_T;


typedef enum
{
    UNITY_ARRAY_TO_VAL = 0,
    UNITY_ARRAY_TO_ARRAY,
    UNITY_ARRAY_UNKNOWN
} UNITY_FLAGS_T;

struct UNITY_STORAGE_T
{
    const char* TestFile;
    const char* CurrentTestName;

    const char* CurrentDetail1;
    const char* CurrentDetail2;

    UNITY_UINT CurrentTestLineNumber;
    UNITY_UINT NumberOfTests;
    UNITY_UINT TestFailures;
    UNITY_UINT TestIgnores;
    UNITY_UINT CurrentTestFailed;
    UNITY_UINT CurrentTestIgnored;





    jmp_buf AbortFrame;

};

extern struct UNITY_STORAGE_T Unity;





void UnityBegin(const char* filename);
int UnityEnd(void);
void UnitySetTestFile(const char* filename);
void UnityConcludeTest(void);


void UnityDefaultTestRun(UnityTestFunction Func, const char* FuncName, const int FuncLineNum);
# 585 "build_x86/vendor/unity/src/unity_internals.h"
void UnityPrint(const char* string);





void UnityPrintLen(const char* string, const UNITY_UINT32 length);
void UnityPrintMask(const UNITY_UINT mask, const UNITY_UINT number);
void UnityPrintNumberByStyle(const UNITY_INT number, const UNITY_DISPLAY_STYLE_T style);
void UnityPrintNumber(const UNITY_INT number_to_print);
void UnityPrintNumberUnsigned(const UNITY_UINT number);
void UnityPrintNumberHex(const UNITY_UINT number, const char nibbles_to_print);


void UnityPrintFloat(const UNITY_DOUBLE input_number);
# 610 "build_x86/vendor/unity/src/unity_internals.h"
void UnityAssertEqualNumber(const UNITY_INT expected,
                            const UNITY_INT actual,
                            const char* msg,
                            const UNITY_UINT lineNumber,
                            const UNITY_DISPLAY_STYLE_T style);

void UnityAssertGreaterOrLessOrEqualNumber(const UNITY_INT threshold,
                                           const UNITY_INT actual,
                                           const UNITY_COMPARISON_T compare,
                                           const char *msg,
                                           const UNITY_UINT lineNumber,
                                           const UNITY_DISPLAY_STYLE_T style);

void UnityAssertEqualIntArray( const void* expected,
                              const void* actual,
                              const UNITY_UINT32 num_elements,
                              const char* msg,
                              const UNITY_UINT lineNumber,
                              const UNITY_DISPLAY_STYLE_T style,
                              const UNITY_FLAGS_T flags);

void UnityAssertBits(const UNITY_INT mask,
                     const UNITY_INT expected,
                     const UNITY_INT actual,
                     const char* msg,
                     const UNITY_UINT lineNumber);

void UnityAssertEqualString(const char* expected,
                            const char* actual,
                            const char* msg,
                            const UNITY_UINT lineNumber);

void UnityAssertEqualStringLen(const char* expected,
                            const char* actual,
                            const UNITY_UINT32 length,
                            const char* msg,
                            const UNITY_UINT lineNumber);

void UnityAssertEqualStringArray( const void* expected,
                                  const char** actual,
                                  const UNITY_UINT32 num_elements,
                                  const char* msg,
                                  const UNITY_UINT lineNumber,
                                  const UNITY_FLAGS_T flags);

void UnityAssertEqualMemory( const void* expected,
                             const void* actual,
                             const UNITY_UINT32 length,
                             const UNITY_UINT32 num_elements,
                             const char* msg,
                             const UNITY_UINT lineNumber,
                             const UNITY_FLAGS_T flags);

void UnityAssertNumbersWithin(const UNITY_UINT delta,
                              const UNITY_INT expected,
                              const UNITY_INT actual,
                              const char* msg,
                              const UNITY_UINT lineNumber,
                              const UNITY_DISPLAY_STYLE_T style);

void UnityAssertNumbersArrayWithin(const UNITY_UINT delta,
                                   const void* expected,
                                   const void* actual,
                                   const UNITY_UINT32 num_elements,
                                   const char* msg,
                                   const UNITY_UINT lineNumber,
                                   const UNITY_DISPLAY_STYLE_T style,
                                   const UNITY_FLAGS_T flags);


_Noreturn void UnityFail(const char* message, const UNITY_UINT line);
_Noreturn void UnityIgnore(const char* message, const UNITY_UINT line);





void UnityMessage(const char* message, const UNITY_UINT line);


void UnityAssertFloatsWithin(const UNITY_FLOAT delta,
                             const UNITY_FLOAT expected,
                             const UNITY_FLOAT actual,
                             const char* msg,
                             const UNITY_UINT lineNumber);

void UnityAssertFloatsNotWithin(const UNITY_FLOAT delta,
                                const UNITY_FLOAT expected,
                                const UNITY_FLOAT actual,
                                const char* msg,
                                const UNITY_UINT lineNumber);

void UnityAssertGreaterOrLessFloat(const UNITY_FLOAT threshold,
                                   const UNITY_FLOAT actual,
                                   const UNITY_COMPARISON_T compare,
                                   const char* msg,
                                   const UNITY_UINT linenumber);

void UnityAssertWithinFloatArray(const UNITY_FLOAT delta,
                                 const UNITY_FLOAT* expected,
                                 const UNITY_FLOAT* actual,
                                 const UNITY_UINT32 num_elements,
                                 const char* msg,
                                 const UNITY_UINT lineNumber,
                                 const UNITY_FLAGS_T flags);

void UnityAssertFloatSpecial(const UNITY_FLOAT actual,
                             const char* msg,
                             const UNITY_UINT lineNumber,
                             const UNITY_FLOAT_TRAIT_T style);
# 759 "build_x86/vendor/unity/src/unity_internals.h"
 const void* UnityNumToPtr(const UNITY_INT num, const UNITY_UINT8 size);

 const void* UnityFloatToPtr(const float num);
# 771 "build_x86/vendor/unity/src/unity_internals.h"
extern const char UnityStrOk[];
extern const char UnityStrPass[];
extern const char UnityStrFail[];
extern const char UnityStrIgnore[];

extern const char UnityStrErrFloat[];
extern const char UnityStrErrDouble[];
extern const char UnityStrErr64[];
extern const char UnityStrErrShorthand[];
# 23 "build_x86/vendor/unity/src/unity.h" 2
# 32 "build_x86/vendor/unity/src/unity.h"
void setUp(void);
void tearDown(void);







void suiteSetUp(void);
int suiteTearDown(int num_failures);
# 53 "build_x86/vendor/unity/src/unity.h"
void resetTest(void);
void verifyTest(void);
# 52 "User/lib/test/test_meter_register.c" 2
# 1 "User/lib/inc/meter_register.h" 1
# 20 "User/lib/inc/meter_register.h"
# 1 "User/common/inc/share_types.h" 1



# 1 "User/app/inc/app_cfg.h" 1
# 5 "User/common/inc/share_types.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 1
# 31 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 1
# 52 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
# 1 "/usr/include/string.h" 1 3 4
# 26 "/usr/include/string.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/libc-header-start.h" 1 3 4
# 27 "/usr/include/string.h" 2 3 4






# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 1 3 4
# 34 "/usr/include/string.h" 2 3 4
# 43 "/usr/include/string.h" 3 4

# 43 "/usr/include/string.h" 3 4
extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));




extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 80 "/usr/include/string.h" 3 4
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 107 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 141 "/usr/include/string.h" 3 4
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));

extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));

extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));



# 1 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 1 3 4
# 22 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 3 4
# 1 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 1 3 4
# 27 "/usr/include/x86_64-linux-gnu/bits/types/__locale_t.h" 3 4
struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
};

typedef struct __locale_struct *__locale_t;
# 23 "/usr/include/x86_64-linux-gnu/bits/types/locale_t.h" 2 3 4

typedef __locale_t locale_t;
# 173 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));


extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)))
     __attribute__ ((__access__ (__write_only__, 1, 3)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 246 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 273 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 293 "/usr/include/string.h" 3 4
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 323 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 350 "/usr/include/string.h" 3 4
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));



extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));

extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
# 407 "/usr/include/string.h" 3 4
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
# 432 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
# 458 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));



# 1 "/usr/include/strings.h" 1 3 4
# 23 "/usr/include/strings.h" 3 4
# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stddef.h" 1 3 4
# 24 "/usr/include/strings.h" 2 3 4










extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
# 68 "/usr/include/strings.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 96 "/usr/include/strings.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));






extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));






extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));



extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));



# 463 "/usr/include/string.h" 2 3 4



extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));



extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));




extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
# 489 "/usr/include/string.h" 3 4
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));



extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
# 539 "/usr/include/string.h" 3 4

# 53 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 2

# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/float.h" 1 3 4
# 55 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 2
# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 1 3 4
# 56 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 2
# 73 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
# 124 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
# 1 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h" 1
# 59 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h"
# 1 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h" 1
# 29 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wunused-parameter"
# 71 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  
# 74 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
 struct __attribute__((packed)) T_UINT32 { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_WRITE { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT16_READ { uint16_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_WRITE { uint32_t v; };
#pragma GCC diagnostic pop



#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpacked"
#pragma GCC diagnostic ignored "-Wattributes"
  struct __attribute__((packed, aligned(1))) T_UINT32_READ { uint32_t v; };
#pragma GCC diagnostic pop
# 137 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline __attribute__((__noreturn__)) void __cmsis_start(void)
{
  extern void _start(void) __attribute__((__noreturn__));

  typedef struct __copy_table {
    uint32_t const* src;
    uint32_t* dest;
    uint32_t wlen;
  } __copy_table_t;

  typedef struct __zero_table {
    uint32_t* dest;
    uint32_t wlen;
  } __zero_table_t;

  extern const __copy_table_t __copy_table_start__;
  extern const __copy_table_t __copy_table_end__;
  extern const __zero_table_t __zero_table_start__;
  extern const __zero_table_t __zero_table_end__;

  for (__copy_table_t const* pTable = &__copy_table_start__; pTable < &__copy_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = pTable->src[i];
    }
  }

  for (__zero_table_t const* pTable = &__zero_table_start__; pTable < &__zero_table_end__; ++pTable) {
    for(uint32_t i=0u; i<pTable->wlen; ++i) {
      pTable->dest[i] = 0u;
    }
  }

  _start();
}
# 264 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __ISB(void)
{
  __asm volatile ("isb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DSB(void)
{
  __asm volatile ("dsb 0xF":::"memory");
}







__attribute__((always_inline)) static inline void __DMB(void)
{
  __asm volatile ("dmb 0xF":::"memory");
}
# 298 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __REV(uint32_t value)
{

  return __builtin_bswap32(value);






}
# 317 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __REV16(uint32_t value)
{
  uint32_t result;

  __asm ("rev16 %0, %1" : "=r" (result) : "r" (value) );
  return result;
}
# 332 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline int16_t __REVSH(int16_t value)
{

  return (int16_t)__builtin_bswap16(value);






}
# 352 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __ROR(uint32_t op1, uint32_t op2)
{
  op2 %= 32U;
  if (op2 == 0U)
  {
    return op1;
  }
  return (op1 >> op2) | (op1 << (32U - op2));
}
# 379 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __RBIT(uint32_t value)
{
  uint32_t result;






  uint32_t s = (4U * 8U) - 1U;

  result = value;
  for (value >>= 1U; value != 0U; value >>= 1U)
  {
    result <<= 1U;
    result |= value & 1U;
    s--;
  }
  result <<= s;

  return result;
}
# 409 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint8_t __CLZ(uint32_t value)
{
# 420 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
  if (value == 0U)
  {
    return 32U;
  }
  return __builtin_clz(value);
}
# 713 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline int32_t __SSAT(int32_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 32U))
  {
    const int32_t max = (int32_t)((1U << (sat - 1U)) - 1U);
    const int32_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}
# 738 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __USAT(int32_t val, uint32_t sat)
{
  if (sat <= 31U)
  {
    const uint32_t max = ((1U << sat) - 1U);
    if (val > (int32_t)max)
    {
      return max;
    }
    else if (val < 0)
    {
      return 0U;
    }
  }
  return (uint32_t)val;
}
# 955 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __enable_irq(void)
{
  __asm volatile ("cpsie i" : : : "memory");
}







__attribute__((always_inline)) static inline void __disable_irq(void)
{
  __asm volatile ("cpsid i" : : : "memory");
}







__attribute__((always_inline)) static inline uint32_t __get_CONTROL(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, control" : "=r" (result) );
  return(result);
}
# 1007 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_CONTROL(uint32_t control)
{
  __asm volatile ("MSR control, %0" : : "r" (control) : "memory");
  __ISB();
}
# 1033 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_IPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, ipsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_APSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, apsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_xPSR(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, xpsr" : "=r" (result) );
  return(result);
}







__attribute__((always_inline)) static inline uint32_t __get_PSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, psp" : "=r" (result) );
  return(result);
}
# 1105 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_PSP(uint32_t topOfProcStack)
{
  __asm volatile ("MSR psp, %0" : : "r" (topOfProcStack) : );
}
# 1129 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_MSP(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, msp" : "=r" (result) );
  return(result);
}
# 1159 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_MSP(uint32_t topOfMainStack)
{
  __asm volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}
# 1210 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_PRIMASK(void)
{
  uint32_t result;

  __asm volatile ("MRS %0, primask" : "=r" (result) );
  return(result);
}
# 1240 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline void __set_PRIMASK(uint32_t priMask)
{
  __asm volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
}
# 1594 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
__attribute__((always_inline)) static inline uint32_t __get_FPSCR(void)
{
# 1610 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
  return(0U);

}







__attribute__((always_inline)) static inline void __set_FPSCR(uint32_t fpscr)
{
# 1633 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
  (void)fpscr;

}
# 2215 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_gcc.h"
#pragma GCC diagnostic pop
# 60 "Middlewares/CMSIS/submodule/external/CMSIS_5/CMSIS/Core/Include/cmsis_compiler.h" 2
# 125 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 2
# 301 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
#pragma GCC diagnostic pop
# 342 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
  typedef int8_t q7_t;




  typedef int16_t q15_t;




  typedef int32_t q31_t;




  typedef int64_t q63_t;





  typedef float float32_t;





  typedef double float64_t;
# 621 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
  typedef enum
  {
    ARM_MATH_SUCCESS = 0,
    ARM_MATH_ARGUMENT_ERROR = -1,
    ARM_MATH_LENGTH_ERROR = -2,
    ARM_MATH_SIZE_MISMATCH = -3,
    ARM_MATH_NANINF = -4,
    ARM_MATH_SINGULAR = -5,
    ARM_MATH_TEST_FAILURE = -6,
    ARM_MATH_DECOMPOSITION_FAILURE = -7
  } arm_status;
# 685 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h"
typedef enum {
  ARM_MATH_F16 = 16,
  ARM_MATH_F32 = 32,
  ARM_MATH_F64 = 64,
  ARM_MATH_Q7 = 7,
  ARM_MATH_Q15 = 15,
  ARM_MATH_Q31 = 31
} arm_math_datatype;







 typedef enum {
  ARM_MATH_SCALAR_ARCH = 1,
  ARM_MATH_DSP_EXTENSIONS_ARCH = 2,
  ARM_MATH_HELIUM_ARCH = 3,
  ARM_MATH_NEON_ARCH = 4
} arm_math_target_arch;
# 32 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_memory.h" 1
# 97 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_memory.h"
__attribute__((always_inline)) static inline q31_t read_q15x2 (
  q15_t const * pQ15)
{
  q31_t val;




  val = (pQ15[1] << 16) | (pQ15[0] & 0x0FFFF) ;


  return (val);
}
# 130 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_memory.h"
__attribute__((always_inline)) static inline void write_q15x2_ia (
  q15_t ** pQ15,
  q31_t value)
{
  q31_t val = value;



  (*pQ15)[0] = (q15_t)(val & 0x0FFFF);
  (*pQ15)[1] = (q15_t)((val >> 16) & 0x0FFFF);


 *pQ15 += 2;
}






__attribute__((always_inline)) static inline void write_q15x2 (
  q15_t * pQ15,
  q31_t value)
{
  q31_t val = value;




  pQ15[0] = (q15_t)(val & 0x0FFFF);
  pQ15[1] = (q15_t)(val >> 16);

}







__attribute__((always_inline)) static inline q31_t read_q7x4 (
  q7_t const * pQ7)
{
  q31_t val;




  val =((pQ7[3] & 0x0FF) << 24) | ((pQ7[2] & 0x0FF) << 16) | ((pQ7[1] & 0x0FF) << 8) | (pQ7[0] & 0x0FF);

  return (val);
}
# 202 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_memory.h"
__attribute__((always_inline)) static inline void write_q7x4_ia (
  q7_t ** pQ7,
  q31_t value)
{
  q31_t val = value;



  (*pQ7)[0] = (q7_t)(val & 0x0FF);
  (*pQ7)[1] = (q7_t)((val >> 8) & 0x0FF);
  (*pQ7)[2] = (q7_t)((val >> 16) & 0x0FF);
  (*pQ7)[3] = (q7_t)((val >> 24) & 0x0FF);


  *pQ7 += 4;
}
# 33 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2

# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h" 1
# 40 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_types.h" 1
# 41 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h" 2
# 136 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h"
  __attribute__((always_inline)) static inline q31_t clip_q63_to_q31(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFFFFFF ^ ((q31_t) (x >> 63)))) : (q31_t) x;
  }




  __attribute__((always_inline)) static inline q15_t clip_q63_to_q15(
  q63_t x)
  {
    return ((q31_t) (x >> 32) != ((q31_t) x >> 31)) ?
      ((0x7FFF ^ ((q15_t) (x >> 63)))) : (q15_t) (x >> 15);
  }




  __attribute__((always_inline)) static inline q7_t clip_q31_to_q7(
  q31_t x)
  {
    return ((q31_t) (x >> 24) != ((q31_t) x >> 23)) ?
      ((0x7F ^ ((q7_t) (x >> 31)))) : (q7_t) x;
  }




  __attribute__((always_inline)) static inline q15_t clip_q31_to_q15(
  q31_t x)
  {
    return ((q31_t) (x >> 16) != ((q31_t) x >> 15)) ?
      ((0x7FFF ^ ((q15_t) (x >> 31)))) : (q15_t) x;
  }




  __attribute__((always_inline)) static inline q63_t mult32x64(
  q63_t x,
  q31_t y)
  {
    return ((((q63_t) (x & 0x00000000FFFFFFFF) * y) >> 32) +
            (((q63_t) (x >> 32) * y) ) );
  }
# 245 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h"
  __attribute__((always_inline)) static inline uint32_t __QADD8(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s, t, u;

    r = __SSAT(((((q31_t)x << 24) >> 24) + (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) + (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x << 8) >> 24) + (((q31_t)y << 8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x ) >> 24) + (((q31_t)y ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s << 8) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __QSUB8(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s, t, u;

    r = __SSAT(((((q31_t)x << 24) >> 24) - (((q31_t)y << 24) >> 24)), 8) & (int32_t)0x000000FF;
    s = __SSAT(((((q31_t)x << 16) >> 24) - (((q31_t)y << 16) >> 24)), 8) & (int32_t)0x000000FF;
    t = __SSAT(((((q31_t)x << 8) >> 24) - (((q31_t)y << 8) >> 24)), 8) & (int32_t)0x000000FF;
    u = __SSAT(((((q31_t)x ) >> 24) - (((q31_t)y ) >> 24)), 8) & (int32_t)0x000000FF;

    return ((uint32_t)((u << 24) | (t << 16) | (s << 8) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __QADD16(
  uint32_t x,
  uint32_t y)
  {

    q31_t r = 0, s = 0;

    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x ) >> 16) + (((q31_t)y ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __SHADD16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x ) >> 16) + (((q31_t)y ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __QSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x ) >> 16) - (((q31_t)y ) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __SHSUB16(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x ) >> 16) - (((q31_t)y ) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __QASX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) - (((q31_t)y ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x ) >> 16) + (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __SHASX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) - (((q31_t)y ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x ) >> 16) + (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __QSAX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = __SSAT(((((q31_t)x << 16) >> 16) + (((q31_t)y ) >> 16)), 16) & (int32_t)0x0000FFFF;
    s = __SSAT(((((q31_t)x ) >> 16) - (((q31_t)y << 16) >> 16)), 16) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __SHSAX(
  uint32_t x,
  uint32_t y)
  {
    q31_t r, s;

    r = (((((q31_t)x << 16) >> 16) + (((q31_t)y ) >> 16)) >> 1) & (int32_t)0x0000FFFF;
    s = (((((q31_t)x ) >> 16) - (((q31_t)y << 16) >> 16)) >> 1) & (int32_t)0x0000FFFF;

    return ((uint32_t)((s << 16) | (r )));
  }





  __attribute__((always_inline)) static inline uint32_t __SMUSDX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y ) >> 16)) -
                       ((((q31_t)x ) >> 16) * (((q31_t)y << 16) >> 16)) ));
  }




  __attribute__((always_inline)) static inline uint32_t __SMUADX(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y ) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y << 16) >> 16)) ));
  }





  __attribute__((always_inline)) static inline int32_t __QADD(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63_t)x + (q31_t)y)));
  }





  __attribute__((always_inline)) static inline int32_t __QSUB(
  int32_t x,
  int32_t y)
  {
    return ((int32_t)(clip_q63_to_q31((q63_t)x - (q31_t)y)));
  }





  __attribute__((always_inline)) static inline uint32_t __SMLAD(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y ) >> 16)) +
                       ( ((q31_t)sum ) ) ));
  }





  __attribute__((always_inline)) static inline uint32_t __SMLADX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y ) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum ) ) ));
  }





  __attribute__((always_inline)) static inline uint32_t __SMLSDX(
  uint32_t x,
  uint32_t y,
  uint32_t sum)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y ) >> 16)) -
                       ((((q31_t)x ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q31_t)sum ) ) ));
  }





  __attribute__((always_inline)) static inline uint64_t __SMLALD(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {

    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y ) >> 16)) +
                       ( ((q63_t)sum ) ) ));
  }





  __attribute__((always_inline)) static inline uint64_t __SMLALDX(
  uint32_t x,
  uint32_t y,
  uint64_t sum)
  {

    return ((uint64_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y ) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ( ((q63_t)sum ) ) ));
  }





  __attribute__((always_inline)) static inline uint32_t __SMUAD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) +
                       ((((q31_t)x ) >> 16) * (((q31_t)y ) >> 16)) ));
  }





  __attribute__((always_inline)) static inline uint32_t __SMUSD(
  uint32_t x,
  uint32_t y)
  {
    return ((uint32_t)(((((q31_t)x << 16) >> 16) * (((q31_t)y << 16) >> 16)) -
                       ((((q31_t)x ) >> 16) * (((q31_t)y ) >> 16)) ));
  }





  __attribute__((always_inline)) static inline uint32_t __SXTB16(
  uint32_t x)
  {
    return ((uint32_t)(((((q31_t)x << 24) >> 24) & (q31_t)0x0000FFFF) |
                       ((((q31_t)x << 8) >> 8) & (q31_t)0xFFFF0000) ));
  }




  __attribute__((always_inline)) static inline int32_t __SMMLA(
  int32_t x,
  int32_t y,
  int32_t sum)
  {
    return (sum + (int32_t) (((int64_t) x * y) >> 32));
  }
# 35 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h" 1
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h"
# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/limits.h" 1 3 4
# 37 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h" 2
# 67 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h"
  __attribute__((always_inline)) static inline uint32_t arm_recip_q31(
        q31_t in,
        q31_t * dst,
  const q31_t * pRecipTable)
  {
    q31_t out;
    uint32_t tempVal;
    uint32_t index, i;
    uint32_t signBits;

    if (in > 0)
    {
      signBits = ((uint32_t) (__CLZ( (uint32_t)in) - 1));
    }
    else
    {
      signBits = ((uint32_t) (__CLZ((uint32_t)(-in)) - 1));
    }


    in = (in << signBits);


    index = (uint32_t)(in >> 24);
    index = (index & 0x0000003F);


    out = pRecipTable[index];



    for (i = 0U; i < 2U; i++)
    {
      tempVal = (uint32_t) (((q63_t) in * out) >> 31);
      tempVal = 0x7FFFFFFFu - tempVal;


      out = clip_q63_to_q31(((q63_t) out * tempVal) >> 30);
    }


    *dst = out;


    return (signBits + 1U);
  }






  __attribute__((always_inline)) static inline uint32_t arm_recip_q15(
        q15_t in,
        q15_t * dst,
  const q15_t * pRecipTable)
  {
    q15_t out = 0;
    int32_t tempVal = 0;
    uint32_t index = 0, i = 0;
    uint32_t signBits = 0;

    if (in > 0)
    {
      signBits = ((uint32_t)(__CLZ( (uint32_t)in) - 17));
    }
    else
    {
      signBits = ((uint32_t)(__CLZ((uint32_t)(-in)) - 17));
    }


    in = (q15_t)(in << signBits);


    index = (uint32_t)(in >> 8);
    index = (index & 0x0000003F);


    out = pRecipTable[index];



    for (i = 0U; i < 2U; i++)
    {
      tempVal = (((q31_t) in * out) >> 15);
      tempVal = 0x7FFF - tempVal;

      out = (q15_t) (((q31_t) out * tempVal) >> 14);

    }


    *dst = out;


    return (signBits + 1);
  }
# 173 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h"
static inline void arm_norm_64_to_32u(uint64_t in, int32_t * normalized, int32_t *norm)
{
    int32_t n1;
    int32_t hi = (int32_t) (in >> 32);
    int32_t lo = (int32_t) ((in << 32) >> 32);

    n1 = __CLZ((uint32_t)hi) - 32;
    if (!n1)
    {



        n1 = __CLZ((uint32_t)lo);
        if (!n1)
        {



            *norm = -1;
            *normalized = (((uint32_t) lo) >> 1);
        } else
        {
            if (n1 == 32)
            {



                *norm = 0;
                *normalized = 0;
            } else
            {



                *norm = n1 - 1;
                *normalized = lo << *norm;
            }
        }
    } else
    {



        n1 = 1 - n1;
        *norm = -n1;



        *normalized = (int32_t)(((uint32_t)lo) >> n1) | (hi << (32 - n1));
    }
}
# 232 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h"
static inline int32_t arm_div_int64_to_int32(int64_t num, int32_t den)
{
    int32_t result;
    uint64_t absNum;
    int32_t normalized;
    int32_t norm;





    if (num == 
# 243 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h" 3 4
              (-0x7fffffffffffffffLL - 1LL)
# 243 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h"
                       )
    {
        absNum = 0x7fffffffffffffffLL;
    }
    else
    {
       absNum = (uint64_t) (num > 0 ? num : -num);
    }
    arm_norm_64_to_32u(absNum, &normalized, &norm);
    if (norm > 0)



        result = (int32_t) num / den;
    else



        result = clip_q63_to_q31(num / den);

    return result;
}
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2

# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h" 1
# 31 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math_memory.h" 1
# 32 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h" 2

# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/none.h" 1
# 34 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/utils.h" 1
# 35 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h" 2
# 53 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_mult_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);
# 67 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_mult_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);
# 81 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_mult_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);
# 95 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_mult_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);
# 110 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_mult_f64(
const float64_t * pSrcA,
const float64_t * pSrcB,
   float64_t * pDst,
   uint32_t blockSize);
# 125 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_add_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);
# 140 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
 void arm_add_f64(
 const float64_t * pSrcA,
 const float64_t * pSrcB,
    float64_t * pDst,
    uint32_t blockSize);
# 155 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_add_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);
# 169 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_add_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);
# 183 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_add_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);
# 197 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_sub_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t blockSize);
# 212 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_sub_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        float64_t * pDst,
        uint32_t blockSize);
# 227 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_sub_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        q7_t * pDst,
        uint32_t blockSize);
# 241 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_sub_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t blockSize);
# 255 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_sub_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t blockSize);
# 269 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_scale_f32(
  const float32_t * pSrc,
        float32_t scale,
        float32_t * pDst,
        uint32_t blockSize);
# 284 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_scale_f64(
  const float64_t * pSrc,
        float64_t scale,
        float64_t * pDst,
        uint32_t blockSize);
# 300 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_scale_q7(
  const q7_t * pSrc,
        q7_t scaleFract,
        int8_t shift,
        q7_t * pDst,
        uint32_t blockSize);
# 316 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_scale_q15(
  const q15_t * pSrc,
        q15_t scaleFract,
        int8_t shift,
        q15_t * pDst,
        uint32_t blockSize);
# 332 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_scale_q31(
  const q31_t * pSrc,
        q31_t scaleFract,
        int8_t shift,
        q31_t * pDst,
        uint32_t blockSize);
# 346 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_abs_q7(
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);
# 358 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_abs_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 371 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_abs_f64(
const float64_t * pSrc,
   float64_t * pDst,
   uint32_t blockSize);
# 384 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_abs_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 396 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_abs_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 409 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t blockSize,
        float32_t * result);
# 424 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_dot_prod_f64(
const float64_t * pSrcA,
const float64_t * pSrcB,
   uint32_t blockSize,
   float64_t * result);
# 439 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_dot_prod_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        uint32_t blockSize,
        q31_t * result);
# 453 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q63_t * result);
# 467 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t blockSize,
        q63_t * result);
# 481 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_shift_q7(
  const q7_t * pSrc,
        int8_t shiftBits,
        q7_t * pDst,
        uint32_t blockSize);
# 495 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_shift_q15(
  const q15_t * pSrc,
        int8_t shiftBits,
        q15_t * pDst,
        uint32_t blockSize);
# 509 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_shift_q31(
  const q31_t * pSrc,
        int8_t shiftBits,
        q31_t * pDst,
        uint32_t blockSize);
# 523 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_offset_f64(
const float64_t * pSrc,
   float64_t offset,
   float64_t * pDst,
   uint32_t blockSize);
# 538 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_offset_f32(
  const float32_t * pSrc,
        float32_t offset,
        float32_t * pDst,
        uint32_t blockSize);
# 553 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_offset_q7(
  const q7_t * pSrc,
        q7_t offset,
        q7_t * pDst,
        uint32_t blockSize);
# 567 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_offset_q15(
  const q15_t * pSrc,
        q15_t offset,
        q15_t * pDst,
        uint32_t blockSize);
# 581 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_offset_q31(
  const q31_t * pSrc,
        q31_t offset,
        q31_t * pDst,
        uint32_t blockSize);
# 594 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_negate_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 607 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_negate_f64(
const float64_t * pSrc,
   float64_t * pDst,
   uint32_t blockSize);
# 620 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_negate_q7(
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);
# 632 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_negate_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 644 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_negate_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 656 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_and_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);
# 669 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_and_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);
# 682 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_and_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
          uint32_t blockSize);
# 695 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_or_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);
# 708 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_or_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);
# 721 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_or_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
          uint32_t blockSize);







  void arm_not_u16(
    const uint16_t * pSrc,
          uint16_t * pDst,
          uint32_t blockSize);







  void arm_not_u32(
    const uint32_t * pSrc,
          uint32_t * pDst,
          uint32_t blockSize);







  void arm_not_u8(
    const uint8_t * pSrc,
          uint8_t * pDst,
          uint32_t blockSize);
# 767 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_xor_u16(
    const uint16_t * pSrcA,
    const uint16_t * pSrcB,
          uint16_t * pDst,
          uint32_t blockSize);
# 780 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_xor_u32(
    const uint32_t * pSrcA,
    const uint32_t * pSrcB,
          uint32_t * pDst,
          uint32_t blockSize);
# 793 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
  void arm_xor_u8(
    const uint8_t * pSrcA,
    const uint8_t * pSrcB,
          uint8_t * pDst,
    uint32_t blockSize);
# 808 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_clip_f32(const float32_t * pSrc,
  float32_t * pDst,
  float32_t low,
  float32_t high,
  uint32_t numSamples);
# 823 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_clip_q31(const q31_t * pSrc,
  q31_t * pDst,
  q31_t low,
  q31_t high,
  uint32_t numSamples);
# 838 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_clip_q15(const q15_t * pSrc,
  q15_t * pDst,
  q15_t low,
  q15_t high,
  uint32_t numSamples);
# 853 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h"
void arm_clip_q7(const q7_t * pSrc,
  q7_t * pDst,
  q7_t low,
  q7_t high,
  uint32_t numSamples);
# 38 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h" 1
# 53 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  typedef struct
  {
          uint32_t nValues;
          float32_t x1;
          float32_t xSpacing;
          const float32_t *pYData;
  } arm_linear_interp_instance_f32;




  typedef struct
  {
          uint16_t numRows;
          uint16_t numCols;
          const float32_t *pData;
  } arm_bilinear_interp_instance_f32;




  typedef struct
  {
          uint16_t numRows;
          uint16_t numCols;
          const q31_t *pData;
  } arm_bilinear_interp_instance_q31;




  typedef struct
  {
          uint16_t numRows;
          uint16_t numCols;
          const q15_t *pData;
  } arm_bilinear_interp_instance_q15;




  typedef struct
  {
          uint16_t numRows;
          uint16_t numCols;
          const q7_t *pData;
  } arm_bilinear_interp_instance_q7;





  typedef enum
  {
    ARM_SPLINE_NATURAL = 0,
    ARM_SPLINE_PARABOLIC_RUNOUT = 1
  } arm_spline_type;




  typedef struct
  {
    arm_spline_type type;
    const float32_t * x;
    const float32_t * y;
    uint32_t n_x;
    float32_t * coeffs;
  } arm_spline_instance_f32;
# 131 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  void arm_spline_f32(
        arm_spline_instance_f32 * S,
  const float32_t * xq,
        float32_t * pDst,
        uint32_t blockSize);
# 147 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  void arm_spline_init_f32(
          arm_spline_instance_f32 * S,
          arm_spline_type type,
    const float32_t * x,
    const float32_t * y,
          uint32_t n,
          float32_t * coeffs,
          float32_t * tempBuffer);
# 164 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  float32_t arm_linear_interp_f32(
  const arm_linear_interp_instance_f32 * S,
  float32_t x);
# 181 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  q31_t arm_linear_interp_q31(
  const q31_t * pYData,
  q31_t x,
  uint32_t nValues);
# 199 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  q15_t arm_linear_interp_q15(
  const q15_t * pYData,
  q31_t x,
  uint32_t nValues);
# 216 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
q7_t arm_linear_interp_q7(
  const q7_t * pYData,
  q31_t x,
  uint32_t nValues);
# 228 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  float32_t arm_bilinear_interp_f32(
  const arm_bilinear_interp_instance_f32 * S,
  float32_t X,
  float32_t Y);
# 240 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  q31_t arm_bilinear_interp_q31(
  arm_bilinear_interp_instance_q31 * S,
  q31_t X,
  q31_t Y);
# 253 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  q15_t arm_bilinear_interp_q15(
  arm_bilinear_interp_instance_q15 * S,
  q31_t X,
  q31_t Y);
# 265 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/interpolation_functions.h"
  q7_t arm_bilinear_interp_q7(
  arm_bilinear_interp_instance_q7 * S,
  q31_t X,
  q31_t Y);
# 39 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/bayes_functions.h" 1
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/bayes_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h" 1
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/basic_math_functions.h" 1
# 37 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h" 1
# 80 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  float32_t arm_sin_f32(
  float32_t x);







  q31_t arm_sin_q31(
  q31_t x);






  q15_t arm_sin_q15(
  q15_t x);







  float32_t arm_cos_f32(
  float32_t x);







  q31_t arm_cos_q31(
  q31_t x);







  q15_t arm_cos_q15(
  q15_t x);
# 134 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  void arm_vlog_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 147 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  void arm_vlog_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);
# 160 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  void arm_vlog_q31(const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);







  void arm_vlog_q15(const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 182 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  void arm_vexp_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 195 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  void arm_vexp_f64(
  const float64_t * pSrc,
  float64_t * pDst,
  uint32_t blockSize);
# 236 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
__attribute__((always_inline)) static inline arm_status arm_sqrt_f32(
  const float32_t in,
  float32_t * pOut)
  {
    if (in >= 0.0f)
    {
# 264 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
      *pOut = sqrtf(in);





      return (ARM_MATH_SUCCESS);
    }
    else
    {
      *pOut = 0.0f;
      return (ARM_MATH_ARGUMENT_ERROR);
    }
  }
# 288 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
arm_status arm_sqrt_q31(
  q31_t in,
  q31_t * pOut);
# 301 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
arm_status arm_sqrt_q15(
  q15_t in,
  q15_t * pOut);
# 323 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
arm_status arm_divide_q15(q15_t numerator,
  q15_t denominator,
  q15_t *quotient,
  int16_t *shift);
# 340 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
arm_status arm_divide_q31(q31_t numerator,
  q31_t denominator,
  q31_t *quotient,
  int16_t *shift);
# 354 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  arm_status arm_atan2_f32(float32_t y,float32_t x,float32_t *result);
# 364 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  arm_status arm_atan2_q31(q31_t y,q31_t x,q31_t *result);
# 373 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h"
  arm_status arm_atan2_q15(q15_t y,q15_t x,q15_t *result);
# 38 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h" 2
# 74 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float32_t arm_logsumexp_f32(const float32_t *in, uint32_t blockSize);
# 90 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float32_t arm_logsumexp_dot_prod_f32(const float32_t * pSrcA,
  const float32_t * pSrcB,
  uint32_t blockSize,
  float32_t *pTmpBuffer);
# 105 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float32_t arm_entropy_f32(const float32_t * pSrcA,uint32_t blockSize);
# 118 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float64_t arm_entropy_f64(const float64_t * pSrcA, uint32_t blockSize);
# 130 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float32_t arm_kullback_leibler_f32(const float32_t * pSrcA
  ,const float32_t * pSrcB
  ,uint32_t blockSize);
# 144 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
float64_t arm_kullback_leibler_f64(const float64_t * pSrcA,
                const float64_t * pSrcB,
                uint32_t blockSize);
# 155 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_power_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q63_t * pResult);
# 167 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_power_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 179 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_power_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);
# 191 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_power_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q63_t * pResult);
# 203 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_power_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 215 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_mean_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult);
# 227 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_mean_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 239 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_mean_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 251 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_mean_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 263 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_mean_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);
# 275 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_var_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 287 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_var_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);
# 299 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_var_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 311 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_var_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 323 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_rms_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 335 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_rms_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 347 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_rms_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 359 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_std_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 371 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_std_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);
# 383 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_std_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 395 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_std_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 409 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_min_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);
# 422 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmin_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);







  void arm_absmin_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult);
# 447 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_min_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);
# 460 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmin_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);







  void arm_absmin_no_idx_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 485 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_min_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);
# 498 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmin_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);







  void arm_absmin_no_idx_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 523 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_min_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);
# 536 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmin_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);







  void arm_absmin_no_idx_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 561 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_min_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);
# 574 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmin_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);







  void arm_absmin_no_idx_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);
# 599 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_max_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);
# 612 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmax_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult,
        uint32_t * pIndex);







  void arm_absmax_no_idx_q7(
  const q7_t * pSrc,
        uint32_t blockSize,
        q7_t * pResult);
# 637 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_max_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);
# 650 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmax_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult,
        uint32_t * pIndex);







  void arm_absmax_no_idx_q15(
  const q15_t * pSrc,
        uint32_t blockSize,
        q15_t * pResult);
# 674 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_max_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);
# 687 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmax_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult,
        uint32_t * pIndex);







  void arm_absmax_no_idx_q31(
  const q31_t * pSrc,
        uint32_t blockSize,
        q31_t * pResult);
# 711 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_max_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);
# 724 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmax_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult,
        uint32_t * pIndex);







  void arm_absmax_no_idx_f32(
  const float32_t * pSrc,
        uint32_t blockSize,
        float32_t * pResult);
# 748 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_max_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);
# 761 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
  void arm_absmax_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult,
        uint32_t * pIndex);







  void arm_absmax_no_idx_f64(
  const float64_t * pSrc,
        uint32_t blockSize,
        float64_t * pResult);







  void arm_max_no_idx_f32(
      const float32_t *pSrc,
      uint32_t blockSize,
      float32_t *pResult);







  void arm_min_no_idx_f32(
      const float32_t *pSrc,
      uint32_t blockSize,
      float32_t *pResult);







  void arm_max_no_idx_f64(
      const float64_t *pSrc,
      uint32_t blockSize,
      float64_t *pResult);







  void arm_max_no_idx_q31(
      const q31_t *pSrc,
      uint32_t blockSize,
      q31_t *pResult);







  void arm_max_no_idx_q15(
      const q15_t *pSrc,
      uint32_t blockSize,
      q15_t *pResult);







  void arm_max_no_idx_q7(
      const q7_t *pSrc,
      uint32_t blockSize,
      q7_t *pResult);







  void arm_min_no_idx_f64(
      const float64_t *pSrc,
      uint32_t blockSize,
      float64_t *pResult);







  void arm_min_no_idx_q31(
      const q31_t *pSrc,
      uint32_t blockSize,
      q31_t *pResult);







  void arm_min_no_idx_q15(
      const q15_t *pSrc,
      uint32_t blockSize,
      q15_t *pResult);







void arm_min_no_idx_q7(
     const q7_t *pSrc,
      uint32_t blockSize,
      q7_t *pResult);
# 896 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_mse_q7(
  const q7_t * pSrcA,
  const q7_t * pSrcB,
        uint32_t blockSize,
        q7_t * pResult);
# 910 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_mse_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t blockSize,
        q15_t * pResult);
# 924 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_mse_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t blockSize,
        q31_t * pResult);
# 938 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_mse_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t blockSize,
        float32_t * pResult);
# 952 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_mse_f64(
  const float64_t * pSrcA,
  const float64_t * pSrcB,
        uint32_t blockSize,
        float64_t * pResult);
# 966 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_accumulate_f32(
const float32_t * pSrc,
      uint32_t blockSize,
      float32_t * pResult);
# 978 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h"
void arm_accumulate_f64(
const float64_t * pSrc,
      uint32_t blockSize,
      float64_t * pResult);
# 37 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/bayes_functions.h" 2
# 57 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/bayes_functions.h"
typedef struct
{
  uint32_t vectorDimension;
  uint32_t numberOfClasses;
  const float32_t *theta;
  const float32_t *sigma;
  const float32_t *classPriors;
  float32_t epsilon;
} arm_gaussian_naive_bayes_instance_f32;
# 76 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/bayes_functions.h"
uint32_t arm_gaussian_naive_bayes_predict_f32(const arm_gaussian_naive_bayes_instance_f32 *S,
   const float32_t * in,
   float32_t *pOutputProbabilities,
   float32_t *pBufferB);
# 40 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h" 1
# 118 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  typedef struct
  {
    uint16_t numRows;
    uint16_t numCols;
    float32_t *pData;
  } arm_matrix_instance_f32;




  typedef struct
  {
    uint16_t numRows;
    uint16_t numCols;
    float64_t *pData;
  } arm_matrix_instance_f64;




  typedef struct
  {
    uint16_t numRows;
    uint16_t numCols;
    q7_t *pData;
  } arm_matrix_instance_q7;




  typedef struct
  {
    uint16_t numRows;
    uint16_t numCols;
    q15_t *pData;
  } arm_matrix_instance_q15;




  typedef struct
  {
    uint16_t numRows;
    uint16_t numCols;
    q31_t *pData;
  } arm_matrix_instance_q31;
# 173 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_add_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst);
# 186 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_add_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst);
# 199 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_add_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst);
# 212 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst);
# 225 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst,
        q15_t * pScratch);
# 239 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst);
# 251 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_trans_f32(
  const arm_matrix_instance_f32 * pSrc,
        arm_matrix_instance_f32 * pDst);
# 262 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_trans_f64(
  const arm_matrix_instance_f64 * pSrc,
        arm_matrix_instance_f64 * pDst);
# 273 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_trans_f32(
  const arm_matrix_instance_f32 * pSrc,
  arm_matrix_instance_f32 * pDst);
# 285 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_trans_q15(
  const arm_matrix_instance_q15 * pSrc,
        arm_matrix_instance_q15 * pDst);
# 296 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_trans_q15(
  const arm_matrix_instance_q15 * pSrc,
  arm_matrix_instance_q15 * pDst);
# 307 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_trans_q7(
  const arm_matrix_instance_q7 * pSrc,
        arm_matrix_instance_q7 * pDst);
# 318 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_trans_q31(
  const arm_matrix_instance_q31 * pSrc,
        arm_matrix_instance_q31 * pDst);
# 329 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_cmplx_trans_q31(
  const arm_matrix_instance_q31 * pSrc,
  arm_matrix_instance_q31 * pDst);
# 341 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst);
# 354 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_f64(
  const arm_matrix_instance_f64 * pSrcA,
  const arm_matrix_instance_f64 * pSrcB,
        arm_matrix_instance_f64 * pDst);







void arm_mat_vec_mult_f32(
  const arm_matrix_instance_f32 *pSrcMat,
  const float32_t *pVec,
  float32_t *pDst);
# 379 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_q7(
  const arm_matrix_instance_q7 * pSrcA,
  const arm_matrix_instance_q7 * pSrcB,
        arm_matrix_instance_q7 * pDst,
        q7_t * pState);







void arm_mat_vec_mult_q7(
  const arm_matrix_instance_q7 *pSrcMat,
  const q7_t *pVec,
  q7_t *pDst);
# 405 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst,
        q15_t * pState);







void arm_mat_vec_mult_q15(
  const arm_matrix_instance_q15 *pSrcMat,
  const q15_t *pVec,
  q15_t *pDst);
# 431 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_fast_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst,
        q15_t * pState);
# 445 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst);
# 459 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_opt_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst,
        q31_t *pState);







void arm_mat_vec_mult_q31(
  const arm_matrix_instance_q31 *pSrcMat,
  const q31_t *pVec,
  q31_t *pDst);
# 484 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_mult_fast_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst);
# 497 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_sub_f32(
  const arm_matrix_instance_f32 * pSrcA,
  const arm_matrix_instance_f32 * pSrcB,
        arm_matrix_instance_f32 * pDst);
# 510 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_sub_f64(
  const arm_matrix_instance_f64 * pSrcA,
  const arm_matrix_instance_f64 * pSrcB,
        arm_matrix_instance_f64 * pDst);
# 523 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_sub_q15(
  const arm_matrix_instance_q15 * pSrcA,
  const arm_matrix_instance_q15 * pSrcB,
        arm_matrix_instance_q15 * pDst);
# 536 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_sub_q31(
  const arm_matrix_instance_q31 * pSrcA,
  const arm_matrix_instance_q31 * pSrcB,
        arm_matrix_instance_q31 * pDst);
# 549 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_scale_f32(
  const arm_matrix_instance_f32 * pSrc,
        float32_t scale,
        arm_matrix_instance_f32 * pDst);
# 563 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_scale_q15(
  const arm_matrix_instance_q15 * pSrc,
        q15_t scaleFract,
        int32_t shift,
        arm_matrix_instance_q15 * pDst);
# 578 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_scale_q31(
  const arm_matrix_instance_q31 * pSrc,
        q31_t scaleFract,
        int32_t shift,
        arm_matrix_instance_q31 * pDst);
# 591 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
void arm_mat_init_q31(
        arm_matrix_instance_q31 * S,
        uint16_t nRows,
        uint16_t nColumns,
        q31_t * pData);
# 604 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
void arm_mat_init_q15(
        arm_matrix_instance_q15 * S,
        uint16_t nRows,
        uint16_t nColumns,
        q15_t * pData);
# 617 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
void arm_mat_init_q7(
        arm_matrix_instance_q7 * S,
        uint16_t nRows,
        uint16_t nColumns,
        q7_t * pData);
# 630 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
void arm_mat_init_f32(
        arm_matrix_instance_f32 * S,
        uint16_t nRows,
        uint16_t nColumns,
        float32_t * pData);
# 643 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
void arm_mat_init_f64(
      arm_matrix_instance_f64 * S,
      uint16_t nRows,
      uint16_t nColumns,
      float64_t * pData);
# 659 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_inverse_f32(
  const arm_matrix_instance_f32 * src,
  arm_matrix_instance_f32 * dst);
# 671 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_inverse_f64(
  const arm_matrix_instance_f64 * src,
  arm_matrix_instance_f64 * dst);
# 684 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_cholesky_f64(
  const arm_matrix_instance_f64 * src,
  arm_matrix_instance_f64 * dst);
# 697 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_cholesky_f32(
  const arm_matrix_instance_f32 * src,
  arm_matrix_instance_f32 * dst);
# 708 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_solve_upper_triangular_f32(
  const arm_matrix_instance_f32 * ut,
  const arm_matrix_instance_f32 * a,
  arm_matrix_instance_f32 * dst);
# 720 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_solve_lower_triangular_f32(
  const arm_matrix_instance_f32 * lt,
  const arm_matrix_instance_f32 * a,
  arm_matrix_instance_f32 * dst);
# 733 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_solve_upper_triangular_f64(
  const arm_matrix_instance_f64 * ut,
  const arm_matrix_instance_f64 * a,
  arm_matrix_instance_f64 * dst);
# 745 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_solve_lower_triangular_f64(
  const arm_matrix_instance_f64 * lt,
  const arm_matrix_instance_f64 * a,
  arm_matrix_instance_f64 * dst);
# 761 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_ldlt_f32(
  const arm_matrix_instance_f32 * src,
  arm_matrix_instance_f32 * l,
  arm_matrix_instance_f32 * d,
  uint16_t * pp);
# 777 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
  arm_status arm_mat_ldlt_f64(
  const arm_matrix_instance_f64 * src,
  arm_matrix_instance_f64 * l,
  arm_matrix_instance_f64 * d,
  uint16_t * pp);
# 798 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_qr_f32(
    const arm_matrix_instance_f32 * pSrc,
    const float32_t threshold,
    arm_matrix_instance_f32 * pOutR,
    arm_matrix_instance_f32 * pOutQ,
    float32_t * pOutTau,
    float32_t *pTmpA,
    float32_t *pTmpB
    );
# 823 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
arm_status arm_mat_qr_f64(
    const arm_matrix_instance_f64 * pSrc,
    const float64_t threshold,
    arm_matrix_instance_f64 * pOutR,
    arm_matrix_instance_f64 * pOutQ,
    float64_t * pOutTau,
    float64_t *pTmpA,
    float64_t *pTmpB
    );
# 842 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
float32_t arm_householder_f32(
    const float32_t * pSrc,
    const float32_t threshold,
    uint32_t blockSize,
    float32_t * pOut
    );
# 858 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h"
float64_t arm_householder_f64(
    const float64_t * pSrc,
    const float64_t threshold,
    uint32_t blockSize,
    float64_t * pOut
    );
# 41 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h" 1
# 58 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_conj_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);







  void arm_cmplx_conj_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);
# 81 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_conj_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);
# 93 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_squared_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);
# 105 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_squared_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t numSamples);
# 117 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_squared_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);
# 129 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_squared_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);
# 141 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t numSamples);
# 153 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t numSamples);
# 165 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t numSamples);
# 177 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mag_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);







  void arm_cmplx_mag_fast_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t numSamples);
# 202 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_dot_prod_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        uint32_t numSamples,
        q31_t * realResult,
        q31_t * imagResult);
# 218 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_dot_prod_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        uint32_t numSamples,
        q63_t * realResult,
        q63_t * imagResult);
# 234 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_dot_prod_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        uint32_t numSamples,
        float32_t * realResult,
        float32_t * imagResult);
# 249 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_real_q15(
  const q15_t * pSrcCmplx,
  const q15_t * pSrcReal,
        q15_t * pCmplxDst,
        uint32_t numSamples);
# 263 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_real_q31(
  const q31_t * pSrcCmplx,
  const q31_t * pSrcReal,
        q31_t * pCmplxDst,
        uint32_t numSamples);
# 277 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_real_f32(
  const float32_t * pSrcCmplx,
  const float32_t * pSrcReal,
        float32_t * pCmplxDst,
        uint32_t numSamples);
# 290 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_cmplx_q15(
  const q15_t * pSrcA,
  const q15_t * pSrcB,
        q15_t * pDst,
        uint32_t numSamples);
# 304 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_cmplx_q31(
  const q31_t * pSrcA,
  const q31_t * pSrcB,
        q31_t * pDst,
        uint32_t numSamples);
# 318 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
  void arm_cmplx_mult_cmplx_f32(
  const float32_t * pSrcA,
  const float32_t * pSrcB,
        float32_t * pDst,
        uint32_t numSamples);
# 333 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h"
void arm_cmplx_mult_cmplx_f64(
const float64_t * pSrcA,
const float64_t * pSrcB,
   float64_t * pDst,
   uint32_t numSamples);
# 42 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/statistics_functions.h" 1
# 43 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h" 1
# 90 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  void arm_sin_cos_f32(
        float32_t theta,
        float32_t * pSinVal,
        float32_t * pCosVal);
# 102 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  void arm_sin_cos_q31(
        q31_t theta,
        q31_t * pSinVal,
        q31_t * pCosVal);
# 175 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  typedef struct
  {
          q15_t A0;

          q15_t A1;
          q15_t A2;



          q15_t state[3];
          q15_t Kp;
          q15_t Ki;
          q15_t Kd;
  } arm_pid_instance_q15;





  typedef struct
  {
          q31_t A0;
          q31_t A1;
          q31_t A2;
          q31_t state[3];
          q31_t Kp;
          q31_t Ki;
          q31_t Kd;
  } arm_pid_instance_q31;





  typedef struct
  {
          float32_t A0;
          float32_t A1;
          float32_t A2;
          float32_t state[3];
          float32_t Kp;
          float32_t Ki;
          float32_t Kd;
  } arm_pid_instance_f32;
# 227 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  void arm_pid_init_f32(
        arm_pid_instance_f32 * S,
        int32_t resetStateFlag);






  void arm_pid_reset_f32(
        arm_pid_instance_f32 * S);







  void arm_pid_init_q31(
        arm_pid_instance_q31 * S,
        int32_t resetStateFlag);







  void arm_pid_reset_q31(
        arm_pid_instance_q31 * S);







  void arm_pid_init_q15(
        arm_pid_instance_q15 * S,
        int32_t resetStateFlag);






  void arm_pid_reset_q15(
        arm_pid_instance_q15 * S);
# 287 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  __attribute__((always_inline)) static inline float32_t arm_pid_f32(
  arm_pid_instance_f32 * S,
  float32_t in)
  {
    float32_t out;


    out = (S->A0 * in) +
      (S->A1 * S->state[0]) + (S->A2 * S->state[1]) + (S->state[2]);


    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;


    return (out);

  }
# 321 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline q31_t arm_pid_q31(
  arm_pid_instance_q31 * S,
  q31_t in)
  {
    q63_t acc;
    q31_t out;


    acc = (q63_t) S->A0 * in;


    acc += (q63_t) S->A1 * S->state[0];


    acc += (q63_t) S->A2 * S->state[1];


    out = (q31_t) (acc >> 31U);


    out += S->state[2];


    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;


    return (out);
  }
# 368 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline q15_t arm_pid_q15(
  arm_pid_instance_q15 * S,
  q15_t in)
  {
    q63_t acc;
    q15_t out;
# 385 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
    acc = ((q31_t) S->A0) * in;


    acc += (q31_t) S->A1 * S->state[0];
    acc += (q31_t) S->A2 * S->state[1];



    acc += (q31_t) S->state[2] << 15;


    out = (q15_t) (__SSAT((q31_t)(acc >> 15), 16));


    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;


    return (out);
  }
# 452 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  __attribute__((always_inline)) static inline void arm_park_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pId,
  float32_t * pIq,
  float32_t sinVal,
  float32_t cosVal)
  {

    *pId = Ialpha * cosVal + Ibeta * sinVal;


    *pIq = -Ialpha * sinVal + Ibeta * cosVal;
  }
# 483 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline void arm_park_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pId,
  q31_t * pIq,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;
    q31_t product3, product4;


    product1 = (q31_t) (((q63_t) (Ialpha) * (cosVal)) >> 31);


    product2 = (q31_t) (((q63_t) (Ibeta) * (sinVal)) >> 31);



    product3 = (q31_t) (((q63_t) (Ialpha) * (sinVal)) >> 31);


    product4 = (q31_t) (((q63_t) (Ibeta) * (cosVal)) >> 31);


    *pId = __QADD(product1, product2);


    *pIq = __QSUB(product4, product3);
  }
# 549 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  __attribute__((always_inline)) static inline void arm_inv_park_f32(
  float32_t Id,
  float32_t Iq,
  float32_t * pIalpha,
  float32_t * pIbeta,
  float32_t sinVal,
  float32_t cosVal)
  {

    *pIalpha = Id * cosVal - Iq * sinVal;


    *pIbeta = Id * sinVal + Iq * cosVal;
  }
# 580 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline void arm_inv_park_q31(
  q31_t Id,
  q31_t Iq,
  q31_t * pIalpha,
  q31_t * pIbeta,
  q31_t sinVal,
  q31_t cosVal)
  {
    q31_t product1, product2;
    q31_t product3, product4;


    product1 = (q31_t) (((q63_t) (Id) * (cosVal)) >> 31);


    product2 = (q31_t) (((q63_t) (Iq) * (sinVal)) >> 31);



    product3 = (q31_t) (((q63_t) (Id) * (sinVal)) >> 31);


    product4 = (q31_t) (((q63_t) (Iq) * (cosVal)) >> 31);


    *pIalpha = __QSUB(product1, product2);


    *pIbeta = __QADD(product4, product3);
  }
# 648 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  __attribute__((always_inline)) static inline void arm_clarke_f32(
  float32_t Ia,
  float32_t Ib,
  float32_t * pIalpha,
  float32_t * pIbeta)
  {

    *pIalpha = Ia;


    *pIbeta = (0.57735026919f * Ia + 1.15470053838f * Ib);
  }
# 675 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline void arm_clarke_q31(
  q31_t Ia,
  q31_t Ib,
  q31_t * pIalpha,
  q31_t * pIbeta)
  {
    q31_t product1, product2;


    *pIalpha = Ia;


    product1 = (q31_t) (((q63_t) Ia * 0x24F34E8B) >> 30);


    product2 = (q31_t) (((q63_t) Ib * 0x49E69D16) >> 30);


    *pIbeta = __QADD(product1, product2);
  }
# 728 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
  __attribute__((always_inline)) static inline void arm_inv_clarke_f32(
  float32_t Ialpha,
  float32_t Ibeta,
  float32_t * pIa,
  float32_t * pIb)
  {

    *pIa = Ialpha;


    *pIb = -0.5f * Ialpha + 0.8660254039f * Ibeta;
  }
# 755 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/controller_functions.h"
__attribute__((always_inline)) static inline void arm_inv_clarke_q31(
  q31_t Ialpha,
  q31_t Ibeta,
  q31_t * pIa,
  q31_t * pIb)
  {
    q31_t product1, product2;


    *pIa = Ialpha;


    product1 = (q31_t) (((q63_t) (Ialpha) * (0x40000000)) >> 31);


    product2 = (q31_t) (((q63_t) (Ibeta) * (0x6ED9EBA1)) >> 31);


    *pIb = __QSUB(product2, product1);
  }
# 44 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h" 1
# 52 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_f64_to_float(
  const float64_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);







  void arm_f64_to_q31(
  const float64_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);







  void arm_f64_to_q15(
  const float64_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);







  void arm_f64_to_q7(
  const float64_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);
# 98 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_float_to_f64(
  const float32_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);







  void arm_float_to_q31(
  const float32_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 121 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_float_to_q15(
  const float32_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 133 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_float_to_q7(
  const float32_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);







void arm_q31_to_f64(
const q31_t * pSrc,
      float64_t * pDst,
      uint32_t blockSize);







  void arm_q31_to_float(
  const q31_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 167 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q31_to_q15(
  const q31_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 179 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q31_to_q7(
  const q31_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);







void arm_q15_to_f64(
const q15_t * pSrc,
      float64_t * pDst,
      uint32_t blockSize);







  void arm_q15_to_float(
  const q15_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 213 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q15_to_q31(
  const q15_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 225 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q15_to_q7(
  const q15_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);







void arm_q7_to_f64(
const q7_t * pSrc,
      float64_t * pDst,
      uint32_t blockSize);







  void arm_q7_to_float(
  const q7_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 259 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q7_to_q31(
  const q7_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 271 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_q7_to_q15(
  const q7_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 283 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  typedef enum
  {
    ARM_SORT_BITONIC = 0,

    ARM_SORT_BUBBLE = 1,

    ARM_SORT_HEAP = 2,

    ARM_SORT_INSERTION = 3,

    ARM_SORT_QUICK = 4,

    ARM_SORT_SELECTION = 5

  } arm_sort_alg;




  typedef enum
  {
    ARM_SORT_DESCENDING = 0,

    ARM_SORT_ASCENDING = 1

  } arm_sort_dir;




  typedef struct
  {
    arm_sort_alg alg;
    arm_sort_dir dir;
  } arm_sort_instance_f32;







  void arm_sort_f32(
    const arm_sort_instance_f32 * S,
          float32_t * pSrc,
          float32_t * pDst,
          uint32_t blockSize);






  void arm_sort_init_f32(
    arm_sort_instance_f32 * S,
    arm_sort_alg alg,
    arm_sort_dir dir);




  typedef struct
  {
    arm_sort_dir dir;
    float32_t * buffer;
  } arm_merge_sort_instance_f32;







  void arm_merge_sort_f32(
    const arm_merge_sort_instance_f32 * S,
          float32_t *pSrc,
          float32_t *pDst,
          uint32_t blockSize);






  void arm_merge_sort_init_f32(
    arm_merge_sort_instance_f32 * S,
    arm_sort_dir dir,
    float32_t * buffer);
# 380 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_copy_f32(
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 393 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_copy_f64(
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);
# 406 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_copy_q7(
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);
# 418 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_copy_q15(
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 430 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_copy_q31(
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 442 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_fill_f32(
        float32_t value,
        float32_t * pDst,
        uint32_t blockSize);
# 454 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_fill_f64(
        float64_t value,
        float64_t * pDst,
        uint32_t blockSize);
# 466 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_fill_q7(
        q7_t value,
        q7_t * pDst,
        uint32_t blockSize);
# 478 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_fill_q15(
        q15_t value,
        q15_t * pDst,
        uint32_t blockSize);
# 490 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
  void arm_fill_q31(
        q31_t value,
        q31_t * pDst,
        uint32_t blockSize);
# 511 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
float32_t arm_weighted_average_f32(const float32_t *in
  , const float32_t *weights
  , uint32_t blockSize);
# 527 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h"
void arm_barycenter_f32(const float32_t *in
  , const float32_t *weights
  , float32_t *out
  , uint32_t nbVectors
  , uint32_t vecDim);
# 45 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h" 1
# 39 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/matrix_functions.h" 1
# 40 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h" 2
# 71 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_euclidean_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 82 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float64_t arm_euclidean_distance_f64(const float64_t *pA,const float64_t *pB, uint32_t blockSize);
# 92 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_braycurtis_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 107 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_canberra_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 118 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_chebyshev_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 129 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float64_t arm_chebyshev_distance_f64(const float64_t *pA,const float64_t *pB, uint32_t blockSize);
# 140 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_cityblock_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 150 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float64_t arm_cityblock_distance_f64(const float64_t *pA,const float64_t *pB, uint32_t blockSize);
# 163 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_correlation_distance_f32(float32_t *pA,float32_t *pB, uint32_t blockSize);
# 175 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_cosine_distance_f32(const float32_t *pA,const float32_t *pB, uint32_t blockSize);
# 187 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float64_t arm_cosine_distance_f64(const float64_t *pA,const float64_t *pB, uint32_t blockSize);
# 209 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_jensenshannon_distance_f32(const float32_t *pA,const float32_t *pB,uint32_t blockSize);
# 224 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_minkowski_distance_f32(const float32_t *pA,const float32_t *pB, int32_t order, uint32_t blockSize);
# 238 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_dice_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 250 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_hamming_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 262 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_jaccard_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 274 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_kulsinski_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 286 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_rogerstanimoto_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 298 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_russellrao_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 310 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_sokalmichener_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 322 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_sokalsneath_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);
# 334 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
float32_t arm_yule_distance(const uint32_t *pA, const uint32_t *pB, uint32_t numberOfBools);

typedef enum
  {
    ARM_DTW_SAKOE_CHIBA_WINDOW = 1,

    ARM_DTW_SLANTED_BAND_WINDOW = 3
  } arm_dtw_window;
# 351 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
arm_status arm_dtw_init_window_q7(const arm_dtw_window windowType,
                                  const int32_t windowSize,
                                  arm_matrix_instance_q7 *pWindow);
# 365 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
arm_status arm_dtw_distance_f32(const arm_matrix_instance_f32 *pDistance,
                               const arm_matrix_instance_q7 *pWindow,
                               arm_matrix_instance_f32 *pDTW,
                               float32_t *distance);
# 379 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/distance_functions.h"
void arm_dtw_path_f32(const arm_matrix_instance_f32 *pDTW,
                      int16_t *pPath,
                      uint32_t *pathLength);
# 46 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h" 1
# 35 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_defines.h" 1
# 34 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_defines.h"
typedef enum
{
    ARM_ML_KERNEL_LINEAR = 0,

    ARM_ML_KERNEL_POLYNOMIAL = 1,

    ARM_ML_KERNEL_RBF = 2,

    ARM_ML_KERNEL_SIGMOID = 3

} arm_ml_kernel_type;
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h" 2
# 64 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
static inline float32_t arm_exponent_f32(float32_t x, int32_t nb)
{
    float32_t r = x;
    nb --;
    while(nb > 0)
    {
        r = r * x;
        nb--;
    }
    return(r);
}





typedef struct
{
  uint32_t nbOfSupportVectors;
  uint32_t vectorDimension;
  float32_t intercept;
  const float32_t *dualCoefficients;
  const float32_t *supportVectors;
  const int32_t *classes;
} arm_svm_linear_instance_f32;





typedef struct
{
  uint32_t nbOfSupportVectors;
  uint32_t vectorDimension;
  float32_t intercept;
  const float32_t *dualCoefficients;
  const float32_t *supportVectors;
  const int32_t *classes;
  int32_t degree;
  float32_t coef0;
  float32_t gamma;
} arm_svm_polynomial_instance_f32;





typedef struct
{
  uint32_t nbOfSupportVectors;
  uint32_t vectorDimension;
  float32_t intercept;
  const float32_t *dualCoefficients;
  const float32_t *supportVectors;
  const int32_t *classes;
  float32_t gamma;
} arm_svm_rbf_instance_f32;





typedef struct
{
  uint32_t nbOfSupportVectors;
  uint32_t vectorDimension;
  float32_t intercept;
  const float32_t *dualCoefficients;
  const float32_t *supportVectors;
  const int32_t *classes;
  float32_t coef0;
  float32_t gamma;
} arm_svm_sigmoid_instance_f32;
# 149 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_linear_init_f32(arm_svm_linear_instance_f32 *S,
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors,
  const int32_t *classes);
# 164 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_linear_predict_f32(const arm_svm_linear_instance_f32 *S,
   const float32_t * in,
   int32_t * pResult);
# 182 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_polynomial_init_f32(arm_svm_polynomial_instance_f32 *S,
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors,
  const int32_t *classes,
  int32_t degree,
  float32_t coef0,
  float32_t gamma
  );
# 201 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_polynomial_predict_f32(const arm_svm_polynomial_instance_f32 *S,
   const float32_t * in,
   int32_t * pResult);
# 217 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_rbf_init_f32(arm_svm_rbf_instance_f32 *S,
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors,
  const int32_t *classes,
  float32_t gamma
  );
# 234 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_rbf_predict_f32(const arm_svm_rbf_instance_f32 *S,
   const float32_t * in,
   int32_t * pResult);
# 251 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_sigmoid_init_f32(arm_svm_sigmoid_instance_f32 *S,
  uint32_t nbOfSupportVectors,
  uint32_t vectorDimension,
  float32_t intercept,
  const float32_t *dualCoefficients,
  const float32_t *supportVectors,
  const int32_t *classes,
  float32_t coef0,
  float32_t gamma
  );
# 269 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/svm_functions.h"
void arm_svm_sigmoid_predict_f32(const arm_svm_sigmoid_instance_f32 *S,
   const float32_t * in,
   int32_t * pResult);
# 47 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/fast_math_functions.h" 1
# 48 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h" 1
# 37 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/complex_math_functions.h" 1
# 38 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h" 2
# 110 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const q15_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
  } arm_cfft_radix2_instance_q15;


  arm_status arm_cfft_radix2_init_q15(
        arm_cfft_radix2_instance_q15 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  void arm_cfft_radix2_q15(
  const arm_cfft_radix2_instance_q15 * S,
        q15_t * pSrc);





  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const q15_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
  } arm_cfft_radix4_instance_q15;


  arm_status arm_cfft_radix4_init_q15(
        arm_cfft_radix4_instance_q15 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  void arm_cfft_radix4_q15(
  const arm_cfft_radix4_instance_q15 * S,
        q15_t * pSrc);




  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const q31_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
  } arm_cfft_radix2_instance_q31;


  arm_status arm_cfft_radix2_init_q31(
        arm_cfft_radix2_instance_q31 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  void arm_cfft_radix2_q31(
  const arm_cfft_radix2_instance_q31 * S,
        q31_t * pSrc);




  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const q31_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
  } arm_cfft_radix4_instance_q31;


  void arm_cfft_radix4_q31(
  const arm_cfft_radix4_instance_q31 * S,
        q31_t * pSrc);


  arm_status arm_cfft_radix4_init_q31(
        arm_cfft_radix4_instance_q31 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);




  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const float32_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
          float32_t onebyfftLen;
  } arm_cfft_radix2_instance_f32;



  arm_status arm_cfft_radix2_init_f32(
        arm_cfft_radix2_instance_f32 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  void arm_cfft_radix2_f32(
  const arm_cfft_radix2_instance_f32 * S,
        float32_t * pSrc);




  typedef struct
  {
          uint16_t fftLen;
          uint8_t ifftFlag;
          uint8_t bitReverseFlag;
    const float32_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t twidCoefModifier;
          uint16_t bitRevFactor;
          float32_t onebyfftLen;
  } arm_cfft_radix4_instance_f32;




  arm_status arm_cfft_radix4_init_f32(
        arm_cfft_radix4_instance_f32 * S,
        uint16_t fftLen,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);


  void arm_cfft_radix4_f32(
  const arm_cfft_radix4_instance_f32 * S,
        float32_t * pSrc);
# 282 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint16_t fftLen;
    const q15_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t bitRevLength;
# 296 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  } arm_cfft_instance_q15;


arm_status arm_cfft_init_4096_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_2048_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_1024_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_512_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_256_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_128_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_64_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_32_q15(arm_cfft_instance_q15 * S);
arm_status arm_cfft_init_16_q15(arm_cfft_instance_q15 * S);

arm_status arm_cfft_init_q15(
  arm_cfft_instance_q15 * S,
  uint16_t fftLen);
# 327 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
void arm_cfft_q15(
    const arm_cfft_instance_q15 * S,
          q15_t * p1,
          uint8_t ifftFlag,
          uint8_t bitReverseFlag);
# 347 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint16_t fftLen;
    const q31_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t bitRevLength;
# 361 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  } arm_cfft_instance_q31;


arm_status arm_cfft_init_4096_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_2048_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_1024_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_512_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_256_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_128_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_64_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_32_q31(arm_cfft_instance_q31 * S);
arm_status arm_cfft_init_16_q31(arm_cfft_instance_q31 * S);

arm_status arm_cfft_init_q31(
  arm_cfft_instance_q31 * S,
  uint16_t fftLen);
# 390 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
void arm_cfft_q31(
    const arm_cfft_instance_q31 * S,
          q31_t * p1,
          uint8_t ifftFlag,
          uint8_t bitReverseFlag);
# 410 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint16_t fftLen;
    const float32_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t bitRevLength;
# 424 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  } arm_cfft_instance_f32;



arm_status arm_cfft_init_4096_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_2048_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_1024_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_512_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_256_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_128_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_64_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_32_f32(arm_cfft_instance_f32 * S);
arm_status arm_cfft_init_16_f32(arm_cfft_instance_f32 * S);

  arm_status arm_cfft_init_f32(
  arm_cfft_instance_f32 * S,
  uint16_t fftLen);
# 456 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  void arm_cfft_f32(
  const arm_cfft_instance_f32 * S,
        float32_t * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);






  typedef struct
  {
          uint16_t fftLen;
    const float64_t *pTwiddle;
    const uint16_t *pBitRevTable;
          uint16_t bitRevLength;
  } arm_cfft_instance_f64;

arm_status arm_cfft_init_4096_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_2048_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_1024_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_512_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_256_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_128_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_64_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_32_f64(arm_cfft_instance_f64 * S);
arm_status arm_cfft_init_16_f64(arm_cfft_instance_f64 * S);

  arm_status arm_cfft_init_f64(
  arm_cfft_instance_f64 * S,
  uint16_t fftLen);

  void arm_cfft_f64(
  const arm_cfft_instance_f64 * S,
        float64_t * p1,
        uint8_t ifftFlag,
        uint8_t bitReverseFlag);
# 508 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint32_t fftLenReal;
          uint8_t ifftFlagR;
          uint8_t bitReverseFlagR;
          uint32_t twidCoefRModifier;
    const q15_t *pTwiddleAReal;
    const q15_t *pTwiddleBReal;



    const arm_cfft_instance_q15 *pCfft;

  } arm_rfft_instance_q15;
# 566 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
arm_status arm_rfft_init_32_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_64_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_128_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_256_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_512_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_1024_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_2048_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_4096_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

arm_status arm_rfft_init_8192_q15(
        arm_rfft_instance_q15 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_q15(
        arm_rfft_instance_q15 * S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  void arm_rfft_q15(
  const arm_rfft_instance_q15 * S,
        q15_t * pSrc,
        q15_t * pDst);
# 636 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  typedef struct
  {
          uint32_t fftLenReal;
          uint8_t ifftFlagR;
          uint8_t bitReverseFlagR;
          uint32_t twidCoefRModifier;
    const q31_t *pTwiddleAReal;
    const q31_t *pTwiddleBReal;



    const arm_cfft_instance_q31 *pCfft;

  } arm_rfft_instance_q31;
# 695 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
    arm_status arm_rfft_init_32_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_64_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_128_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_256_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_512_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_1024_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_2048_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_4096_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_8192_q31(
        arm_rfft_instance_q31 * S,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  arm_status arm_rfft_init_q31(
        arm_rfft_instance_q31 * S,
        uint32_t fftLenReal,
        uint32_t ifftFlagR,
        uint32_t bitReverseFlag);

  void arm_rfft_q31(
  const arm_rfft_instance_q31 * S,
        q31_t * pSrc,
        q31_t * pDst);





  typedef struct
  {
          uint32_t fftLenReal;
          uint16_t fftLenBy2;
          uint8_t ifftFlagR;
          uint8_t bitReverseFlagR;
          uint32_t twidCoefRModifier;
    const float32_t *pTwiddleAReal;
    const float32_t *pTwiddleBReal;
          arm_cfft_radix4_instance_f32 *pCfft;
  } arm_rfft_instance_f32;




typedef struct
  {
          arm_cfft_instance_f64 Sint;
          uint16_t fftLenRFFT;
    const float64_t * pTwiddleRFFT;
  } arm_rfft_fast_instance_f64 ;

arm_status arm_rfft_fast_init_32_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_64_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_128_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_256_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_512_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_1024_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_2048_f64( arm_rfft_fast_instance_f64 * S );
arm_status arm_rfft_fast_init_4096_f64( arm_rfft_fast_instance_f64 * S );

arm_status arm_rfft_fast_init_f64 (
         arm_rfft_fast_instance_f64 * S,
         uint16_t fftLen);


void arm_rfft_fast_f64(
    arm_rfft_fast_instance_f64 * S,
    float64_t * p, float64_t * pOut,
    uint8_t ifftFlag);
# 813 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
typedef struct
  {
          arm_cfft_instance_f32 Sint;
          uint16_t fftLenRFFT;
    const float32_t * pTwiddleRFFT;
  } arm_rfft_fast_instance_f32 ;


arm_status arm_rfft_fast_init_32_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_64_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_128_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_256_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_512_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_1024_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_2048_f32( arm_rfft_fast_instance_f32 * S );
arm_status arm_rfft_fast_init_4096_f32( arm_rfft_fast_instance_f32 * S );


arm_status arm_rfft_fast_init_f32 (
         arm_rfft_fast_instance_f32 * S,
         uint16_t fftLen);
# 846 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  void arm_rfft_fast_f32(
        const arm_rfft_fast_instance_f32 * S,
        float32_t * p, float32_t * pOut,
        uint8_t ifftFlag);






typedef struct
  {
     const float32_t *dctCoefs;
     const float32_t *filterCoefs;
     const float32_t *windowCoefs;
     const uint32_t *filterPos;
     const uint32_t *filterLengths;
     uint32_t fftLen;
     uint32_t nbMelFilters;
     uint32_t nbDctOutputs;





     arm_rfft_fast_instance_f32 rfft;

  } arm_mfcc_instance_f32 ;

arm_status arm_mfcc_init_32_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_64_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_128_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_256_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_512_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_1024_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_2048_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_4096_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );

arm_status arm_mfcc_init_f32(
  arm_mfcc_instance_f32 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const float32_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const float32_t *filterCoefs,
  const float32_t *windowCoefs
  );
# 992 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  void arm_mfcc_f32(
  const arm_mfcc_instance_f32 * S,
  float32_t *pSrc,
  float32_t *pDst,
  float32_t *pTmp
  );





typedef struct
  {
     const q31_t *dctCoefs;
     const q31_t *filterCoefs;
     const q31_t *windowCoefs;
     const uint32_t *filterPos;
     const uint32_t *filterLengths;
     uint32_t fftLen;
     uint32_t nbMelFilters;
     uint32_t nbDctOutputs;





     arm_rfft_instance_q31 rfft;

  } arm_mfcc_instance_q31 ;

arm_status arm_mfcc_init_32_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_64_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_128_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_256_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_512_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_1024_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_2048_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_4096_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );

arm_status arm_mfcc_init_q31(
  arm_mfcc_instance_q31 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q31_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q31_t *filterCoefs,
  const q31_t *windowCoefs
  );
# 1140 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  arm_status arm_mfcc_q31(
  const arm_mfcc_instance_q31 * S,
  q31_t *pSrc,
  q31_t *pDst,
  q31_t *pTmp
  );





typedef struct
  {
     const q15_t *dctCoefs;
     const q15_t *filterCoefs;
     const q15_t *windowCoefs;
     const uint32_t *filterPos;
     const uint32_t *filterLengths;
     uint32_t fftLen;
     uint32_t nbMelFilters;
     uint32_t nbDctOutputs;





     arm_rfft_instance_q15 rfft;

  } arm_mfcc_instance_q15 ;

arm_status arm_mfcc_init_32_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_64_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_128_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_256_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_512_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_1024_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_2048_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_4096_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );

arm_status arm_mfcc_init_q15(
  arm_mfcc_instance_q15 * S,
  uint32_t fftLen,
  uint32_t nbMelFilters,
  uint32_t nbDctOutputs,
  const q15_t *dctCoefs,
  const uint32_t *filterPos,
  const uint32_t *filterLengths,
  const q15_t *filterCoefs,
  const q15_t *windowCoefs
  );
# 1288 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
  arm_status arm_mfcc_q15(
  const arm_mfcc_instance_q15 * S,
  q15_t *pSrc,
  q15_t *pDst,
  q31_t *pTmp
  );
# 1307 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_cfft_tmp_buffer_size(arm_math_target_arch arch,
                                         arm_math_datatype dt,
                                         uint32_t nb_samples,
                                         uint32_t buf_id);
# 1322 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_cfft_output_buffer_size(arm_math_target_arch arch,
                                            arm_math_datatype dt,
                                            uint32_t nb_samples);
# 1336 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_cifft_output_buffer_size(arm_math_target_arch arch,
                                             arm_math_datatype dt,
                                             uint32_t nb_samples);
# 1351 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_rfft_tmp_buffer_size(arm_math_target_arch arch,
                                         arm_math_datatype dt,
                                         uint32_t nb_samples,
                                         uint32_t buf_id);
# 1366 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_rfft_output_buffer_size(arm_math_target_arch arch,
                                            arm_math_datatype dt,
                                            uint32_t nb_samples);
# 1382 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_rifft_input_buffer_size(arm_math_target_arch arch,
                                            arm_math_datatype dt,
                                            uint32_t nb_samples);
# 1398 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/transform_functions.h"
extern int32_t arm_mfcc_tmp_buffer_size(arm_math_target_arch arch,
                                         arm_math_datatype dt,
                                         uint32_t nb_samples,
                                         uint32_t buf_id,
                                         uint32_t use_cfft);
# 49 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h" 1
# 36 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/support_functions.h" 1
# 37 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h" 2
# 56 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  typedef struct
  {
          uint16_t numTaps;
          q7_t *pState;
    const q7_t *pCoeffs;
  } arm_fir_instance_q7;




  typedef struct
  {
          uint16_t numTaps;
          q15_t *pState;
    const q15_t *pCoeffs;
  } arm_fir_instance_q15;




  typedef struct
  {
          uint16_t numTaps;
          q31_t *pState;
    const q31_t *pCoeffs;
  } arm_fir_instance_q31;




  typedef struct
  {
          uint16_t numTaps;
          float32_t *pState;
    const float32_t *pCoeffs;
  } arm_fir_instance_f32;




  typedef struct
  {
          uint16_t numTaps;
          float64_t *pState;
    const float64_t *pCoeffs;
  } arm_fir_instance_f64;
# 110 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_q7(
  const arm_fir_instance_q7 * S,
  const q7_t * pSrc,
        q7_t * pDst,
        uint32_t blockSize);
# 127 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_init_q7(
        arm_fir_instance_q7 * S,
        uint16_t numTaps,
  const q7_t * pCoeffs,
        q7_t * pState,
        uint32_t blockSize);
# 141 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_q15(
  const arm_fir_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 154 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_fast_q15(
  const arm_fir_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 175 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_init_q15(
        arm_fir_instance_q15 * S,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);
# 189 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_q31(
  const arm_fir_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 202 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_fast_q31(
  const arm_fir_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 219 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_init_q31(
        arm_fir_instance_q31 * S,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);
# 233 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_f32(
  const arm_fir_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 246 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_f64(
  const arm_fir_instance_f64 * S,
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);
# 260 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_init_f32(
        arm_fir_instance_f32 * S,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);
# 275 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_init_f64(
        arm_fir_instance_f64 * S,
        uint16_t numTaps,
  const float64_t * pCoeffs,
        float64_t * pState,
        uint32_t blockSize);




  typedef struct
  {
          int8_t numStages;
          q15_t *pState;
    const q15_t *pCoeffs;
          int8_t postShift;
  } arm_biquad_casd_df1_inst_q15;




  typedef struct
  {
          uint32_t numStages;
          q31_t *pState;
    const q31_t *pCoeffs;
          uint8_t postShift;
  } arm_biquad_casd_df1_inst_q31;




  typedef struct
  {
          uint32_t numStages;
          float32_t *pState;
    const float32_t *pCoeffs;
  } arm_biquad_casd_df1_inst_f32;
# 331 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 345 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_init_q15(
        arm_biquad_casd_df1_inst_q15 * S,
        uint8_t numStages,
  const q15_t * pCoeffs,
        q15_t * pState,
        int8_t postShift);
# 359 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_fast_q15(
  const arm_biquad_casd_df1_inst_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 372 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 385 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_fast_q31(
  const arm_biquad_casd_df1_inst_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 399 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_init_q31(
        arm_biquad_casd_df1_inst_q31 * S,
        uint8_t numStages,
  const q31_t * pCoeffs,
        q31_t * pState,
        int8_t postShift);
# 413 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_f32(
  const arm_biquad_casd_df1_inst_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 436 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df1_init_f32(
        arm_biquad_casd_df1_inst_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);
# 451 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst);
# 469 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 487 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);
# 503 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);
# 521 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 539 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);
# 555 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);
# 573 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 591 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_conv_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst);
# 610 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);
# 633 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 656 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);
# 677 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);
# 700 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 723 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);
# 744 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);
# 767 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 790 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_conv_partial_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        uint32_t firstIndex,
        uint32_t numPoints);





  typedef struct
  {
          uint8_t M;
          uint16_t numTaps;
    const q15_t *pCoeffs;
          q15_t *pState;
  } arm_fir_decimate_instance_q15;




  typedef struct
  {
          uint8_t M;
          uint16_t numTaps;
    const q31_t *pCoeffs;
          q31_t *pState;
  } arm_fir_decimate_instance_q31;




typedef struct
  {
          uint8_t M;
          uint16_t numTaps;
    const float32_t *pCoeffs;
          float32_t *pState;
  } arm_fir_decimate_instance_f32;




  typedef struct
  {
    uint8_t M;
    uint16_t numTaps;
    const float64_t *pCoeffs;
    float64_t *pState;
  } arm_fir_decimate_instance_f64;
# 851 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_decimate_f64(
      const arm_fir_decimate_instance_f64 * S,
      const float64_t * pSrc,
      float64_t * pDst,
      uint32_t blockSize);
# 870 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_decimate_init_f64(
      arm_fir_decimate_instance_f64 * S,
      uint16_t numTaps,
      uint8_t M,
      const float64_t * pCoeffs,
      float64_t * pState,
      uint32_t blockSize);
# 886 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_fir_decimate_f32(
  const arm_fir_decimate_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 905 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
arm_status arm_fir_decimate_init_f32(
        arm_fir_decimate_instance_f32 * S,
        uint16_t numTaps,
        uint8_t M,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);
# 921 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_decimate_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 935 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_decimate_fast_q15(
  const arm_fir_decimate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 953 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_decimate_init_q15(
        arm_fir_decimate_instance_q15 * S,
        uint16_t numTaps,
        uint8_t M,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);
# 969 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_decimate_q31(
  const arm_fir_decimate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 982 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_decimate_fast_q31(
  const arm_fir_decimate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 1000 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_decimate_init_q31(
        arm_fir_decimate_instance_q31 * S,
        uint16_t numTaps,
        uint8_t M,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);





  typedef struct
  {
        uint8_t L;
        uint16_t phaseLength;
  const q15_t *pCoeffs;
        q15_t *pState;
  } arm_fir_interpolate_instance_q15;




  typedef struct
  {
        uint8_t L;
        uint16_t phaseLength;
  const q31_t *pCoeffs;
        q31_t *pState;
  } arm_fir_interpolate_instance_q31;




  typedef struct
  {
        uint8_t L;
        uint16_t phaseLength;
  const float32_t *pCoeffs;
        float32_t *pState;
  } arm_fir_interpolate_instance_f32;
# 1050 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_interpolate_q15(
  const arm_fir_interpolate_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 1068 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_interpolate_init_q15(
        arm_fir_interpolate_instance_q15 * S,
        uint8_t L,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        uint32_t blockSize);
# 1084 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_interpolate_q31(
  const arm_fir_interpolate_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 1102 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_interpolate_init_q31(
        arm_fir_interpolate_instance_q31 * S,
        uint8_t L,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        uint32_t blockSize);
# 1118 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_interpolate_f32(
  const arm_fir_interpolate_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 1136 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  arm_status arm_fir_interpolate_init_f32(
        arm_fir_interpolate_instance_f32 * S,
        uint8_t L,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        uint32_t blockSize);





  typedef struct
  {
          uint8_t numStages;
          q63_t *pState;
    const q31_t *pCoeffs;
          uint8_t postShift;
  } arm_biquad_cas_df1_32x64_ins_q31;
# 1163 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cas_df1_32x64_q31(
  const arm_biquad_cas_df1_32x64_ins_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 1177 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cas_df1_32x64_init_q31(
        arm_biquad_cas_df1_32x64_ins_q31 * S,
        uint8_t numStages,
  const q31_t * pCoeffs,
        q63_t * pState,
        uint8_t postShift);





  typedef struct
  {
          uint8_t numStages;
          float32_t *pState;
    const float32_t *pCoeffs;
  } arm_biquad_cascade_df2T_instance_f32;




  typedef struct
  {
          uint8_t numStages;
          float32_t *pState;
    const float32_t *pCoeffs;
  } arm_biquad_cascade_stereo_df2T_instance_f32;




  typedef struct
  {
          uint8_t numStages;
          float64_t *pState;
    const float64_t *pCoeffs;
  } arm_biquad_cascade_df2T_instance_f64;
# 1223 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df2T_f32(
  const arm_biquad_cascade_df2T_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 1237 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_stereo_df2T_f32(
  const arm_biquad_cascade_stereo_df2T_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 1251 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df2T_f64(
  const arm_biquad_cascade_df2T_instance_f64 * S,
  const float64_t * pSrc,
        float64_t * pDst,
        uint32_t blockSize);
# 1277 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df2T_init_f32(
        arm_biquad_cascade_df2T_instance_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);
# 1291 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_stereo_df2T_init_f32(
        arm_biquad_cascade_stereo_df2T_instance_f32 * S,
        uint8_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);
# 1305 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_biquad_cascade_df2T_init_f64(
        arm_biquad_cascade_df2T_instance_f64 * S,
        uint8_t numStages,
        const float64_t * pCoeffs,
        float64_t * pState);





  typedef struct
  {
          uint16_t numStages;
          q15_t *pState;
    const q15_t *pCoeffs;
  } arm_fir_lattice_instance_q15;




  typedef struct
  {
          uint16_t numStages;
          q31_t *pState;
    const q31_t *pCoeffs;
  } arm_fir_lattice_instance_q31;




  typedef struct
  {
          uint16_t numStages;
          float32_t *pState;
    const float32_t *pCoeffs;
  } arm_fir_lattice_instance_f32;
# 1350 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_init_q15(
        arm_fir_lattice_instance_q15 * S,
        uint16_t numStages,
  const q15_t * pCoeffs,
        q15_t * pState);
# 1364 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_q15(
  const arm_fir_lattice_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 1378 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_init_q31(
        arm_fir_lattice_instance_q31 * S,
        uint16_t numStages,
  const q31_t * pCoeffs,
        q31_t * pState);
# 1392 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_q31(
  const arm_fir_lattice_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 1406 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_init_f32(
        arm_fir_lattice_instance_f32 * S,
        uint16_t numStages,
  const float32_t * pCoeffs,
        float32_t * pState);
# 1420 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_lattice_f32(
  const arm_fir_lattice_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);





  typedef struct
  {
          uint16_t numStages;
          q15_t *pState;
          q15_t *pkCoeffs;
          q15_t *pvCoeffs;
  } arm_iir_lattice_instance_q15;




  typedef struct
  {
          uint16_t numStages;
          q31_t *pState;
          q31_t *pkCoeffs;
          q31_t *pvCoeffs;
  } arm_iir_lattice_instance_q31;




  typedef struct
  {
          uint16_t numStages;
          float32_t *pState;
          float32_t *pkCoeffs;
          float32_t *pvCoeffs;
  } arm_iir_lattice_instance_f32;
# 1468 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_f32(
  const arm_iir_lattice_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        uint32_t blockSize);
# 1484 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_init_f32(
        arm_iir_lattice_instance_f32 * S,
        uint16_t numStages,
        float32_t * pkCoeffs,
        float32_t * pvCoeffs,
        float32_t * pState,
        uint32_t blockSize);
# 1500 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_q31(
  const arm_iir_lattice_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        uint32_t blockSize);
# 1516 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_init_q31(
        arm_iir_lattice_instance_q31 * S,
        uint16_t numStages,
        q31_t * pkCoeffs,
        q31_t * pvCoeffs,
        q31_t * pState,
        uint32_t blockSize);
# 1532 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_q15(
  const arm_iir_lattice_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        uint32_t blockSize);
# 1548 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_iir_lattice_init_q15(
        arm_iir_lattice_instance_q15 * S,
        uint16_t numStages,
        q15_t * pkCoeffs,
        q15_t * pvCoeffs,
        q15_t * pState,
        uint32_t blockSize);





  typedef struct
  {
          uint16_t numTaps;
          float32_t *pState;
          float32_t *pCoeffs;
          float32_t mu;
  } arm_lms_instance_f32;
# 1578 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_f32(
  const arm_lms_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pRef,
        float32_t * pOut,
        float32_t * pErr,
        uint32_t blockSize);
# 1596 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_init_f32(
        arm_lms_instance_f32 * S,
        uint16_t numTaps,
        float32_t * pCoeffs,
        float32_t * pState,
        float32_t mu,
        uint32_t blockSize);





  typedef struct
  {
          uint16_t numTaps;
          q15_t *pState;
          q15_t *pCoeffs;
          q15_t mu;
          uint32_t postShift;
  } arm_lms_instance_q15;
# 1628 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_init_q15(
        arm_lms_instance_q15 * S,
        uint16_t numTaps,
        q15_t * pCoeffs,
        q15_t * pState,
        q15_t mu,
        uint32_t blockSize,
        uint32_t postShift);
# 1647 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_q15(
  const arm_lms_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pRef,
        q15_t * pOut,
        q15_t * pErr,
        uint32_t blockSize);





  typedef struct
  {
          uint16_t numTaps;
          q31_t *pState;
          q31_t *pCoeffs;
          q31_t mu;
          uint32_t postShift;
  } arm_lms_instance_q31;
# 1678 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_q31(
  const arm_lms_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pRef,
        q31_t * pOut,
        q31_t * pErr,
        uint32_t blockSize);
# 1697 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_init_q31(
        arm_lms_instance_q31 * S,
        uint16_t numTaps,
        q31_t * pCoeffs,
        q31_t * pState,
        q31_t mu,
        uint32_t blockSize,
        uint32_t postShift);





  typedef struct
  {
          uint16_t numTaps;
          float32_t *pState;
          float32_t *pCoeffs;
          float32_t mu;
          float32_t energy;
          float32_t x0;
  } arm_lms_norm_instance_f32;
# 1730 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_f32(
        arm_lms_norm_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pRef,
        float32_t * pOut,
        float32_t * pErr,
        uint32_t blockSize);
# 1748 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_init_f32(
        arm_lms_norm_instance_f32 * S,
        uint16_t numTaps,
        float32_t * pCoeffs,
        float32_t * pState,
        float32_t mu,
        uint32_t blockSize);





  typedef struct
  {
          uint16_t numTaps;
          q31_t *pState;
          q31_t *pCoeffs;
          q31_t mu;
          uint8_t postShift;
    const q31_t *recipTable;
          q31_t energy;
          q31_t x0;
  } arm_lms_norm_instance_q31;
# 1782 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_q31(
        arm_lms_norm_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pRef,
        q31_t * pOut,
        q31_t * pErr,
        uint32_t blockSize);
# 1801 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_init_q31(
        arm_lms_norm_instance_q31 * S,
        uint16_t numTaps,
        q31_t * pCoeffs,
        q31_t * pState,
        q31_t mu,
        uint32_t blockSize,
        uint8_t postShift);





  typedef struct
  {
          uint16_t numTaps;
          q15_t *pState;
          q15_t *pCoeffs;
          q15_t mu;
          uint8_t postShift;
    const q15_t *recipTable;
          q15_t energy;
          q15_t x0;
  } arm_lms_norm_instance_q15;
# 1836 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_q15(
        arm_lms_norm_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pRef,
        q15_t * pOut,
        q15_t * pErr,
        uint32_t blockSize);
# 1855 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_lms_norm_init_q15(
        arm_lms_norm_instance_q15 * S,
        uint16_t numTaps,
        q15_t * pCoeffs,
        q15_t * pState,
        q15_t mu,
        uint32_t blockSize,
        uint8_t postShift);
# 1873 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_f32(
  const float32_t * pSrcA,
        uint32_t srcALen,
  const float32_t * pSrcB,
        uint32_t srcBLen,
        float32_t * pDst);
# 1889 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_f64(
  const float64_t * pSrcA,
        uint32_t srcALen,
  const float64_t * pSrcB,
        uint32_t srcBLen,
        float64_t * pDst);
# 1906 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_correlate_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch);
# 1923 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);
# 1939 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_correlate_fast_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst);
# 1956 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_correlate_fast_opt_q15(
  const q15_t * pSrcA,
        uint32_t srcALen,
  const q15_t * pSrcB,
        uint32_t srcBLen,
        q15_t * pDst,
        q15_t * pScratch);
# 1973 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);
# 1989 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_correlate_fast_q31(
  const q31_t * pSrcA,
        uint32_t srcALen,
  const q31_t * pSrcB,
        uint32_t srcBLen,
        q31_t * pDst);
# 2007 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_opt_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst,
        q15_t * pScratch1,
        q15_t * pScratch2);
# 2025 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_correlate_q7(
  const q7_t * pSrcA,
        uint32_t srcALen,
  const q7_t * pSrcB,
        uint32_t srcBLen,
        q7_t * pDst);





  typedef struct
  {
          uint16_t numTaps;
          uint16_t stateIndex;
          float32_t *pState;
    const float32_t *pCoeffs;
          uint16_t maxDelay;
          int32_t *pTapDelay;
  } arm_fir_sparse_instance_f32;




  typedef struct
  {
          uint16_t numTaps;
          uint16_t stateIndex;
          q31_t *pState;
    const q31_t *pCoeffs;
          uint16_t maxDelay;
          int32_t *pTapDelay;
  } arm_fir_sparse_instance_q31;




  typedef struct
  {
          uint16_t numTaps;
          uint16_t stateIndex;
          q15_t *pState;
    const q15_t *pCoeffs;
          uint16_t maxDelay;
          int32_t *pTapDelay;
  } arm_fir_sparse_instance_q15;




  typedef struct
  {
          uint16_t numTaps;
          uint16_t stateIndex;
          q7_t *pState;
    const q7_t *pCoeffs;
          uint16_t maxDelay;
          int32_t *pTapDelay;
  } arm_fir_sparse_instance_q7;
# 2094 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_f32(
        arm_fir_sparse_instance_f32 * S,
  const float32_t * pSrc,
        float32_t * pDst,
        float32_t * pScratchIn,
        uint32_t blockSize);
# 2112 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_init_f32(
        arm_fir_sparse_instance_f32 * S,
        uint16_t numTaps,
  const float32_t * pCoeffs,
        float32_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);
# 2130 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_q31(
        arm_fir_sparse_instance_q31 * S,
  const q31_t * pSrc,
        q31_t * pDst,
        q31_t * pScratchIn,
        uint32_t blockSize);
# 2148 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_init_q31(
        arm_fir_sparse_instance_q31 * S,
        uint16_t numTaps,
  const q31_t * pCoeffs,
        q31_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);
# 2167 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_q15(
        arm_fir_sparse_instance_q15 * S,
  const q15_t * pSrc,
        q15_t * pDst,
        q15_t * pScratchIn,
        q31_t * pScratchOut,
        uint32_t blockSize);
# 2186 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_init_q15(
        arm_fir_sparse_instance_q15 * S,
        uint16_t numTaps,
  const q15_t * pCoeffs,
        q15_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);
# 2205 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_q7(
        arm_fir_sparse_instance_q7 * S,
  const q7_t * pSrc,
        q7_t * pDst,
        q7_t * pScratchIn,
        q31_t * pScratchOut,
        uint32_t blockSize);
# 2224 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  void arm_fir_sparse_init_q7(
        arm_fir_sparse_instance_q7 * S,
        uint16_t numTaps,
  const q7_t * pCoeffs,
        q7_t * pState,
        int32_t * pTapDelay,
        uint16_t maxDelay,
        uint32_t blockSize);
# 2241 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
  __attribute__((always_inline)) static inline void arm_circularWrite_f32(
  int32_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const int32_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;



    wOffset = *writeOffset;


    i = blockSize;

    while (i > 0U)
    {

      circBuffer[wOffset] = *src;


      src += srcInc;


      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;


      i--;
    }


    *writeOffset = (uint16_t)wOffset;
  }






  __attribute__((always_inline)) static inline void arm_circularRead_f32(
  int32_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  int32_t * dst,
  int32_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t rOffset;
    int32_t* dst_end;



    rOffset = *readOffset;
    dst_end = dst_base + dst_length;


    i = blockSize;

    while (i > 0U)
    {

      *dst = circBuffer[rOffset];


      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }


      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }


      i--;
    }


    *readOffset = rOffset;
  }





  __attribute__((always_inline)) static inline void arm_circularWrite_q15(
  q15_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q15_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;



    wOffset = *writeOffset;


    i = blockSize;

    while (i > 0U)
    {

      circBuffer[wOffset] = *src;


      src += srcInc;


      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;


      i--;
    }


    *writeOffset = (uint16_t)wOffset;
  }





  __attribute__((always_inline)) static inline void arm_circularRead_q15(
  q15_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q15_t * dst,
  q15_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q15_t* dst_end;



    rOffset = *readOffset;

    dst_end = dst_base + dst_length;


    i = blockSize;

    while (i > 0U)
    {

      *dst = circBuffer[rOffset];


      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }


      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }


      i--;
    }


    *readOffset = rOffset;
  }





  __attribute__((always_inline)) static inline void arm_circularWrite_q7(
  q7_t * circBuffer,
  int32_t L,
  uint16_t * writeOffset,
  int32_t bufferInc,
  const q7_t * src,
  int32_t srcInc,
  uint32_t blockSize)
  {
    uint32_t i = 0U;
    int32_t wOffset;



    wOffset = *writeOffset;


    i = blockSize;

    while (i > 0U)
    {

      circBuffer[wOffset] = *src;


      src += srcInc;


      wOffset += bufferInc;
      if (wOffset >= L)
        wOffset -= L;


      i--;
    }


    *writeOffset = (uint16_t)wOffset;
  }





  __attribute__((always_inline)) static inline void arm_circularRead_q7(
  q7_t * circBuffer,
  int32_t L,
  int32_t * readOffset,
  int32_t bufferInc,
  q7_t * dst,
  q7_t * dst_base,
  int32_t dst_length,
  int32_t dstInc,
  uint32_t blockSize)
  {
    uint32_t i = 0;
    int32_t rOffset;
    q7_t* dst_end;



    rOffset = *readOffset;

    dst_end = dst_base + dst_length;


    i = blockSize;

    while (i > 0U)
    {

      *dst = circBuffer[rOffset];


      dst += dstInc;

      if (dst == dst_end)
      {
        dst = dst_base;
      }


      rOffset += bufferInc;

      if (rOffset >= L)
      {
        rOffset -= L;
      }


      i--;
    }


    *readOffset = rOffset;
  }
# 2548 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_levinson_durbin_f32(const float32_t *phi,
  float32_t *a,
  float32_t *err,
  int nbCoefs);
# 2561 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/filtering_functions.h"
void arm_levinson_durbin_q31(const q31_t *phi,
  q31_t *a,
  q31_t *err,
  int nbCoefs);
# 50 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h" 1
# 56 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_norm_f32(const float32_t *pInputQuaternions,
    float32_t *pNorms,
    uint32_t nbQuaternions);
# 67 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_inverse_f32(const float32_t *pInputQuaternions,
    float32_t *pInverseQuaternions,
    uint32_t nbQuaternions);
# 78 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_conjugate_f32(const float32_t *inputQuaternions,
    float32_t *pConjugateQuaternions,
    uint32_t nbQuaternions);
# 89 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_normalize_f32(const float32_t *inputQuaternions,
    float32_t *pNormalizedQuaternions,
    uint32_t nbQuaternions);
# 100 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_product_single_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *r);
# 112 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion_product_f32(const float32_t *qa,
    const float32_t *qb,
    float32_t *r,
    uint32_t nbQuaternions);
# 133 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_quaternion2rotation_f32(const float32_t *pInputQuaternions,
    float32_t *pOutputRotations,
    uint32_t nbQuaternions);
# 144 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/quaternion_math_functions.h"
void arm_rotation2quaternion_f32(const float32_t *pInputRotations,
    float32_t *pOutputQuaternions,
    uint32_t nbQuaternions);
# 51 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 1 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h" 1
# 61 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_welch_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 81 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_welch_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 99 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_bartlett_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 119 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_bartlett_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 137 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hamming_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 157 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hamming_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 175 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hanning_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 195 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hanning_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 213 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 233 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 251 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 271 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 289 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3a_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 309 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3a_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 327 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3b_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 347 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall3b_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 365 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4a_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 385 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4a_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 403 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_blackman_harris_92db_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 423 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_blackman_harris_92db_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 441 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4b_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 461 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4b_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 479 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4c_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 499 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_nuttall4c_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 517 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft90d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 537 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft90d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 555 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft95_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 575 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft95_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 593 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft116d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 613 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft116d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 631 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft144d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 651 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft144d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 669 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft169d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 689 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft169d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 707 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft196d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 727 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft196d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 745 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft223d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 765 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft223d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 783 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft248d_f64(
        float64_t * pDst,
        uint32_t blockSize);
# 803 "Middlewares/CMSIS/CMSIS-DSP/Include/dsp/window_functions.h"
  void arm_hft248d_f32(
        float32_t * pDst,
        uint32_t blockSize);
# 52 "Middlewares/CMSIS/CMSIS-DSP/Include/arm_math.h" 2
# 6 "User/common/inc/share_types.h" 2
# 37 "User/common/inc/share_types.h"
struct THD_s {
  float32_t voltage;
  float32_t current;
};

struct phase_angle_s {
  float32_t voltage;
  float32_t current;
};

struct phase_data_s {
  float32_t rms_voltage;
  float32_t rms_current;;
  float32_t act_pwr;
  float32_t react_pwr;
  float32_t app_pwr;
  float32_t pf;
  struct THD_s thd;
  struct phase_angle_s angle;
};

struct vol_line_s {
  float32_t ab;
  float32_t bc;
  float32_t ca;
};

struct vol_line_coef_s {
  float32_t ab_gain;
  float32_t bc_gain;
  float32_t ca_gain;
  float32_t ab_offset;
  float32_t bc_offset;
  float32_t ca_offset;
};

struct meter_data_s {
  struct phase_data_s phase_data[3U];
  struct vol_line_s vol_line;
  float32_t frequency;
  float64_t energy_Ws;
  int64_t energy_hWh;
};

struct dsp_phase_coef_s {
  float32_t v_coef;
  float32_t i_coef;
  float32_t i_phase_shift;
  float32_t v_offset;
  float32_t i_offset;
};


struct dsp_coef_s {
  struct dsp_phase_coef_s phase_coef[3U];
  struct vol_line_coef_s vll;
};

enum meter_state_e {
  METER_STATE_ERROR = -2,
  METER_STATE_WARNING = -1,
  METER_STATE_START = 0,
  METER_STATE_WAIT_FOR_STARTING_CURRENT,
  METER_STATE_WAIT_FOR_PLL_LOCK,
  METER_STATE_RUNNING_3PHASE,
  METER_STATE_RUNNING_PHASE_A,
  METER_STATE_RUNNING_PHASE_B,
  METER_STATE_RUNNING_PHASE_C,
};
# 21 "User/lib/inc/meter_register.h" 2
# 158 "User/lib/inc/meter_register.h"
void meter_update_registers(const struct meter_data_s *m);





const struct meter_data_s *meter_get_data(void);
# 53 "User/lib/test/test_meter_register.c" 2



# 1 "/usr/lib/gcc/x86_64-linux-gnu/12/include/stdbool.h" 1 3 4
# 57 "User/lib/test/test_meter_register.c" 2





static uint16_t _stub_regs[0x0060];


void mb_set_float(uint16_t addr, float32_t val)
{
    uint32_t bits;
    memcpy(&bits, &val, 4);
    _stub_regs[addr] = (uint16_t)(bits >> 16);
    _stub_regs[addr + 1] = (uint16_t)(bits & 0xFFFF);
}

float32_t mb_get_float(uint16_t addr)
{
    uint32_t bits = ((uint32_t)_stub_regs[addr] << 16) |
                     (uint32_t)_stub_regs[addr + 1];
    float32_t val;
    memcpy(&val, &bits, 4);
    return val;
}


struct mb_data_store *mb_get_data_store(void) { return 
# 83 "User/lib/test/test_meter_register.c" 3 4
                                                      ((void *)0)
# 83 "User/lib/test/test_meter_register.c"
                                                          ; }
void mb_set_coil(uint16_t a, 
# 84 "User/lib/test/test_meter_register.c" 3 4
                            _Bool 
# 84 "User/lib/test/test_meter_register.c"
                                 v) { (void)a; (void)v; }

# 85 "User/lib/test/test_meter_register.c" 3 4
_Bool 
# 85 "User/lib/test/test_meter_register.c"
    mb_get_coil(uint16_t a) { (void)a; return 0; }
void mb_set_discrete_input(uint16_t a, 
# 86 "User/lib/test/test_meter_register.c" 3 4
                                      _Bool 
# 86 "User/lib/test/test_meter_register.c"
                                           v){ (void)a; (void)v; }

# 87 "User/lib/test/test_meter_register.c" 3 4
_Bool 
# 87 "User/lib/test/test_meter_register.c"
    mb_get_discrete_input(uint16_t a) { (void)a; return 0; }
void mb_set_input_reg(uint16_t a, uint16_t v) { (void)a; (void)v; }
uint16_t mb_get_input_reg(uint16_t a) { (void)a; return 0; }
void mb_set_holding_reg(uint16_t a, uint16_t v){ (void)a; (void)v; }
uint16_t mb_get_holding_reg(uint16_t a) { (void)a; return 0; }






static struct meter_data_s make_data(void)
{
    struct meter_data_s m;
    memset(&m, 0, sizeof(m));
    m.frequency = 50.0f;
    m.energy_hWh = 1000;
    m.energy_Ws = 360000.0;

    for (int i = 0; i < 3U; i++) {
        m.phase_data[i].rms_voltage = 230.0f + i * 1.0f;
        m.phase_data[i].rms_current = 10.0f + i * 0.5f;
        m.phase_data[i].act_pwr = 2000.0f + i * 100.0f;
        m.phase_data[i].react_pwr = 500.0f + i * 50.0f;
        m.phase_data[i].app_pwr = 2100.0f + i * 100.0f;
        m.phase_data[i].pf = 0.95f - i * 0.01f;
        m.phase_data[i].thd.voltage = 3.0f + i * 0.5f;
        m.phase_data[i].thd.current = 5.0f + i * 1.0f;
    }
    m.vol_line.ab = 400.0f;
    m.vol_line.bc = 401.0f;
    m.vol_line.ca = 402.0f;
    return m;
}




void setUp(void)
{
    memset(_stub_regs, 0, sizeof(_stub_regs));
}

void tearDown(void) {}





void test_mreg_get_data_returns_non_null(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    do { if ((((meter_get_data())) != 
# 140 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 140 "User/lib/test/test_meter_register.c"
   )) { } else { UnityFail( (((" Expected Non-NULL"))), (UNITY_UINT)(((140)))); } } while (0);
}

void test_mreg_get_data_matches_last_written(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *out = meter_get_data();
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.frequency)), (UNITY_FLOAT)((out->frequency)), (
# 148 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 148 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(148));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_voltage)), (UNITY_FLOAT)((out->phase_data[0].rms_voltage)), (
# 149 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 149 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(149))
                                                            ;
}





void test_mreg_voltage_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0000))), (
# 161 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 161 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(161));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0002))), (
# 162 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 162 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(162));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].rms_voltage)), (UNITY_FLOAT)((mb_get_float(0x0004))), (
# 163 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 163 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(163));
}

void test_mreg_voltage_line_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ab)), (UNITY_FLOAT)((mb_get_float(0x0006))), (
# 170 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 170 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(170));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.bc)), (UNITY_FLOAT)((mb_get_float(0x0008))), (
# 171 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 171 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(171));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ca)), (UNITY_FLOAT)((mb_get_float(0x000A))), (
# 172 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 172 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(172));
}





void test_mreg_current_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].rms_current)), (UNITY_FLOAT)((mb_get_float(0x000C))), (
# 183 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 183 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(183));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].rms_current)), (UNITY_FLOAT)((mb_get_float(0x000E))), (
# 184 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 184 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(184));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].rms_current)), (UNITY_FLOAT)((mb_get_float(0x0010))), (
# 185 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 185 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(185));
}

void test_mreg_neutral_current_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected_in = m.phase_data[0].rms_current
                          + m.phase_data[1].rms_current
                          + m.phase_data[2].rms_current;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected_in)), (UNITY_FLOAT)((mb_get_float(0x0012))), (
# 195 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 195 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(195));
}





void test_mreg_active_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0014))), (
# 206 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 206 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(206));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0016))), (
# 207 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 207 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(207));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].act_pwr)), (UNITY_FLOAT)((mb_get_float(0x0018))), (
# 208 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 208 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(208));
}

void test_mreg_active_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].act_pwr
                       + m.phase_data[1].act_pwr
                       + m.phase_data[2].act_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x001A))), (
# 218 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 218 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(218));
}





void test_mreg_reactive_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x001C))), (
# 229 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 229 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(229));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x001E))), (
# 230 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 230 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(230));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].react_pwr)), (UNITY_FLOAT)((mb_get_float(0x0020))), (
# 231 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 231 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(231));
}

void test_mreg_reactive_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].react_pwr
                       + m.phase_data[1].react_pwr
                       + m.phase_data[2].react_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x0022))), (
# 241 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 241 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(241));
}





void test_mreg_apparent_power_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0024))), (
# 252 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 252 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(252));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0026))), (
# 253 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 253 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(253));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].app_pwr)), (UNITY_FLOAT)((mb_get_float(0x0028))), (
# 254 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 254 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(254));
}

void test_mreg_apparent_power_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].app_pwr
                       + m.phase_data[1].app_pwr
                       + m.phase_data[2].app_pwr;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x002A))), (
# 264 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 264 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(264));
}





void test_mreg_power_factor_phase_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].pf)), (UNITY_FLOAT)((mb_get_float(0x002C))), (
# 275 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 275 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(275));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].pf)), (UNITY_FLOAT)((mb_get_float(0x002E))), (
# 276 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 276 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(276));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].pf)), (UNITY_FLOAT)((mb_get_float(0x0030))), (
# 277 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 277 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(277));
}

void test_mreg_power_factor_total_is_sum(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    float32_t expected = m.phase_data[0].pf
                       + m.phase_data[1].pf
                       + m.phase_data[2].pf;
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((expected)), (UNITY_FLOAT)((mb_get_float(0x0032))), (
# 287 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 287 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(287));
}





void test_mreg_frequency_register(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((50.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
# 298 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 298 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(298));
}

void test_mreg_frequency_boundary_45Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 45.0f;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((45.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
# 306 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 306 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(306));
}

void test_mreg_frequency_boundary_65Hz(void)
{
    struct meter_data_s m = make_data();
    m.frequency = 65.0f;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((65.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
# 314 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 314 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(314));
}





void test_mreg_energy_export_kwh_conversion(void)
{
    struct meter_data_s m = make_data();
    m.energy_hWh = 1000;
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((100.0f)), (UNITY_FLOAT)((mb_get_float(0x0038))), (
# 326 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 326 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(326));
}

void test_mreg_energy_import_is_zero(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x0036))), (
# 333 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 333 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(333));
}

void test_mreg_energy_reactive_not_implemented(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x003C))), (
# 340 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 340 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(340));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((0.0f)), (UNITY_FLOAT)((mb_get_float(0x003A))), (
# 341 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 341 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(341));
}





void test_mreg_thd_voltage_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x003E))), (
# 352 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 352 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(352));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x0040))), (
# 353 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 353 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(353));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].thd.voltage)), (UNITY_FLOAT)((mb_get_float(0x0042))), (
# 354 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 354 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(354));
}

void test_mreg_thd_current_registers(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[0].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0044))), (
# 361 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 361 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(361));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[1].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0046))), (
# 362 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 362 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(362));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[2].thd.current)), (UNITY_FLOAT)((mb_get_float(0x0048))), (
# 363 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 363 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(363));
}





void test_mreg_snapshot_all_fields_preserved(void)
{
    struct meter_data_s m = make_data();
    meter_update_registers(&m);
    const struct meter_data_s *snap = meter_get_data();

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.frequency)), (UNITY_FLOAT)((snap->frequency)), (
# 376 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 376 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(376));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ab)), (UNITY_FLOAT)((snap->vol_line.ab)), (
# 377 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 377 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(377));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.bc)), (UNITY_FLOAT)((snap->vol_line.bc)), (
# 378 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 378 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(378));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.vol_line.ca)), (UNITY_FLOAT)((snap->vol_line.ca)), (
# 379 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 379 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(379));
    UnityAssertEqualNumber((UNITY_INT)((m.energy_hWh)), (UNITY_INT)((snap->energy_hWh)), (
# 380 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 380 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(380), UNITY_DISPLAY_STYLE_INT64);

    for (int i = 0; i < 3U; i++) {
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].rms_voltage)), (UNITY_FLOAT)((snap->phase_data[i].rms_voltage)), (
# 383 "User/lib/test/test_meter_register.c" 3 4
       ((void *)0)
# 383 "User/lib/test/test_meter_register.c"
       ), (UNITY_UINT)(383))
                                                                 ;
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].rms_current)), (UNITY_FLOAT)((snap->phase_data[i].rms_current)), (
# 385 "User/lib/test/test_meter_register.c" 3 4
       ((void *)0)
# 385 "User/lib/test/test_meter_register.c"
       ), (UNITY_UINT)(385))
                                                                 ;
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].act_pwr)), (UNITY_FLOAT)((snap->phase_data[i].act_pwr)), (
# 387 "User/lib/test/test_meter_register.c" 3 4
       ((void *)0)
# 387 "User/lib/test/test_meter_register.c"
       ), (UNITY_UINT)(387))
                                                             ;
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].pf)), (UNITY_FLOAT)((snap->phase_data[i].pf)), (
# 389 "User/lib/test/test_meter_register.c" 3 4
       ((void *)0)
# 389 "User/lib/test/test_meter_register.c"
       ), (UNITY_UINT)(389))
                                                        ;
        UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((m.phase_data[i].thd.voltage)), (UNITY_FLOAT)((snap->phase_data[i].thd.voltage)), (
# 391 "User/lib/test/test_meter_register.c" 3 4
       ((void *)0)
# 391 "User/lib/test/test_meter_register.c"
       ), (UNITY_UINT)(391))
                                                                 ;
    }
}





void test_mreg_overwrite_updates_registers(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;
    m2.phase_data[0].rms_voltage = 240.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((60.0f)), (UNITY_FLOAT)((mb_get_float(0x0034))), (
# 410 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 410 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(410));
    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((240.0f)), (UNITY_FLOAT)((mb_get_float(0x0000))), (
# 411 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 411 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(411));
}

void test_mreg_overwrite_updates_snapshot(void)
{
    struct meter_data_s m1 = make_data();
    struct meter_data_s m2 = make_data();
    m2.frequency = 60.0f;

    meter_update_registers(&m1);
    meter_update_registers(&m2);

    UnityAssertFloatsWithin((UNITY_FLOAT)((0.001f)), (UNITY_FLOAT)((60.0f)), (UNITY_FLOAT)((meter_get_data()->frequency)), (
# 423 "User/lib/test/test_meter_register.c" 3 4
   ((void *)0)
# 423 "User/lib/test/test_meter_register.c"
   ), (UNITY_UINT)(423));
}
