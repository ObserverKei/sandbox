#ifndef __SANDBOX_H__
#define __SANDBOX_H__

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

#include "space.h"

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

extern FILE *g_log_fp;
#define dmsg(fmt, ...) do { \
    fprintf(g_log_fp, "%s %s (%d) " fmt "\n", __FILE__, __FUNCTION__, __LINE__, ##__VA_ARGS__); \
    fflush(g_log_fp); \
} while (0)


bool still_running(void);

#ifdef __cplusplus
}//extern "C"
#endif//__cplusplus

#endif//__SANDBOX_H__
