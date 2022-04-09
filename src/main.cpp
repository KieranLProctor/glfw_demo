#include <GLFW/glfw3.h>

GLFWwindow* WINDOW;

int init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

        /* Create a windowed mode window and its OpenGL context */
    WINDOW = glfwCreateWindow(640, 480, "GLFW Demo", NULL, NULL);
    if (!WINDOW)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(WINDOW);
    glClearColor( 0.4f, 0.3f, 0.4f, 0.0f );
}

int main()
{
    init();

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(WINDOW))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(WINDOW);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
