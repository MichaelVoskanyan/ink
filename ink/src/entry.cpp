#include "ink.h"

#include <cmath>
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_set>
#include <utility>

struct pairHash_t
{
    inline std::size_t operator()(const std::pair<int, int> &v) const
    {
        return v.first * 31 + v.second;
    }
};
using CollisionPair = std::pair<int, int>;
std::unordered_set<std::pair<int, int>, pairHash_t> activeCollisions;

float sigmoid(float t, float t0, float k)
{
    return 1.0f / (1.0f + std::exp(-k * (t - t0)));
}

bool CollisionHandler(event_t &e)
{
    std::cout << "Collision at: " << glfwGetTime() << std::endl;
    collisionEvent_t *collision_event = static_cast<collisionEvent_t *>(&e);
    std::shared_ptr<cPhysicsBody_t> playerPhysics = collision_event->entityA->GetComponent<cPhysicsBody_t>();
    std::shared_ptr<cPhysicsBody_t> blockPhysics = collision_event->entityB->GetComponent<cPhysicsBody_t>();
    glm::vec2 overlap = collision_event->overlap;
    std::cout << "(" << overlap.x << ", " << overlap.y << ")" << std::endl;
    glm::vec3 currVel = playerPhysics->Velocity();
    if(overlap.x < overlap.y)
    {
        // Resolve in x direction, zero out y
        overlap.y = 0.f;
        std::cout << "Adjust position by " << glm::length(overlap) << std::endl;
        collision_event->entityA->position_ =
            collision_event->entityA->position_ + glm::vec3(overlap.x, overlap.y, 0.f);
    }
    else
    {
        // Resolve in y direction, zero out x
        overlap.x = 0.f;
        std::cout << "Adjust position by " << glm::length(overlap) << std::endl;
        collision_event->entityA->position_ =
            collision_event->entityA->position_ + glm::vec3(overlap.x, overlap.y, 0.f);
        if(glm::abs(currVel.y) < 0.25)
        {
            currVel.y = 0.f;
            playerPhysics->Acceleration(glm::vec3(0.f, 0.f, 0.f));
        }
        else
        {
            currVel.y *= -0.8f;
        }
    }
    playerPhysics->Velocity(currVel);
    return true;
}

bool MovementHandler(event_t &e)
{
    movementEvent_t *movement_event = static_cast<movementEvent_t *>(&e);
    int pressed = movement_event->keyPress_;
    float deltaTime = movement_event->deltaTime_;
    std::shared_ptr<entity_t> player = movement_event->player_;
    std::shared_ptr<cPhysicsBody_t> playerPhysics = player->GetComponent<cPhysicsBody_t>();

    static float timeHeld = 0.0f;
    static bool jumpApplied = false;
    float maxSpeed = 2.0f; // Maximum horizontal speed
    float t0 = 0.5f; // Decrease to start accelerating faster
    float k = 8.0f; // Adjusted steepness for smoother acceleration

    if(pressed != GLFW_KEY_A && pressed != GLFW_KEY_D)
    {
        timeHeld = 0.0f; // Only reset when neither A nor D is pressed
    }
    glm::vec3 currVelocity = playerPhysics->Velocity();
    switch(pressed)
    {
    case GLFW_KEY_A:
        timeHeld += deltaTime;
        jumpApplied = false;
        playerPhysics->Velocity(glm::vec3(maxSpeed * sigmoid(timeHeld, t0, k), currVelocity.y, currVelocity.z));
        break;
    case GLFW_KEY_D:
        jumpApplied = false;
        playerPhysics->Velocity(glm::vec3(-maxSpeed * sigmoid(timeHeld, t0, k), currVelocity.y, currVelocity.z));
        break;
    case GLFW_KEY_SPACE:
        if(!jumpApplied)
        {
            playerPhysics->Velocity(glm::vec3(currVelocity.x, currVelocity.y + 2.f, currVelocity.z));
            jumpApplied = true;
        }
        break;
    default:
        std::cout << "Unknown movement event!" << std::endl;
        return false;
        break;
    };
    return true;
}

class Ink : public application_t
{
public:
    Ink()
    {
        window_ = std::make_unique<window_t>();

        Start();
    }

    std::vector<std::shared_ptr<cBoxCollider_t>> colliders;

    std::shared_ptr<entity_t> player;

    std::shared_ptr<cBoxCollider_t> playerCol;
    std::shared_ptr<cBoxCollider_t> blockCol;

    renderer_t *renderer = renderer_t::GetInstance();

