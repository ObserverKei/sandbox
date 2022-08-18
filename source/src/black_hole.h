#ifndef __BLACK_HOLE_H__
#define __BLACK_HOLE_H__

#include "sandbox.h"

class BlackHole : public Object {
    public:
        BlackHole(Space *space, local_t local);
        bool interest(const Object &obj);
        int action(Object &obj);
        void destroy();
        using Object::operator==;
        
    private:
        size_t m_action_radius;
        Space *m_space;
};

#endif//__BLACK_HOLE_H__
