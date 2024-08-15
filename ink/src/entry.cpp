#include "ink.h"

#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <utility>

struct pair_hash
{
    inline std::size_t operator()(const std::pair<int, int> &v) const
    {
        return v.first * 31 + v.second;
    }
};
using CollisionPair = std::pair<int, int>;
std::unordered_set<std::pair<int, int>, pair_hash> activeCollisions;

bool collision_handler(Event &e)
{
    std::cout << "Collision at: " << glfwGetTime() << std::endl;
    CollisionEvent *collision_event = static_cast<CollisionEvent *>(&e);
    std::shared_ptr<C_PhysicsBody> playerPhysics = collision_event->entityA->get_component<C_PhysicsBody>();
    std::shared_ptr<C_PhysicsBody> blockPhysics = collision_event->entityB->get_component<C_PhysicsBody>();
    std::shared_ptr<C_BoxCollider> playerCollider = collision_event->entityA->get_component<C_BoxCollider>();
    std::shared_ptr<C_BoxCollider> blockCollider = collision_event->entityA->get_component<C_BoxCollider>();
    glm::vec3 direction = collision_event->entityA->m_position - collision_event->entityB->m_position;
    float adjustDistance = 1.f - glm::length(direction);
    std::cout << "Adjust position by " << adjustDistance << std::endl;
    collision_event->entityA->m_position = collision_event->entityA->m_position + glm::vec3(0.f, adjustDistance, 0.f);
    glm::vec3 currVel = playerPhysics->velocity();
    if(glm::length(currVel) < 0.25)
    {
        currVel.y = 0.f;
        playerPhysics->acceleration(glm::vec3(0.f, 0.f, 0.f));
    }
    else
    {
        currVel.y = currVel.y * -0.9f;
    }
    playerPhysics->velocity(currVel);
    return true;
}

bool movement_handler(Event &e)
{
    MovementEvent *movement_event = static_cast<MovementEvent *>(&e);
    int pressed = movement_event->keyPress;
    float deltaTime = movement_event->deltaTime;
    std::shared_ptr<Entity> player = movement_event->player;
    std::cout << "Processing Movement Command " << pressed << std::endl;
    switch(pressed)
    {
    case GLFW_KEY_W:
        player->m_position.y += 5.f * deltaTime;
        break;
    case GLFW_KEY_A:
        player->m_position.x += 5.f * deltaTime;
        break;
    case GLFW_KEY_S:
        player->m_position.y -= 5.f * deltaTime;
        break;
    case GLFW_KEY_D:
        player->m_position.x -= 5.f * deltaTime;
        break;
    default:
        std::cout << "Unknown movement event!" << std::endl;
        return false;
        break;
    };
    return true;
}

class Ink : public Application
{
public:
    Ink()
    {
        m_window = std::make_unique<Window>();

        Start();
    }

    std::vector<std::shared_ptr<C_BoxCollider>> colliders;

    std::shared_ptr<Entity> player;

    std::shared_ptr<C_BoxCollider> playerCol;
    std::shared_ptr<C_BoxCollider> blockCol;

    Renderer *renderer = Renderer::get_instance();

    void Start()
    {
        std::shared_ptr<Shader> shader = std::make_shared<Shader>("/shaders/tri.vs", "/shaders/tri.fs");
        shader->bind();

        // h_Rend->setActiveShaderHandle(shader);

        auto camera = Camera::get_instance();

        std::vector<float> verts1 = {-0.5f, -0.5f, 0.0f, 0.f,   0.f,  0.f,  0.f,  0.f,  -0.5f, 0.5f, 0.0f,
                                     0.f,   0.f,   0.f,  0.f,   1.f,  0.5f, 0.5f, 0.0f, 0.f,   0.f,  0.f,
                                     1.f,   1.f,   0.5f, -0.5f, 0.0f, 0.f,  0.f,  0.f,  1.f,   0.f};

        std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

        player = std::make_shared<Entity>();
        std::shared_ptr<C_RenderObject> ro = player->add_component<C_RenderObject>();
        std::shared_ptr<C_PhysicsBody> physicsBody = player->add_component<C_PhysicsBody>();
        playerCol = player->add_component<C_BoxCollider>();

        std::shared_ptr<Entity> block = std::make_shared<Entity>();
        std::shared_ptr<C_RenderObject> blockRend = block->add_component<C_RenderObject>();
        blockCol = block->add_component<C_BoxCollider>();

        ro->init_render_object(std::make_shared<VertexArray>(verts1, physicsinds), shader);

        blockRend->init_render_object(std::make_shared<VertexArray>(verts1, physicsinds), shader);

        player->m_position = glm::vec3(0.f, 0.f, 0.f);
        player->m_rotation = glm::vec3(0.f);
        player->m_scale = glm::vec3(1.f);

        block->m_position = glm::vec3(0.f, -1.25f, 0.f);
        block->m_rotation = glm::vec3(0.f);
        block->m_scale = glm::vec3(1.f);

        playerCol->m_width = 1;
        playerCol->m_height = 1;
        blockCol->m_width = 1;
        blockCol->m_height = 1;

        m_entities.push_back(player);
        m_entities.push_back(block);

        for(auto &e : m_entities)
        {
            e->init();
            e->start();
        }

        Renderer::s_viewProjectionMatrix = glm::perspective(
            glm::radians(65.f), (float)Window::get_window_width() / (float)Window::get_window_height(), 0.01f, 100.f);
        Renderer::s_viewProjectionMatrix *=
            glm::lookAt(glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.f, 0.f, -2.f), glm::vec3(0.f, 1.f, 0.f));
    }

    void Run()
    {
        while(!glfwWindowShouldClose(m_window->get_glfw_window()))
        {
            float currentFrame = (float)glfwGetTime();
            m_deltaTime = currentFrame - m_lastFrame;
            m_lastFrame = currentFrame;
            GLFWwindow *window = glfwGetCurrentContext();

            for(auto &e : m_entities)
            {
                e->update(m_deltaTime);
            }

            for(auto &e : m_entities)
            {
                e->late_update();
            }
            if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                MovementEvent movementEvent(GLFW_KEY_W, m_deltaTime, player);
                EventDispatcher dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<MovementEvent>(movement_handler);
            }
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                MovementEvent movementEvent(GLFW_KEY_A, m_deltaTime, player);
                EventDispatcher dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<MovementEvent>(movement_handler);
            }
            if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                MovementEvent movementEvent(GLFW_KEY_S, m_deltaTime, player);
                EventDispatcher dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<MovementEvent>(movement_handler);
            }
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                MovementEvent movementEvent(GLFW_KEY_D, m_deltaTime, player);
                EventDispatcher dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<MovementEvent>(movement_handler);
            }

            CollisionPair pair = std::minmax({playerCol->get_owner()->getId(), blockCol->get_owner()->getId()});
            if(C_BoxCollider::check_collision(*playerCol, *blockCol))
            {
                if(activeCollisions.find(pair) == activeCollisions.end())
                {
                    CollisionEvent col_event(playerCol->get_owner(), blockCol->get_owner());
                    EventDispatcher dispatcher(col_event);
                    dispatcher.Dispatch<CollisionEvent>(collision_handler);
                }
                activeCollisions.insert(pair);
            }
            else
            {
                activeCollisions.erase(pair);
                playerCol->get_owner()->get_component<C_PhysicsBody>()->acceleration(glm::vec3(0.0f, -1.5f, 0.0f));
            }
            renderer->draw_queue();
            glfwPollEvents();
        }
    }
};

int main(int argc, char **argv)
{
    auto ink = new Ink();

    ink->Run();
    glfwTerminate();
    return 0;
}
