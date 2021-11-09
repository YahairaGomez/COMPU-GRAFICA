//     ALUMNA//Nombre: Christina Chacón
//Curso: Computación gráfica

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, unsigned int VAO[]);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    float vertices_triangle[] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
    unsigned int indices_triangle[] = {  // note that we start from 0!
        0, 1, 2  // first Triangle
    };
    float vertices_Quad[] = {
        0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // top right
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom right
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom left
       -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f   // top left 
    };
    unsigned int indices_Quad[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3   // second Triangle
    };
    float vertices_star[] = {
        -0.06f * 2, 0.2f * 2, 0.0f,     1.0f, 0.0f, 0.0f, //A
    0.0f, 0.4f * 2, 0.0f,               0.0f, 1.0f, 0.0f, //B
     0.06f * 2, 0.2f * 2, 0.0f,         0.0f, 1.0f, 0.0f,     //C
    0.20f * 2, 0.2f * 2, 0.0f,          0.0f, 1.0f, 0.0f, //D
    0.09f * 2, 0.1f * 2, 0.0f,          1.0f, 0.0f, 0.0f, //E
    0.15f * 2, -0.1f * 2, 0.0f,         0.0f, 0.0f, 0.0f, //F
    0.0f * 2, 0.03f * 2, 0.0f,          1.0f, 1.0f, 0.0f, //G
    -0.15f * 2, -0.1f * 2, 0.0f,        0.0f, 0.0f, 0.0f, //H
    -0.09f * 2, 0.1f * 2, 0.0f,         0.0f, 0.0f, 0.0f, //I
    -0.20f * 2, 0.2f * 2, 0.0f,         1.0f, 0.0f, 0.0f, //J

    };
    unsigned int indices_star[] = {
        0, 1, 2,
        2,3,4,
        4,5,6,
        6,7,8,
        8,9,0,
        0,2,8,
        2,8,6,
        2,6,4

    };
    //TRIANGULO

    unsigned int VBO[3], VAO[3], EBO[3];
    glGenVertexArrays(1, &VAO[0]); glGenBuffers(1, &VBO[0]);  glGenBuffers(1, &EBO[0]); 
    glBindVertexArray(VAO[0]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_triangle), vertices_triangle, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_triangle), indices_triangle, GL_STATIC_DRAW);
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //CUADRADO
    glGenVertexArrays(1, &VAO[1]); glGenBuffers(1, &VBO[1]);  glGenBuffers(1, &EBO[1]);
    glBindVertexArray(VAO[1]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_Quad), vertices_Quad, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_Quad), indices_Quad, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //STAR
    glGenVertexArrays(1, &VAO[2]); glGenBuffers(1, &VBO[2]);  glGenBuffers(1, &EBO[2]); 
    glBindVertexArray(VAO[2]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_star), vertices_star, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_star), indices_star, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    // glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to 
    glUseProgram(shaderProgram);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // input
        // -----
        processInput(window, VAO);
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &*VAO); //glDeleteVertexArrays(1, &VAO[1]); glDeleteVertexArrays(1, &VAO[2]);
    glDeleteBuffers(1, &*VBO); //glDeleteBuffers(1, &VBO[1]); glDeleteBuffers(1, &VBO[2]);
    glDeleteBuffers(1, &*EBO); //glDeleteBuffers(1, &EBO[1]); glDeleteBuffers(1, &EBO[2]);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, unsigned int VAO[])
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { //TRIANGLE
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 4, GL_UNSIGNED_INT, 0);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { //SQUARE
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { //STAR
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES, 24, GL_UNSIGNED_INT, 0);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}