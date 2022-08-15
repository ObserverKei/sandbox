#include "space.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <iostream>

Space::~Space()
{
    for (size_t y = 0; y < SPACE_MAP_Y; ++y) {
        for (size_t x = 0; x < SPACE_MAP_X; ++x) {
            if (m_space[y][x]) {
                delete m_space[y][x];
                m_space[y][x] = nullptr;
            }
        }
    }
}

Space::Space() : m_space() 
{
    view_t *view = (view_t *)&m_view;

    //backgroud
    for (size_t y = 0; y < SPACE_VIEW_Y; ++y) {
        for (size_t x = 0; x < SPACE_VIEW_X; ++x)  {
            (*view)[y][x] = VIEW_EMPTY;
            if (x == 0 || x == SPACE_VIEW_X-1) 
                (*view)[y][x] = VIEW_EDGE_X;
            if (y == 0 || y == SPACE_VIEW_Y-1) 
                (*view)[y][x] = VIEW_EDGE_Y;
            if ((x == SPACE_VIEW_X-1 && y == SPACE_VIEW_Y-1) ||
                    (x == SPACE_VIEW_X-1 && y == 0) ||
                    (x == 0 && y == SPACE_VIEW_Y-1) || 
                    (x == 0 && y == 0)) 
                (*view)[y][x] = VIEW_EDGE_POINT;
        }
        (*view)[y][SPACE_VIEW_X] = '\n';
    }

    for (size_t y = 0; y < SPACE_MAP_Y; ++y) {
        for (size_t x = 0; x < SPACE_MAP_X; ++x) {
            m_space[y][x] = new Object(local_t(x, y));
            std::cerr << "y:" <<  m_space[y][x]->m_local.m_y << ",x:" <<  m_space[y][x]->m_local.m_x <<
                ",m_qu:" <<  m_space[y][x]->m_quality << std::endl;;
        }
    }
}

Space::iterator::iterator(Object &obj_base, size_t idx, size_t size) : m_idx(idx), m_size(size)
{
    m_base = &obj_base;
}

Space::iterator Space::iterator::operator++()
{
    if (m_idx < m_size)
        ++m_idx;
    return *this;
}

bool Space::iterator::operator!=(const iterator &where) const
{
    if (m_idx != where.m_idx)
        return true;
    if (m_size != where.m_size)
        return true;
    if (m_base != where.m_base)
        return true;
    return false;
}

Object &Space::iterator::operator*()
{
    if (m_idx < m_size)
        return m_base[m_idx];
    else
        return m_base[m_size - 1];
}

Space::iterator Space::begin()
{
    return iterator(*m_space[0][0], 0, sizeof(space_t) / sizeof(Object));
}

Space::iterator Space::end()
{
    return iterator(*m_space[0][0], sizeof(space_t) / sizeof(Object),
            sizeof(space_t) / sizeof(Object));
}

int Space::set_object(Object *object)
{
    if (!object || object->m_local.m_x >= SPACE_MAP_X || object->m_local.m_y >= SPACE_MAP_Y)
        return -1;
    if (m_space[object->m_local.m_y][object->m_local.m_x])
        delete m_space[object->m_local.m_y][object->m_local.m_x];

    m_space[object->m_local.m_y][object->m_local.m_x] = object;

    return 0;
}

int Space::get_object(const local_t &local, Object **object)
{
    if (!object || local.m_x >= SPACE_MAP_X || local.m_y >= SPACE_MAP_Y)
        return -1;

    *object = m_space[local.m_y][local.m_x];

    return 0;
}

void Space::draw_view(void)
{
#if 0
    for (auto iter = snake->rbegin(); iter != snake->rend(); ++iter) {
        (*(map_t *)map)[iter->second][iter->first] = 
            (*iter == snake->front()) ? VIEW_SPACE_HEAD : VIEW_SPACE_BODY;
    }
#endif

    for (size_t y = 0; y < SPACE_MAP_Y; ++y) 
        for (size_t x = 0; x < SPACE_MAP_X; ++x)
            m_view[y+SPACE_VIEW_EDGE][x+SPACE_VIEW_EDGE] = m_space[y][x]->m_show;

#define VIEW_INFO "[score:%34zu]\n"
    std::string view_info = std::string("[score:%") + 
        std::to_string((SPACE_MAP_X) > strlen("score:") ? 
                (SPACE_MAP_X - strlen("score:")) : 1) + "zu]\n";
    std::string view_format = std::string("%s") + view_info + 
        std::string("\033[") + std::to_string(SPACE_MAP_Y + 3) + "A";
    std::string view_str((const char *)m_view, sizeof(m_view));

    size_t m_score = 0;

    SPACE_VIEW(view_format.c_str(), view_str.c_str(), m_score);
    usleep(SPACE_VIEW_LOOP_TIME_MS * 1000);
}

