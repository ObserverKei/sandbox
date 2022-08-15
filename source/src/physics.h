#ifndef __PHYSICS_H__
#define __PHYSICS_H__

#include <stdint.h>
#include <stddef.h>

typedef enum object_et {
    OBJECT_DEFAULT = 0,
    OBJECT_BLACK_HOLE 
} object_t;

typedef struct local_st {
    public:
        local_st();
        local_st(const size_t x, const size_t y);
        bool operator==(const local_st &where) const;
        bool operator!=(const local_st &where) const;

    public:
        size_t m_x;
        size_t m_y;
} local_t;


struct Physics {
    public:
        Physics();
        Physics(local_t local);
        Physics(const Physics &where);
        bool operator==(const Physics &where) const;

    public:
        uint64_t m_quality;
        local_st m_local;
        char m_show;
        object_t m_type;
};

#endif//__PHYSICS_H__
