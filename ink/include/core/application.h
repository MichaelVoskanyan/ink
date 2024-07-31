#pragma once

#include <memory>
#include <iostream>
#include <vector>

// --------------------------
// -- Forward Declarations --
// --------------------------
class Window;
class Entity;

class Application {
protected:
  std::unique_ptr<Window> _window; // Window class handle
  float deltaTime = 0, lastFrame = 0, currentTime = 0; // Delta time
  std::vector<std::shared_ptr<Entity>> _entities; // queue of Entities.

public:
  virtual ~Application() {}

  virtual void Start() {}
  virtual void Run() {}
};
