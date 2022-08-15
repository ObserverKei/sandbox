#include "object.h"

Object::Object()
{
}

Object::Object(local_t local) : Physics(local)
{
}

int Object::create()
{
    return 0;
}

bool Object::interest(const Object &obj)
{
    return false;
}

int Object::action(Object &obj)
{
    return 0;
}

void Object::destroy()
{
    
}
