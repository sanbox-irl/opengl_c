#include "Types.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assert.h>
#include <iostream>
#include <sstream>

#include "IndexBuffer.h"
#include "Shader.h"
#include "Texture.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

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
            -0.5f, -0.5f, 0.0f, 0.0f, // 0
            0.5f,  -0.5f, 1.0f, 0.0f, // 1
            0.5f,  0.5f,  1.0f, 1.0f, // 2
            -0.5f, 0.5f,  0.0f, 1.0f, // 3
        };

        u32 indices[] = {
            0, 1, 2, // triangle0
            2, 3, 0  // triangle1
        };

        // glEnable(GL_BLEND);
        // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        VertexArray va;
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        GLCall(va.AddBuffer(vb, layout));

        IndexBuffer ib(indices, 6);
        Shader default_shader("resources/shaders/default_vert.shader",
                              "resources/shaders/default_frag.shader");
        GLCall(default_shader.Bind());
        GLCall(default_shader.SetUniform4f("u_Color", 0.1, 0.2, 0.3, 1.0));

        Texture texture("resources/textures/link.png");
        GLCall(texture.Bind());
        GLCall(default_shader.SetUniform1i("u_Texture", 0));

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        default_shader.Unbind();

        Renderer renderer;

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window)) {
            /* Render here */
            renderer.Clear();

            GLCall(default_shader.Bind());
            GLCall(default_shader.SetUniform1i("u_Texture", 0));

            // default_shader.SetUniform4f("u_Color", 0.1, 0.2, 0.3, 1.0);

            GLCall(renderer.Draw(va, ib, default_shader));

            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
    }

    glfwTerminate();
    return 0;
}
