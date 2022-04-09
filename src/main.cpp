#include <GLFW/glfw3.h>

#include <iostream>

GLFWwindow* WINDOW;

static unsigned int compileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    return id;
}

static int createShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);
} 

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

    float positions[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };

    unsigned int buffer;
    // TODO: These are deprecated so change.
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(0) in vec4 position;"
        "\n"
        "void main()\n"
        "{\n"
        "   gl_Position = position;\n"
        "}";

    std::string fragmentShader = 
        "#version 330 core\n"
        "\n"
        "layout(0) out vec4 colour;"
        "\n"
        "void main()\n"
        "{\n"
        "   colour = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}";

    unsigned int shader = createShader(vertexShader, fragmentShader); 
    glUseProgram(shader);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(WINDOW))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(WINDOW);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
