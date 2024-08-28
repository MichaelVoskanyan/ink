#ifndef INK_APPLICATION_H
#define INK_APPLICATION_H

#include <typedefs.h>

#include <memory>
#include <iostream>
#include <vector>

// --------------------------
// -- Forward Declarations --
// --------------------------
class window_t;
class entity_t;

class application_t
{
protected:
    Scope<window_t> window_; // Window class handle
    f32 deltaTime_ = 0, m_lastFrame = 0, m_currentTime = 0; // Delta time
    Vec<Ref<entity_t>> entities_; // queue of Entities.

public:
    virtual ~application_t() {}

    virtual void Start() {}
    virtual void Run() {}
};

#endif
