#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "physics.h"


struct Object : public Physics {
    public:
        Object();
        Object(local_t local);
        virtual bool interest(const Object &obj);
        virtual int action(Object &obj);
        virtual int create();
        virtual void destroy();
        using Physics::operator==;
};

#endif//__OBJECT_H__
