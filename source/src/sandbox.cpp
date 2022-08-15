#include "sandbox.h"
#include <iostream>
#include <pthread.h>
#include "black_hole.h"
#include <unistd.h>

typedef struct sandbox_st {
    void *data;
} sandbox_t;

enum {
    PTHREAD_VIEW = 0,
    PTHREAD_MAX
};

static pthread_t s_tid[PTHREAD_MAX] = {0};

static sandbox_t s_sandbox = {0};
static Space s_space; 
static bool s_running_enable = true;

bool still_running(void)
{
    return s_running_enable;
}

inline Space *get_space(void)
{
    return &s_space;
}


static void *view(void *arg)
{
    while (still_running())
        s_space.draw_view();
    return NULL;
}


int sandbox_init(void)
{
    Space *space = get_space();
#if 0
    space->set_object(new BlackHole(local_t(5, 5)));
    space->set_object(new BlackHole(local_t(5, 15)));
    space->set_object(new BlackHole(local_t(10, 25)));
    space->set_object(new BlackHole(local_t(15, 35)));
#endif

    pthread_create(&s_tid[PTHREAD_VIEW], NULL, view, &s_sandbox);

    return 0;
}

void sandbox_exit(void)
{
    pthread_join(s_tid[PTHREAD_VIEW], NULL);
    return;
}

int sandbox_exec(void)
{
    local_t local;
    while (still_running()) {
        for (auto iter = s_space.begin(); iter != s_space.end(); ++iter) {
            //std::cout << "++" << std::endl;
            Object &obj = *iter;
            if (!obj.m_quality)
                continue;
            //std::cout << "**" << std::endl;
                    

            for (auto other = s_space.begin(); other != s_space.end(); ++other) {
                Object &other_obj = *other;
                
                if (!other_obj.m_quality)
                    continue;
                //std::cout << "***1" << std::endl;
                if (other_obj == obj)
                    continue;
                std::cerr << "***2" << std::endl;

                if (obj.interest(other_obj)) {
                    std::cout << "---0" << std::endl;
                    obj.action(other_obj);
                    std::cout << "---1" << std::endl;
                }
            }
        }
        
        usleep(1000);
    }

    return 0;
}


int main(int argc, char const* argv[])
{
    sandbox_init();
    sandbox_exec();
    sandbox_exit();

    return 0;
}
