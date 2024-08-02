#ifndef INK_APPLICATION_H
#define INK_APPLICATION_H

#include <typedefs.h>

#include <memory>
#include <iostream>
#include <vector>

// --------------------------
// -- Forward Declarations --
// --------------------------
class Window;
class Entity;

class Application
{
protected:
    Scope<Window> m_window; // Window class handle
    f32 m_deltaTime = 0, m_lastFrame = 0, m_currentTime = 0; // Delta time
    Vec<Ref<Entity>> m_entities; // queue of Entities.

public:
    virtual ~Application() {}

    virtual void start() {}
    virtual void run() {}
};

#endif
