#include "black_hole.h"
#include <iostream>

BlackHole::BlackHole(Space *space, local_t local) : Object(local), m_space(space)
{
    m_show = VIEW_BLACK_HOLE;
    m_quality = 1;
}


bool BlackHole::interest(const Object &obj)
{
    if (!obj.m_quality)
        return false;

    return true;
}

void BlackHole::destroy()
{
    dmsg("kill black hole (%zu, %zu)", m_local.m_x, m_local.m_y);
    m_space->del_object(this->m_local);
}

int BlackHole::action(Object &obj)
{
    local_t obj_old_local = obj.m_local;
    if (obj.m_local.m_x > this->m_local.m_x) {
        dmsg("> obj x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        --obj.m_local.m_x;
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    } else if (obj.m_local.m_x < this->m_local.m_x) {
        dmsg("< obj == x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        ++obj.m_local.m_x;
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    } else {
        dmsg("obj == x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    } 

    if (obj.m_type == this->m_type) {
        //std::cout << "good" << std::endl;
    }
    dmsg("obj(%zu, %zu) %c", obj.m_local.m_x, obj.m_local.m_y, obj.m_show);

    if (obj.m_local == this->m_local) {
        dmsg("== obj x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        this->m_quality += obj.m_quality;
        m_space->del_object(obj_old_local);
        ++m_space->m_score;
    } else {
        m_space->mov_object(&obj, obj_old_local);
    }

    this->m_show = (this->m_quality > 9) ? VIEW_BLACK_HOLE : 
        (this->m_quality + VIEW_ZERO);
    dmsg("this(%zu, %zu) %c", this->m_local.m_x, this->m_local.m_y, this->m_show);



    return 0;
}

