#include "sandbox.h"
#include <iostream>
#include <pthread.h>
#include "black_hole.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>
#include "timer.h"

typedef struct sandbox_st {
    void *data;
} sandbox_t;

enum {
    PTHREAD_VIEW = 0,
    PTHREAD_MAX
};

static pthread_t s_tid[PTHREAD_MAX] = {0};
FILE *g_log_fp = NULL;
char g_debug_enable = 0;

static bool s_running_enable = true;
static sandbox_t s_sandbox = {0};
static Space s_space; 

void set_running(bool enable)
{
	s_running_enable = enable;
}

bool still_running(void)
{
    return s_running_enable;
}

Space *get_space(void)
{
    return &s_space;
}

static void *view(void *arg)
{
    (void)arg;
    while (still_running())
        s_space.draw_view();
    return NULL;
}

void rand_black_hole(void)
{
    Space *space = get_space();
    static uint32_t r = 0;
    local_t local;

    srand(++r);
    local.m_x = rand()%(SPACE_MAP_X);
    local.m_x = (local.m_x > 0) ? (local.m_x - 1) : local.m_x;
    srand(++r);
    local.m_y = rand()%(SPACE_MAP_Y);
    local.m_y = (local.m_y > 0) ? (local.m_y - 1) : local.m_y;

    Object &obj = *space->m_space[local.m_y][local.m_x];

    if (obj.m_type == OBJECT_DEFAULT) {
		BlackHole *bh = new BlackHole(space, local);
        space->set_object(bh);
    }

}

int sandbox_init(void)
{
    g_log_fp = fopen("./sandbox.log", "w");
    if (!g_log_fp) {
        std::cout << "fail to open log\n";
        return -1;
    }
    
    Space *space = get_space();
    dmsg("space:%p", space);
    assert(space != NULL);
	BlackHole *bh = NULL;
	int ret = 0;
	bh = new BlackHole(space, local_t(1, 3));
    ret = space->set_object(bh);
	if (ret)
		delete bh;
	bh = new BlackHole(space, local_t(25, 15));
    ret = space->set_object(bh);
	if (ret)
		delete bh;

    timer_init();
	

    pthread_create(&s_tid[PTHREAD_VIEW], NULL, view, &s_sandbox);
    add_unit_timer(s_space.fflash_fps);

	for (size_t i = 0; i < 100; ++i) {
        add_unit_timer(rand_black_hole);
    }

    return 0;
}

void sandbox_exit(void)
{
    pthread_join(s_tid[PTHREAD_VIEW], NULL);
    timer_exit();
	if (g_log_fp) {
		fclose(g_log_fp);
		g_log_fp = NULL;
	}
		
    return;
}

struct time_st {
    time_st();
    enum limit_et {
        DEEP = 3,
    };
    size_t inc(size_t val[], size_t deep);
    size_t m_trick[DEEP];
    size_t m_min, m_mid, m_max;
    time_st &operator++();
};

size_t time_st::inc(size_t val[], size_t deep)
{
    if (val[deep] == -1ULL){
        val[deep] = 0;
        if (deep < DEEP)
            return inc(val, deep + 1);
        else 
            return val[deep] = 0;
    } else {
        ++val[deep];
        return 0;
    }
}

time_st::time_st() : m_trick(), m_min(0), m_mid(0), m_max(0)
{
}

time_st &time_st::operator++()
{
    inc(m_trick, 0);
    return *this;
}

int sandbox_exec(void)
{
    while (still_running()) {		
        for (auto iter = s_space.begin(); iter != s_space.end(); ++iter) {

			timer_runing();

            Object &obj = *iter;
            if (!obj.m_quality)
                continue;
            if (obj.m_type == OBJECT_DEFAULT)
                continue;

            for (auto other = s_space.begin(); other != s_space.end(); ++other) {
                Object &other_obj = *other;

				if (!obj.m_quality)
					break;
				
                if (other_obj.m_type == OBJECT_DEFAULT)
                    continue;

                if (!other_obj.m_quality) {
                    continue;
                }
                if (other_obj == obj) {
                    continue;
                }

                if (obj.interest(other_obj)) {
                    obj.action(other_obj);
                }
            }

        }
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
