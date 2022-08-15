#ifndef __BLACK_HOLE_H__
#define __BLACK_HOLE_H__

#include "sandbox.h"

class BlackHole : public Object {
    public:
        BlackHole();
        BlackHole(local_t local);
        bool interest(const Object &obj);
        int action(Object &obj);
        using Object::operator==;
        
    private:
        size_t m_action_radius;
};

#endif//__BLACK_HOLE_H__
