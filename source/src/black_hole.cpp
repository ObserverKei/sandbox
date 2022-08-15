#include "black_hole.h"
#include <iostream>

BlackHole::BlackHole()
{
   m_show = VIEW_BLACK_HOLE; 
   m_quality = 1;
}

BlackHole::BlackHole(local_t local) : Object(local)
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

int BlackHole::action(Object &obj)
{
    if (obj.m_local == this->m_local) {
        this->m_quality += obj.m_quality;
        obj.destroy();
    }
    this->m_show = (this->m_quality > 9) ? VIEW_BLACK_HOLE : 
        (this->m_quality + VIEW_ZERO);
    if (obj.m_type == this->m_type) {
        //std::cout << "good" << std::endl;
    }

    return 0;
}

