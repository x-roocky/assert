/*
 * Copyright (c) 2021, Roocky <wangxy@roocky.com>
 * All rights reserved. 
 *
 */

/**
 * @brief 配置打开`1`或关闭`0`断言功能，默认等同于`NDEBUG`
 * 
 */
#ifndef ASSERT_CONFIG_ENABLE
#ifdef NDEBUG
#define ASSERT_CONFIG_ENABLE        0
#else /* !NDEBUG */
#define ASSERT_CONFIG_ENABLE        1
#endif /* !NDEBUG */
#endif /* ASSERT_CONFIG_ENABLE */

/**
 * @brief 配置断言格式化输出宏，默认`fprintf(stderr, ...)`
 * 
 */
#ifndef ASSERT_CONFIG_PRINTF
#include <stdio.h>
#define ASSERT_CONFIG_PRINTF(...)   fprintf(stderr, __VA_ARGS__)
#endif /* ASSERT_CONFIG_PRINTF */

/**
 * @brief 配置断言异常终止宏，默认`abort()`
 * 
 */
#ifndef ASSERT_CONFIG_ABORT
#include <stdlib.h>
#define ASSERT_CONFIG_ABORT()       ((void)abort())
#endif /* ASSERT_CONFIG_ABORT */

/**
 * @brief 定义断言信息记述宏，可重定义实现不同格式或介质记述
 * 
 */
#ifndef ASSERT_CONFIG_TRACE
#define ASSERT_CONFIG_TRACE(_prompt, ...)   do {                    \
    ASSERT_CONFIG_PRINTF("Assertion failed (%s) at <%s:%d:%s>: \"", \
                         _prompt, __FILE__, __LINE__, __func__);    \
    ASSERT_CONFIG_PRINTF(__VA_ARGS__);                              \
    ASSERT_CONFIG_PRINTF("\"\r\n");                                 \
} while (0)
#endif /* ASSERT_CONFIG_TRACE */

/**
 * @brief 定义断言检测宏，可重定义实现不同的检测流程
 * 
 */
#ifndef ASSERT_CONFIG_CHECK
#if ASSERT_CONFIG_ENABLE == 0
#define ASSERT_CONFIG_CHECK(...)    ((void)0)
#else /* ASSERT_CONFIG_ENABLE != 0 */
#define ASSERT_CONFIG_CHECK(_e, ...)     do {                       \
    if (!(_e)) {                                                    \
        ASSERT_CONFIG_TRACE(#_e, __VA_ARGS__);                      \
        ASSERT_CONFIG_ABORT();                                      \
    }                                                               \
} while (0)
#endif /* ASSERT_CONFIG_ENABLE != 0 */
#endif /* ASSERT_CONFIG_CHECK */

/**
 * @brief 扩展assert。既兼容标准assert，又支持格式化输出
 * 
 */
#undef __x_assert_1
#undef __x_assert_n
#undef assert
#define __x_assert_1(e)         ASSERT_CONFIG_CHECK(e, "No message")
#define __x_assert_n(e, ...)    ASSERT_CONFIG_CHECK(e, __VA_ARGS__)
#define assert(...)             __X_ASSERT_O1(__x_assert_1, __x_assert_n, __VA_ARGS__)

/**
 * @brief 内部定义，外部禁用，用于实现根据不同数量参数的宏重载
 * 
 */
#ifndef __X_ASSERT_H__
#define __X_ASSERT_H__

#define __X_ASSERT_Sn(                                                      \
    _01, _02, _03, _04, _05, _06, _07, _08, _09, _10, _11, _12,             \
    _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24,             \
    _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36,             \
    _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48,             \
    _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60,             \
    _61, _62, _63, _64, _n, ...) _n
#define __X_ASSERT_On(_f1, _f2, _f3, _fn, ...) __X_ASSERT_Sn(__VA_ARGS__,   \
    _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn,             \
    _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn,             \
    _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn,             \
    _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn,             \
    _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn, _fn,             \
    _fn, _f3, _f2, _f1)(__VA_ARGS__)
#define __X_ASSERT_O1(_f1, _fn, ...)    __X_ASSERT_On(_f1, _fn, _fn, _fn, __VA_ARGS__)
/* #define __X_ASSERT_O2(_f2, _fn, ...)    __X_ASSERT_On(_f2, _f2, _fn, _fn, __VA_ARGS__) */
/* #define __X_ASSERT_O3(_f3, _fn, ...)    __X_ASSERT_On(_f3, _f3, _f3, _fn, __VA_ARGS__) */

#endif /* __X_ASSERT_H__ */
