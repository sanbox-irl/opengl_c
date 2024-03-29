#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "renderer/IndexBuffer.h"
#include "renderer/Shader.h"
#include "renderer/Texture.h"
#include "renderer/Types.h"
#include "renderer/VertexArray.h"
#include "renderer/VertexBuffer.h"
#include "renderer/VertexBufferLayout.h"

int main(void) {
    GLFWwindow *window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1920, 1080, "Hello World", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        return -1;
    } else {
        std::cout << "Initiating OpenGL " << glGetString(GL_VERSION) << std::endl;
    }
    {

        // Create our OpenGL buffer...
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
            50.0f,  -50.0f, 1.0f, 0.0f, // 1
            50.0f,  50.0f,  1.0f, 1.0f, // 2
            -50.0f, 50.0f,  0.0f, 1.0f, // 3
        };

        u32 indices[] = {
            0, 1, 2, // triangle0
            2, 3, 0  // triangle1
        };

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        glm::mat4 proj = glm::ortho(0.0f, 1920.0f, 0.0f, 1080.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        Shader default_shader("resources/shaders/default_vert.shader",
                              "resources/shaders/default_frag.shader");
        default_shader.Bind();
        default_shader.SetUniform4f("u_Color", 0.1f, 0.2f, 0.3f, 1.0f);

        Texture texture("resources/textures/zelda.png");
        texture.Bind();
        default_shader.SetUniform1i("u_Texture", 0);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        default_shader.Unbind();

        Renderer renderer;
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        ImGuiIO &io = ImGui::GetIO();

        auto translationA = glm::vec3(200, 800, 0);
        auto translationB = glm::vec3(400, 800, 0);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::Begin("Edit Model Matrix");
            ImGui::SliderFloat2("TranslationA", &translationB.x, 0.0f, 1920.0f);
            ImGui::SliderFloat2("TranslationB", &translationB.x, 0.0f, 1920.0f);
            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)",
                        1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

            ImGui::End();

            // Updating Model Matrix
            default_shader.Bind();
            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
                glm::mat4 mvp = proj * view * model;
                default_shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, default_shader);
            }

            {
                glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB);
                glm::mat4 mvp = proj * view * model;
                default_shader.SetUniformMat4f("u_MVP", mvp);
                renderer.Draw(va, ib, default_shader);
            }

            ImGui::Render();
            auto draw_data = ImGui::GetDrawData();
            ImGui_ImplOpenGL3_RenderDrawData(draw_data);

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
