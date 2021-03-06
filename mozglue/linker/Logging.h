/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef Logging_h
#define Logging_h

#ifdef ANDROID
#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_ERROR, "GeckoLinker", __VA_ARGS__)
#else
#include <cstdio>

/* Expand to 1 or m depending on whether there is one argument or more
 * given. */
#define MOZ_ONE_OR_MORE_ARGS_IMPL2(_1, _2, _3, _4, _5, _6, _7, _8, _9, N, ...) \
  N
#define MOZ_ONE_OR_MORE_ARGS_IMPL(args) MOZ_ONE_OR_MORE_ARGS_IMPL2 args
#define MOZ_ONE_OR_MORE_ARGS(...) \
  MOZ_ONE_OR_MORE_ARGS_IMPL((__VA_ARGS__, m, m, m, m, m, m, m, m, 1, 0))

#define MOZ_MACRO_GLUE(a, b) a b
#define MOZ_CONCAT2(a, b) a ## b
#define MOZ_CONCAT1(a, b) MOZ_CONCAT2(a, b)
#define MOZ_CONCAT(a, b) MOZ_CONCAT1(a, b)

/* Some magic to choose between LOG1 and LOGm depending on the number of
 * arguments */
#define MOZ_CHOOSE_LOG(...) \
  MOZ_MACRO_GLUE(MOZ_CONCAT(LOG, MOZ_ONE_OR_MORE_ARGS(__VA_ARGS__)), \
                 (__VA_ARGS__))

#define LOG1(format) fprintf(stderr, format "\n")
#define LOGm(format, ...) fprintf(stderr, format "\n", __VA_ARGS__)
#define LOG(...) MOZ_CHOOSE_LOG(__VA_ARGS__)

#endif

#ifdef MOZ_DEBUG_LINKER
#define DEBUG_LOG LOG
#else
#define DEBUG_LOG(...)
#endif

/* HAVE_64BIT_OS is not defined when building host tools, so use
 * __SIZEOF_POINTER__ */
#if defined(HAVE_64BIT_OS) || __SIZEOF_POINTER__ == 8
#  define PRIxAddr "lx"
#  define PRIxSize "lx"
#  define PRIdSize "ld"
#  define PRIuSize "lu"
#else
#  define PRIxAddr "x"
#  define PRIxSize "x"
#  define PRIdSize "d"
#  define PRIuSize "u"
#endif

#endif /* Logging_h */
