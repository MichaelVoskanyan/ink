#include <ecs/entity.h>

int entity_t::s_idCounter = 0;

void entity_t::Init()
{
    id_ = s_idCounter++;
    for(int i = components_.size() - 1; i >= 0; i--)
    {
        components_[i]->Init();
    }
}

void entity_t::Start()
{
    for(int i = components_.size() - 1; i >= 0; i--)
    {
        components_[i]->Start();
    }
}

void entity_t::Update(float deltaTime)
{
    for(int i = components_.size() - 1; i >= 0; i--)
    {
        components_[i]->Update(deltaTime);
    }
}

void entity_t::LateUpdate()
{
    for(int i = components_.size() - 1; i >= 0; i--)
    {
        components_[i]->LateUpdate();
    }
}
