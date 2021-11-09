/*INTEGRANTES:
     - CHRISTINA CHACÓN ALLEMÁN
     - YAHAIRA GOMEZ SUCASACA
  CURSO: COMPUTACIÓN GRÁFICA
*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void processInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 Color;\n"
"void main()\n"
"{\n"
"   FragColor = Color;\n"
"}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "virgen", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create glfw window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    // glad: load all opengl function pouinter
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //*****************VertexShader******************
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    //**************check vertex shader*********
    int success;
    char infolog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
        std::cout << "ERROR VERTER:_SHADER_COMPILATION" << std::endl;
    }
    //**************CREATE AND COMPILE Fragment shadre***********
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    //**************FRAGMENTSHADER**********************
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infolog << std::endl;
    }
    //***********LINK SHADER*************************
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    //***********check for linking errors************
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //***************END CONCIFG AND LINKED ***************
    float big_aureola[] = {
            0.0f, 0.3f, 0.0f, //origin
            0.0f, 0.0f, 0.0f, //down
            0.05f, 0.01f, 0.0f, //right down
            0.1f, 0.02f, 0.0f,
            0.16f, 0.05f, 0.0f,
            0.23f, 0.1f, 0.0f,
            0.26f, 0.15f, 0.0f,
            0.28f, 0.2f, 0.0f,
            0.29f, 0.25f, 0.0f,
            0.3f, 0.3f, 0.0f, //center right
            0.29f, 0.35f, 0.0f,
            0.28f, 0.4f, 0.0f,
            0.26f, 0.45f, 0.0f,
            0.23f, 0.5f, 0.0f,
            0.16f, 0.55f, 0.0f,
            0.1f, 0.58f, 0.0f,
            0.05f, 0.59f, 0.0f, //right up
            0.0f, 0.6f, 0.0f, //up
            -0.05f, 0.59f, 0.0f, //left up
            -0.1f, 0.58f, 0.0f,
            -0.16f, 0.55f, 0.0f,
            -0.23f, 0.5f, 0.0f,
            -0.26f, 0.45f, 0.0f,
            -0.28f, 0.4f, 0.0f,
            -0.29f, 0.35f, 0.0f,
            -0.3f, 0.3f, 0.0f, //center left
            -0.29f, 0.25f, 0.0f,
            -0.28f, 0.2f, 0.0f,
            -0.26f, 0.15f, 0.0f,
            -0.23f, 0.1f, 0.0f,
            -0.16f, 0.05f, 0.0f,
            -0.1f, 0.02f, 0.0f,
            -0.05f, 0.01f, 0.0f //left down
    };
    unsigned int indices_big_aureola[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,12,
        0,12,13,
        0,13,14,
        0,14,15,
        0,15,16,
        0,16,17,
        0,17,18,
        0,18,19,
        0,19,20,
        0,20,21,
        0,21,22,
        0,22,23,
        0,23,24,
        0,24,25,
        0,25,26,
        0,26,27,
        0,27,28,
        0,28,29,
        0,29,30,
        0,30,31,
        0,31,32,
        32,0,1
    };
    float face_mom[] = {
         -0.17f, 0.37f, 0.0f,
         -0.16f, 0.27f, 0.0f,
         -0.06f, 0.32f, 0.0f,
         0.02f, 0.24f, 0.0f,
         -0.13f, 0.2f, 0.0f,
         -0.1f, 0.16f, 0.0f,
         -0.05f, 0.13f, 0.0f,
         -0.01f, 0.13f, 0.0f,
          0.04f, 0.17f, 0.0f,
         0.05f, 0.12f, 0.0f,
         0.0f, 0.1f, 0.0f
    };
    unsigned int indices_face_mom[] = {
        0,1,2,
        1,2,3,
        3,1,4,
        3,4,5,
        3,5,6,
        3,6,7,
        3,7,8,
        7,8,9,
        7,9,10
    };
    float clothe[] = {
        0.04f, 0.38f, 0.0f,
        0.02f, 0.26f, 0.0f,
        -0.07f, 0.33f, 0.0f,
        -0.13f, 0.36f, 0.0f,
        -0.17f, 0.38f, 0.0f,
        -0.14f, 0.44f, 0.0f,
        -0.07f, 0.5f, 0.0f,
        -0.01f, 0.52f, 0.0f,
        0.07f, 0.5f, 0.0f,
        0.13f, 0.45f, 0.0f,
        0.17f, 0.4f, 0.0f,
        0.2f, 0.35f, 0.0f,
        0.14f, 0.15f, 0.0f,
        0.02f, 0.26f, 0.0f,
        0.2f, 0.35f, 0.0f,
        0.23f, 0.27f, 0.0f,
        0.24f, 0.13f, 0.0f,
        0.25f, 0.06f, 0.0f,
        0.05f, 0.0f, 0.0f,
        0.03f, 0.13f, 0.0f,
        0.0f, 0.1f, 0.0f,
        -0.04f, 0.06f, 0.0f,
        0.08f, -0.06f, 0.0f,
        0.07f, -0.41f, 0.0f,
        0.28f, -0.09f, 0.0f,
        0.3f, -0.24f, 0.0f,
        0.26f, -0.44f, 0.0f,
        0.22f, -0.54f, 0.0f,
        0.13f, -0.57f, 0.0f,
        0.0f, -0.57f, 0.0f,
        -0.07f, -0.56f, 0.0f,
        -0.14f, -0.53f, 0.0f,
        -0.19f, -0.48f, 0.0f,
        -0.22f, -0.37f, 0.0f,
        -0.1f, -0.35f, 0.0f,
        -0.01f, -0.27f, 0.0f,
        -0.09f, -0.2f, 0.0f,
        0.06f, -0.17f, 0.0f
    };
    unsigned int indices_clothe[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1,
        12,13,14,
        12,14,15,
        12,15,16,
        12,16,17,
        12,17,18,
        12,18,19,
        12,19,13,
        18,19,20,
        18,20,21,
        17,18,22,
        23,22,17,
        23,17,24,
        23,24,25,
        23,25,26,
        23,26,27,
        23,27,28,
        23,28,29,
        23,29,30,
        23,30,31,
        23,31,32,
        23,32,33,
        23,33,34,
        23,34,35,
        23,35,36,
        23,36,37,
        23,37,22
    };
    float hair_mom[] = {
       -0.06f, 0.38f,0.0f,
       -0.14f, 0.45f,0.0f,
       -0.16f, 0.41f,0.0f,
       -0.17f, 0.36f,0.0f,
       -0.13f, 0.35f,0.0f,
       -0.1f, 0.34f,0.0f,
       -0.07f, 0.32f,0.0f,
       -0.03f, 0.29f,0.0f,
       0.03f, 0.23f,0.0f,
       -0.01f, 0.33f,0.0f,
       -0.02f, 0.36f,0.0f,
       -0.04f, 0.39f,0.0f,
       -0.08f, 0.42f,0.0f
    };
    unsigned int indices_hair_mom[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
    };
    float hand_mom[] = {
        -0.22f,-0.2f,0.0f,
        -0.1f, -0.03f, 0.0f,
        -0.15f, -0.02f, 0.0f,
        -0.22f, -0.15f, 0.0f,
        -0.24f, -0.2f, 0.0f,
        -0.25f, -0.25f, 0.0f,
        -0.24f, -0.3f, 0.0f,
        -0.23f, -0.34f, 0.0f,
        -0.22f, -0.38f, 0.0f,
        -0.17f, -0.36f, 0.0f,
        -0.13f, -0.36f, 0.0f,
        -0.1f, -0.35f, 0.0f,
        -0.18f, -0.23f, 0.0f,
        -0.14f, -0.22f, 0.0f,
        -0.1f, -0.21f, 0.0f,
        -0.09f, -0.18f, 0.0f,
        -0.11f, -0.17f, 0.0f,
        -0.16f, -0.17f, 0.0f,
        -0.19f, -0.17f, 0.0f
    };
    unsigned int indices_hand_mom[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,12,
        0,12,13,
        0,13,14,
        0,14,15,
        0,15,16,
        0,16,17,
        0,17,18,
        0,18,1
    };
    float small_aureola[] = {
        -0.07f, -0.08f,0.0f,
        -0.14f, 0.03f,0.0f,
        -0.18f, -0.03f,0.0f,
        -0.2f, -0.13f,0.0f,
        -0.1f, -0.24f,0.0f,
        0.0f, -0.21f,0.0f,
         0.06f, -0.17f,0.0f,
        0.07f, -0.1f,0.0f,
        0.08f, -0.06f,0.0f,
        0.05f, 0.0f,0.0f,
        0.0f, 0.04f,0.0f,
        -0.06f, 0.05f,0.0f,
        -0.07f, -0.08f,0.0f
    };
    unsigned int indices_small_aureola[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
    };
    float child[] = {
        -0.02f, -0.13f, 0.0f,
        -0.1f, -0.13f, 0.0f,
        -0.07f, -0.11f, 0.0f,
        0.0f, -0.1f, 0.0f,
        0.04f, -0.08f, 0.0f,
        0.05f, -0.12f, 0.0f,
        0.02f, -0.16f, 0.0f,
        0.0f, -0.17f, 0.0f,
        -0.01f, -0.19f, 0.0f,
        -0.04f, -0.19f, 0.0f
    };
    unsigned int indices_child[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,1
    };
    float body_child[] = {
        -0.02f, -0.13f, 0.0f,
        -0.1f, -0.13f, 0.0f,
        -0.07f, -0.11f, 0.0f,
        0.0f, -0.1f, 0.0f,
        0.04f, -0.08f, 0.0f,
        0.05f, -0.12f, 0.0f,
        0.02f, -0.16f, 0.0f,
        0.0f, -0.17f, 0.0f,
        -0.01f, -0.19f, 0.0f,
        -0.04f, -0.19f, 0.0f,
        -0.09f, -0.26f, 0.0f,
        -0.01f, -0.27f, 0.0f,
        -0.08f, -0.34f, 0.0f,
        -0.12f, -0.33f, 0.0f,
        -0.15f, -0.31f, 0.0f,
        -0.18f, -0.27f, 0.0f,
        -0.19f, -0.24f, 0.0f,
        -0.17f, -0.22f, 0.0f,
        -0.11f, -0.22f, 0.0f,
        -0.09f, -0.19f, 0.0f,
        -0.07f, -0.16f, 0.0f,
        -0.11f, -0.17f, 0.0f,
        -0.15f, -0.13f, 0.0f,
        -0.17f, -0.16f, 0.0f
    };
    unsigned int indices_body_child[] = {
        10,9,11,
        10,11,12,
        10,12,13,
        10,13,14,
        10,14,15,
        10,15,16,
        10,16,17,
        10,17,18,
        10,18,9,
        18,9,19,
        9,19,20,
        19,20,21,
        20,21,1,
        1,21,22,
        23,22,21,
        23,16,9,
        23,11,1,
        10,16,1
    };
    float child_hair[] = {
        -0.07f, -0.08f, 0.0f,
        -0.17f, -0.11f, 0.0f,
        -0.12f, -0.06f, 0.0f,
        -0.07f, -0.01f, 0.0f,
        -0.02f, -0.0f, 0.0f,
        0.03f, -0.02f, 0.0f,
        0.05f, -0.06f, 0.0f,
        0.04f, -0.08f, 0.0f,
        0.0f, -0.1f, 0.0f,
        -0.07f, -0.11f, 0.0f,
        -0.1f, -0.13f, 0.0f,
        -0.15f, -0.13f, 0.0f
    };
    unsigned int indices_child_hair[] = {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,7,
        0,7,8,
        0,8,9,
        0,9,10,
        0,10,11,
        0,11,1
    };
    float picture[] = {
        -0.46f, 0.64f, 0.0f,
        0.44f, 0.64f, 0.0f,
        0.44f, -0.57f, 0.0f,
        -0.45f, -0.57f, 0.0f
    };
    unsigned int indices_picture[] = {
        0,1,2,
        2,3,0
    };
    float lines[] = {
        //picture
        -0.46f, 0.64f, 0.0f,
        0.44f, 0.64f, 0.0f,
        0.44f, -0.57f, 0.0f,
        -0.46f, -0.57f, 0.0f,
        -0.46f, 0.64f, 0.0f,
        //lines
         -0.43f, 0.64f, 0.0f,
         -0.32f, -0.57f, 0.0f,
         -0.2f, -0.57f, 0.0f,
         -0.13f, 0.64f, 0.0f,
         0.0f, 0.64f, 0.0f,
         0.2f, -0.57f, 0.0f,
         0.4f, -0.57f, 0.0f,
         0.35f, 0.64f, 0.0f,
         0.44f, 0.64f, 0.0f,
         0.44f, -0.2f, 0.0f,
         0.3f, -0.57f, 0.0f,
         0.0f, -0.57f, 0.0f,
         0.44f, 0.54f, 0.0f,
         0.44f, 0.64f, 0.0f,
         0.2f, 0.64f, 0.0f,
         -0.46f, -0.45f, 0.0f,
         -0.46f, 0.2f, 0.0f,
         0.0f, 0.64f, 0.0f
    };
    //Variables for each array
    unsigned int VBO[11], VAO[11], EBO[10];
    glGenVertexArrays(11, VAO);
    glGenBuffers(11, VBO);
    glGenBuffers(10, EBO);

    /////////////big_aureola  
    glBindVertexArray(VAO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(big_aureola), big_aureola, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_big_aureola), indices_big_aureola, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////face_mom
    glBindVertexArray(VAO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(face_mom), face_mom, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_face_mom), indices_face_mom, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////clothe
    glBindVertexArray(VAO[2]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(clothe), clothe, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_clothe), indices_clothe, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////small_aureola
    glBindVertexArray(VAO[3]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(small_aureola), small_aureola, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_small_aureola), indices_small_aureola, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////hair_mom
    glBindVertexArray(VAO[4]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hair_mom), hair_mom, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_hair_mom), indices_hair_mom, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////picture
    glBindVertexArray(VAO[5]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(picture), picture, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[5]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_picture), indices_picture, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////child
    glBindVertexArray(VAO[6]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(child), child, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[6]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_child), indices_child, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////body_child
    glBindVertexArray(VAO[7]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(body_child), body_child, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[7]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_body_child), indices_body_child, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////child_hair
    glBindVertexArray(VAO[8]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[8]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(child_hair), child_hair, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[8]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_child_hair), indices_child_hair, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////hand_mom
    glBindVertexArray(VAO[9]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[9]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(hand_mom), hand_mom, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[9]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_hand_mom), indices_hand_mom, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    /////////////lines
    glBindVertexArray(VAO[10]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[10]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(lines), lines, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glPointSize(10);
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "Color");

        //FONDO DE MARCO
        glLineWidth(5.0f);
        glUniform4f(vertexColorLocation, 1.0f, 0.5f, 0.6f, 0.0f);
        glBindVertexArray(VAO[5]);
        glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);

        //Lines
        glUniform4f(vertexColorLocation, 0.0f, 0.0f, 0.0f, 0.0f);
        glBindVertexArray(VAO[10]);
        glLineWidth(5.0f);
        glDrawArrays(GL_LINE_STRIP, 0, 23);

        //AUREOLA MADRE
        glUniform4f(vertexColorLocation, 1.0f, 1.2f, 0.2f, 0.0f);
        glBindVertexArray(VAO[0]);
        glDrawElements(GL_TRIANGLES, 96, GL_UNSIGNED_INT, 0);

        //CARA DE MADRE
        glUniform4f(vertexColorLocation, 0.98f, 0.65f, 0.35f, 0.0f);
        glBindVertexArray(VAO[1]);
        glDrawElements(GL_TRIANGLES, 27, GL_UNSIGNED_INT, 0);

        //TUNICA MADRE 
        glUniform4f(vertexColorLocation, 0.18f, 0.5f, 0.65f, 1.0f);
        glBindVertexArray(VAO[2]);
        glDrawElements(GL_TRIANGLES, 111, GL_UNSIGNED_INT, 0);

        //CABELLO MADRE
        glUniform4f(vertexColorLocation, 0.3f, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(VAO[4]);
        glDrawElements(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0);

        //Aureola_niño 
        glUniform4f(vertexColorLocation, 1.0f, 1.2f, 0.2f, 0.0f);
        glBindVertexArray(VAO[3]);
        glDrawElements(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0);

        //CARA NIÑO
        glUniform4f(vertexColorLocation, 0.98f, 0.65f, 0.35f, 0.0f);
        glBindVertexArray(VAO[6]);
        glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

        //CUERPO NIÑO
        glUniform4f(vertexColorLocation, 1.0f, 0.8f, 0.8f, 0.0f);
        glBindVertexArray(VAO[7]);
        glDrawElements(GL_TRIANGLES, 72, GL_UNSIGNED_INT, 0);

        //CABELLO NIÑO
        glUniform4f(vertexColorLocation, 0.4f, 0.0f, 0.0f, 1.0f);
        glBindVertexArray(VAO[8]);
        glDrawElements(GL_TRIANGLES, 33, GL_UNSIGNED_INT, 0);

        //MANO DE MADRE
        glUniform4f(vertexColorLocation, 0.98f, 0.65f, 0.35f, 0.0f);
        glBindVertexArray(VAO[9]);
        glDrawElements(GL_TRIANGLES, 55, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(3, VAO);
    glDeleteBuffers(3, VBO);
    glDeleteBuffers(1, &*EBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);



}