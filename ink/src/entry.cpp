#include "ink.h"

#include <iostream>
#include <vector>
#include <memory>

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

        std::vector<float> verts1 = {
				-0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 0.f,
				-0.5f, 0.5f, 0.0f, 0.f, 0.f, 0.f, 0.f, 1.f,
				0.5f, 0.5f, 0.0f, 0.f, 0.f, 0.f, 1.f, 1.f,
				0.5f, -0.5f, 0.0f, 0.f, 0.f, 0.f, 1.f, 0.f
		};

        std::vector<uint32_t> physicsinds = {0, 1, 2, 0, 2, 3};

        player = std::make_shared<Entity>();
        std::shared_ptr<C_RenderObject> ro = player->add_component<C_RenderObject>();
        std::shared_ptr<C_CharacterController> cc = player->add_component<C_CharacterController>();
        std::shared_ptr<C_PhysicsBody> phyicsBody = player->add_component<C_PhysicsBody>();
        playerCol = player->add_component<C_BoxCollider>();

        std::shared_ptr<Entity> block = std::make_shared<Entity>();
        std::shared_ptr<C_RenderObject> blockRend = block->add_component<C_RenderObject>();
        blockCol = block->add_component<C_BoxCollider>();

        ro->init_render_object(std::make_shared<VertexArray>(verts1, physicsinds), shader);
        // ro->vertices = verts1;
        // ro->indices = physicsinds;
        // ro->SetShader(shader);

        // blockRend->vertices = verts1;
        // blockRend->indices = physicsinds;
        // blockRend->SetShader(shader);
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

//        renderer->queue_render_object(ro->getRenderObject());
//        renderer->addToRenderQueue(blockRend->getRenderObject());



        for(auto &e : m_entities)
        {
            e->init();
            e->start();
        }
    }

    void Run()
    {
		Renderer::s_viewProjectionMatrix = glm::perspective(glm::radians(65.f), (float)800/(float)600, 0.01f, 100.f);
		Renderer::s_viewProjectionMatrix *= glm::lookAt(glm::vec3(0.f, 0.f, -3.f), glm::vec3(0.f, 0.f, -2.f), glm::vec3(0.f, 1.f, 0.f));

        while(!glfwWindowShouldClose(m_window->get_glfw_window()))
        {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float currentFrame = (float)glfwGetTime();
			m_deltaTime = currentFrame - m_lastFrame;
			m_lastFrame = currentFrame;

            for(auto &e : m_entities)
            {
                e->update(m_deltaTime);
            }

            for(auto &e : m_entities)
            {
				e->late_update();
            }

			renderer->draw_queue();

            if(C_BoxCollider::check_collision(*playerCol, *blockCol))
            {
                std::shared_ptr<C_PhysicsBody> playerPhys = player->get_component<C_PhysicsBody>();
                glm::vec3 currVel = playerPhys->velocity();
                currVel.y = 0.f;
				playerPhys->velocity(currVel);
                std::cout << "Collision\n";
            }

            glfwPollEvents();
            glfwSwapBuffers(m_window->get_glfw_window());
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
