#include "timer.h"
#include <signal.h>
#include <sys/time.h>


#define TIMER_HOOK_MAX (10)

static timer_hook_t timer_hook_list[TIMER_HOOK_MAX] = {0};

void timer_signal_hook(int signo)
{
    if (signo != SIGALRM)
        return;
    
    for (size_t i = 0; i < sizeof(timer_hook_list) / sizeof(timer_hook_list[0]); ++i) {
        if (timer_hook_list[i])
            timer_hook_list[i]();
    }
}

int timer_init(void)
{
    struct itimerval it = {
        .it_interval = { .tv_sec = 1 }, /* 间隔时间 */
        .it_value    = { .tv_sec = 1 }  /* 开始时间 */
    };

    signal(SIGALRM, timer_signal_hook);

    return setitimer(ITIMER_REAL, &it, NULL);
}

int add_unit_timer(timer_hook_t hook)
{
    for (size_t i = 0; i < sizeof(timer_hook_list) / sizeof(timer_hook_list[0]); ++i) {
        if (!timer_hook_list[i]) {
            timer_hook_list[i] = hook;
            return 0;
        }
    }
    return -1;
}

void timer_exit(void)
{
    struct itimerval it = {
        .it_interval = { .tv_sec = 0 }, /* 间隔时间 */
        .it_value    = { .tv_sec = 0 }  /* 开始时间 */
    };

    setitimer(ITIMER_REAL, &it, NULL);
}