    void Start()
    {
        std::shared_ptr<shader_t> shader = std::make_shared<shader_t>("/shaders/tri.vs", "/shaders/tri.fs");
        shader->Bind();

        // h_Rend->setActiveShaderHandle(shader);

        auto camera = camera_t::GetInstance();

        std::vector<float> vertsPlayer = {-0.5f, -0.5f, 0.0f, 0.f,   0.f,  0.f,  0.f,  0.f,  -0.5f, 0.5f, 0.0f,
                                          0.f,   0.f,   0.f,  0.f,   1.f,  0.5f, 0.5f, 0.0f, 0.f,   0.f,  0.f,
                                          1.f,   1.f,   0.5f, -0.5f, 0.0f, 0.f,  0.f,  0.f,  1.f,   0.f};
        std::vector<float> vertsBlock = {-2.0f, -0.5f, 0.0f, 0.f,   0.f,  0.f,  0.f,  0.f,  -2.0f, 0.5f, 0.0f,
                                         0.f,   0.f,   0.f,  0.f,   0.f,  2.0f, 0.5f, 0.0f, 0.f,   0.f,  0.f,
                                         0.f,   0.f,   2.0f, -0.5f, 0.0f, 0.f,  0.f,  0.f,  0.f,   0.f};

        std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

        player = std::make_shared<entity_t>();
        std::shared_ptr<cRenderObject_t> ro = player->AddComponent<cRenderObject_t>();
        std::shared_ptr<cPhysicsBody_t> physicsBody = player->AddComponent<cPhysicsBody_t>();
        playerCol = player->AddComponent<cBoxCollider_t>();

        std::shared_ptr<entity_t> block = std::make_shared<entity_t>();
        std::shared_ptr<cRenderObject_t> blockRend = block->AddComponent<cRenderObject_t>();
        blockCol = block->AddComponent<cBoxCollider_t>();

        ro->InitRenderObject(std::make_shared<vertexArray_t>(vertsPlayer, physicsinds), shader);

        blockRend->InitRenderObject(std::make_shared<vertexArray_t>(vertsBlock, physicsinds), shader);

        player->position_ = glm::vec3(0.f, 0.f, 0.f);
        player->rotation_ = glm::vec3(0.f);
        player->scale_ = glm::vec3(1.f);

        block->position_ = glm::vec3(0.f, -1.25f, 0.f);
        block->rotation_ = glm::vec3(0.f);
        block->scale_ = glm::vec3(1.f);

        playerCol->width_ = 1;
        playerCol->height_ = 1;
        blockCol->width_ = 4;
        blockCol->height_ = 1;

        entities_.push_back(player);
        entities_.push_back(block);

        for(auto &e : entities_)
        {
            e->Init();
            e->Start();
        }

        renderer_t::s_viewProjectionMatrix = glm::perspective(
            glm::radians(65.f), (float)window_t::GetWindowWidth() / (float)window_t::GetWindowHeight(), 0.01f, 100.f);
        renderer_t::s_viewProjectionMatrix *=
            glm::lookAt(glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.f, 0.f, -2.f), glm::vec3(0.f, 1.f, 0.f));
    }

    void Run()
    {
        while(!glfwWindowShouldClose(window_->GetGlfwWindow()))
        {
            float currentFrame = (float)glfwGetTime();
            deltaTime_ = currentFrame - m_lastFrame;
            m_lastFrame = currentFrame;
            GLFWwindow *window = glfwGetCurrentContext();

            for(auto &e : entities_)
            {
                e->Update(deltaTime_);
            }

            for(auto &e : entities_)
            {
                e->LateUpdate();
            }
            if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
            {
                movementEvent_t movementEvent(GLFW_KEY_SPACE, deltaTime_, player);
                eventDispatcher_t dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<movementEvent_t>(MovementHandler);
            }
            if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                movementEvent_t movementEvent(GLFW_KEY_A, deltaTime_, player);
                eventDispatcher_t dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<movementEvent_t>(MovementHandler);
            }
            if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                movementEvent_t movementEvent(GLFW_KEY_D, deltaTime_, player);
                eventDispatcher_t dispatcher(movementEvent); // Correctly initialize dispatcher
                dispatcher.Dispatch<movementEvent_t>(MovementHandler);
            }

            CollisionPair pair = std::minmax({playerCol->GetOwner()->GetID(), blockCol->GetOwner()->GetID()});
            glm::vec2 overlap = cBoxCollider_t::CheckCollision(*playerCol, *blockCol);
            if(overlap.x > 0.001 && overlap.y > 0.001)
            {
                if(activeCollisions.find(pair) == activeCollisions.end())
                {
                    collisionEvent_t col_event(playerCol->GetOwner(), blockCol->GetOwner(), overlap);
                    eventDispatcher_t dispatcher(col_event);
                    dispatcher.Dispatch<collisionEvent_t>(CollisionHandler);
                }
                activeCollisions.insert(pair);
            }
            else
            {
                activeCollisions.erase(pair);
                playerCol->GetOwner()->GetComponent<cPhysicsBody_t>()->Acceleration(glm::vec3(0.0f, -1.5f, 0.0f));
            }
            renderer->DrawQueue();
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
