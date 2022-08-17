#ifndef __TIMER_H__
#define __TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#include "stddef.h"

typedef void (*timer_hook_t)(void);

int timer_init(void);
int add_unit_timer(timer_hook_t hook);
void timer_exit(void);

#ifdef __cplusplus
}
#endif//__cplusplus

#endif//__TIMER_H__
