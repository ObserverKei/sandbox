#include "black_hole.h"
#include <iostream>

#define FABS(a, b) (((a) > (b)) ? ((a) - (b)) : ((b) - (a)))

BlackHole::BlackHole(Space *space, local_t local) : Object(local), m_space(space)
{
    m_show = VIEW_BLACK_HOLE;
    m_type = OBJECT_BLACK_HOLE;
    m_quality = 1;
}


bool BlackHole::interest(const Object &obj)
{
    if (!obj.m_quality)
        return false;

    if (m_quality < FABS(obj.m_local.m_x, m_local.m_x) ||
            m_quality < FABS(obj.m_local.m_y, m_local.m_y))
        return false;

    return true;
}

void BlackHole::destroy()
{
    dmsg("kill black hole (%zu, %zu)", m_local.m_x, m_local.m_y);
    m_show = VIEW_EMPTY;
    m_type = OBJECT_DEFAULT;
    m_quality = 0;
}

int BlackHole::action(Object &obj)
{
	if (this->m_quality < obj.m_quality)
		return 0;
	
    if (obj.m_local.m_x > this->m_local.m_x) {
        dmsg("> obj x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        --obj.m_local.m_x;
		/*
		 * this <-+
		 *        |
		 *        +- other
		 */
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
		/*
		 *        +- other
		 *        |
		 * this <-+ 
		 */
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    } else if (obj.m_local.m_x < this->m_local.m_x) {
        dmsg("< obj == x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
        ++obj.m_local.m_x;
		/*
		 *        +-> this
		 *        |
		 * other -+
		 */
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
		/*
		 * other -+
		 *        |
		 *        +-> this
		 */
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    } else {
        dmsg("obj == x:%zu, y:%zu, this x:%zu, y:%zu", 
                obj.m_local.m_x, obj.m_local.m_y,
                this->m_local.m_x, this->m_local.m_y);
		/*
		 * this
		 *  ^  
		 *  |  
		 * other
		 */
        if (obj.m_local.m_y > this->m_local.m_y)
            --obj.m_local.m_y;
		/*
		 * other
		 *  |  
		 *  v 
		 * this
		 */
        else if (obj.m_local.m_y < this->m_local.m_y) 
            ++obj.m_local.m_y;
    }

	/*
	 * this(other)
	 */
	if (this->m_local == obj.m_local) {
		// this eat other
		if ((obj.m_quality + this->m_quality) <= 9)
			this->m_quality += obj.m_quality;
		

		if (this->m_quality <= 9)
			this->m_show = '0' + this->m_quality;
		else
			this->m_show = VIEW_BLACK_HOLE;
		
		obj.destroy();		
		
		++m_space->m_score;
	}

    return 0;
}

