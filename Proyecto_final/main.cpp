/*
ALUMNA: YAHAIRA GOMEZ SUCASACA
CURSO: COMPUTACIÓN GRÁFICA
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "shader_s.h"
#include "Rubik.hpp"
#include "camera.h"
#include "Particula.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <string.h>
#include <Windows.h>

#include <iostream>
#include <random>
#include <iomanip>

using std::cout;
using std::endl;
using std::setprecision;

constexpr int FLOAT_MIN = 0;
constexpr int FLOAT_MAX = 1;

using namespace std;
using namespace glm;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
//CubeUp is to know if increase scale or reduce

string mainPath = "C:\\Users\\Valeria\\Documents\\CCOMP2-2021\\COMPUTACION GRAFICA\\Shared_Students_CG\\ProjectBaseOpenGL\\GLFW_GLAD_GLUT_GLEW_cmake_project\\src\\PROYECTO_FINAL\\";
unsigned int textures[6];



unsigned int VBO[27], VAO[27];

//L AMARILLO        R BLANCO         B AZUL         F VERDE          D NARANJA        U ROJO
vector<vector<float>> colores = { {1.0, 1.0, 0.0}, {1.0,1.0,1.0},{0.0, 0.0, 1.0},{0.0, 1.0, 0.0},{1.0, 0.647, 0.0}, {1.0, 0.0, 0.0} };


// camera
Camera camera(glm::vec3(5.0f, 5.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;


float espacioCub = 1.1;      //intervalo entre cubos
bool presionado = false;
vector<float> vertices0 = {
    //CARAS DE ABAJO
    -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,      1.0f, 0.0f,      //A
     0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,      0.0f, 0.0f,      //B               
     0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,      0.0f, 1.0f,      //C   

     0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,      0.0f, 1.0f,       // C  
    -0.5f,  0.5f, -0.5f,    0.0,0.0, 0.0,      1.0f, 1.0f,       //D
    -0.5f, -0.5f, -0.5f,    0.0,0.0, 0.0,      1.0f, 0.0,       //A

    //CARAS ARRIBA  
    -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,      // D
     0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,      1.0f, 0.0f,       //  E                  
     0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,      //   F   

     0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,      //F
    -0.5f,  0.5f,  0.5f,    0.0,0.0, 0.0,     1.0f, 1.0f,       //G
    -0.5f, -0.5f,  0.5f,    0.0,0.0, 0.0,     0.0f, 0.0f,       //D


    //CARAS ATRAS
    -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,  //
    -0.5f,  0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,     0.0,0.0, 0.0,     1.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,     0.0,0.0, 0.0,     0.0f, 1.0f,


    //CARAS FRENTE
     0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,      0.0,0.0, 0.0,      0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,

     0.5f,  0.5f,  0.5f,      0.0,0.0, 0.0,      0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,      0.0,0.0, 0.0,      1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,      0.0,0.0, 0.0,    1.0f, 0.0,


     //CARAS IZQUIERDA
    -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,      1.0f, 0.0f,
     0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,

     0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,

    //CARAS DERECHA
    -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,       0.0,0.0, 0.0,     1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,       0.0,0.0, 0.0,     0.0f, 1.0f
};

int getIndex(char side) {
    int ind;
    switch (side) {
    case 'D':
        ind = 0;
        break;
    case 'U':
        ind = 1;
        break;
    case 'B':
        ind = 2;
        break;
    case 'F':
        ind = 3;
        break;
    case 'L':
        ind = 4;
        break;
    case 'R':
        ind = 5;
        break;
    default:
        ind = -1;
        break;
    }
    return ind;
}


//VELOCIDAD DE GIRO
int speed = 100;
float angulo = 90.0f;


//Para girar a cada cubito en rotate_all_face
void rotar_cubie(mat4& model, vec3 val) {
    mat4 nuevo(1.0f);
    nuevo = glm::rotate(nuevo, glm::radians(angulo / speed), val);
    model = nuevo * model;
}
void menu() {
    cout << "\t\tCUBO DE RUBICK\n  :" << endl;
    cout << "Presiona la tecla: " << endl;
    cout << "W:       para acercarte" << endl;
    cout << "S:       para alejarte" << endl;
    cout << "A:       para mover la camara a la izquierda" << endl;
    cout << "D:       para mover la camara a la derecha" << endl;
    cout << "Q:       para mover la camara hacia arriba" << endl;
    cout << "E:       para mover la camara hacia abajo" << endl;
    cout << endl;

    cout << "GIROS DE LAS CARAS: " << endl;
    cout << "  En sentido horario: " << endl;
    cout << "   F:       para mover la cara amarilla" << endl;
    cout << "   G:       para mover la cara blanca" << endl;
    cout << "   H:       para mover la cara azul" << endl;
    cout << "   J:       para mover la cara verde" << endl;
    cout << "   K:       para mover la cara naranja" << endl;
    cout << "   L:       para mover la cara roja" << endl;
    cout << "  En sentido antihorario: " << endl;
    cout << "   Z:       para mover la cara amarilla" << endl;
    cout << "   X:       para mover la cara blanca" << endl;
    cout << "   C:       para mover la cara azul" << endl;
    cout << "   V:       para mover la cara verde" << endl;
    cout << "   B:       para mover la cara naranja" << endl;
    cout << "   N:       para mover la cara roja" << endl;


    cout << "ANIMACIONES: " << endl;
    cout << "P:       para resolver el cubo" << endl;
    cout << "M:       para apreciar la animacion" << endl;
    
}

class cubie
{
public:
    unsigned int idVAO;
    mat4 model;
    vec3 setPunt_ini;
    vector<float> vertices;
    vector<bool> carasActivas;                      //D U B F L R
    vector<int> carasColores;                       //D U B F L R           cada uno con su colo, -1 si no tiene color
    vec3 direccion;
    cubie(vec3 point, int id);
    void configVertex();                                //configura el VAO, VBO
    void drawing(Shader* myShader);                     //dibuja el cubie
    int indexCaras(char side);                          //coloca true en el vector y te devuelve el índice
    void setColors();

    //NUEVO
    void setTextures(int indexCara, int index);
};

cubie::cubie(vec3 point, int id) {
    idVAO = id;
    //seteo punto inicial de mi cubito
    setPunt_ini = point;
    //seteo la matriz model para que pueda mover a mi cubito
    model = mat4(1.0f);

    //muevo mi cubito a ese punto inicial
    model = glm::translate(model, setPunt_ini);

    vertices = vertices0; //para darle color de forma particular a cada cubo

    carasActivas.resize(6);
    fill(carasActivas.begin(), carasActivas.end(), false);

    //inicializando carasColores en -1
    vector<int> carasColoresTemp(6, -1);
    carasColores = carasColoresTemp;

    direccion = vec3(0.0, 0.0, 0.0);
}

void cubie::drawing(Shader* myShader) {

    //Uso la matriz de mi shader para mover a mis cubitos, trabajo con model
    myShader->setMat4("model", model);

    //NUEVO
    int in = 0;
    glBindVertexArray(VAO[idVAO]);
    for (int i = 0; i < 36; i += 6) {
        glBindTexture(GL_TEXTURE_2D, textures[in]);
        myShader->setInt("texture1", in);
        textures[in++];
        glDrawArrays(GL_TRIANGLES, i, 6);

    }
    configVertex();
}

int cubie::indexCaras(char side) {
    int ind;
    switch (side) {
    case 'D':
        ind = 0;
        break;
    case 'U':
        ind = 1;
        break;
    case 'B':
        ind = 2;
        break;
    case 'F':
        ind = 3;
        break;
    case 'L':
        ind = 4;
        break;
    case 'R':
        ind = 5;
        break;
    default:
        ind = -1;
        break;
    }
    carasActivas[ind] = true;
    carasColores[ind] = ind;
    return ind;
}


void cubie::setColors() {
    for (int i = 0; i < carasColores.size(); i++) {     //Evaluo todas las caras
        if (carasColores[i] != -1) {        //si es diferente a negro, aun no hemos pintado
            //cambiando los colores de los 6 vértices que conforman una cara
            int indice = i * 6; //Coloco en la fila inicial de la cara 
            indice *= 8;    //Cada fila tiene 8 vertices 
            indice += 3;   //Para dibujar los cubitos en cada fila
            //cambiando los colores  en las 6 filas que pertenecen a la cara, empiezo en 0 y luego voy por el otro cubito adyacente
            for (int j = 0; j < 6; j++, indice += 8) {
                vertices[indice] = colores[carasColores[i]][0];
                vertices[indice + 1] = colores[carasColores[i]][1];
                vertices[indice + 2] = colores[carasColores[i]][2];

            }
        }
    }

}


void cubie::setTextures(int indexCara, int index)       //indexCara es la cara a la que pertenece, index es el nro de cubo
{
    vector<vector<pair<float, float>>> texturas;
    if (indexCara == 0 || indexCara == 3) {
        texturas = {
                { make_pair(1.0f , 0.0f),make_pair(1.0f , 0.333f),make_pair(0.666f , 0.0f),  make_pair(0.666f , 0.333f) },         //6
                { make_pair(0.333f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.666f , 0.0f),make_pair(0.666f , 0.333f)  },     //3
                { make_pair(0.333f, 0.0f),make_pair(0.333f, 0.333f),make_pair(0.0f, 0.0f),  make_pair(0.0f, 0.333f) },       //0
                { make_pair(1.0f , 0.333f), make_pair(1.0f , 0.666f), make_pair(0.666f , 0.333f),  make_pair(0.666f , 0.666f) },     //7
                { make_pair(0.666f , 0.333f), make_pair(0.666f , 0.666f),make_pair(0.333f , 0.333f),  make_pair(0.333f , 0.666f) },     //4
                { make_pair(0.333f , 0.333f), make_pair(0.333f , 0.666f),make_pair(0.0f , 0.333f),  make_pair(0.0f , 0.666f) },     //1                
                { make_pair(1.0f , 0.666f), make_pair(1.0f , 1.0f), make_pair(0.666f , 0.666f),  make_pair(0.666f , 1.0f) },          //8
                { make_pair(0.666f , 0.666f),make_pair(0.666f , 1.0f), make_pair(0.333f , 0.666f),  make_pair(0.333f , 1.0f) },         //5
                { make_pair(0.333f , 0.666f), make_pair(0.333f , 1.0f), make_pair(0.0f , 0.666f),  make_pair(0.0f , 1.0f) },         //2


        };

    }
    else {
        if (indexCara == 5) {
            texturas = {
            {    make_pair(0.333f, 0.333f), make_pair(0.0f, 0.333f),make_pair(0.333f, 0.0f), make_pair(0.0f, 0.0f)},
            {  make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f),make_pair(0.333f , 0.333f),make_pair(0.0f , 0.333f) },
            {   make_pair(0.333f , 1.0f),make_pair(0.0f , 1.0f),make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f) },

            { make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f),make_pair(0.666f , 0.0f),make_pair(0.333f , 0.0f)    },
            {  make_pair(0.666f , 0.666f),make_pair(0.333f , 0.666f),make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f)  },
            {  make_pair(0.666f , 1.0f), make_pair(0.333f , 1.0f),make_pair(0.666f , 0.666f), make_pair(0.333f , 0.666f) },

            { make_pair(1.0f , 0.333f),make_pair(0.666f , 0.333f),make_pair(1.0f , 0.0f),make_pair(0.666f , 0.0f) },
            {  make_pair(1.0f , 0.666f), make_pair(0.666f , 0.666f),make_pair(1.0f , 0.333f), make_pair(0.666f , 0.333f) },
            { make_pair(1.0f , 1.0f), make_pair(0.666f , 1.0f),make_pair(1.0f , 0.666f),make_pair(0.666f , 0.666f) }
            };
        }
        else {
            if (indexCara == 1) {
                texturas = {
                { make_pair(0.666f , 0.0f),  make_pair(0.666f , 0.333f),make_pair(1.0f , 0.0f),make_pair(1.0f , 0.333f) },         //6

                { make_pair(0.666f , 0.0f),make_pair(0.666f , 0.333f),make_pair(0.333f , 0.0f), make_pair(0.333f , 0.333f)  },     //3
                { make_pair(0.0f, 0.0f),  make_pair(0.0f, 0.333f),make_pair(0.333f, 0.0f),make_pair(0.333f, 0.333f) },       //0


                { make_pair(0.666f , 0.333f),  make_pair(0.666f , 0.666f),make_pair(1.0f , 0.333f), make_pair(1.0f , 0.666f) },     //7
                { make_pair(0.333f , 0.333f),  make_pair(0.333f , 0.666f),make_pair(0.666f , 0.333f), make_pair(0.666f , 0.666f) },     //4
                { make_pair(0.0f , 0.333f),  make_pair(0.0f , 0.666f),make_pair(0.333f , 0.333f), make_pair(0.333f , 0.666f) },     //1                

                { make_pair(0.666f , 0.666f),  make_pair(0.666f , 1.0f), make_pair(1.0f , 0.666f), make_pair(1.0f , 1.0f) },          //8
                { make_pair(0.333f , 0.666f),  make_pair(0.333f , 1.0f),make_pair(0.666f , 0.666f),make_pair(0.666f , 1.0f) },         //5
                { make_pair(0.0f , 0.666f),  make_pair(0.0f , 1.0f),make_pair(0.333f , 0.666f), make_pair(0.333f , 1.0f) },         //2


                };
            }
            else {
                if (indexCara == 2) {
                    texturas = {
                { make_pair(0.666f , 0.333f),make_pair(0.666f , 0.0f),make_pair(1.0f , 0.333f),make_pair(1.0f , 0.0f) },         //6

                {make_pair(0.666f , 0.333f), make_pair(0.666f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.333f , 0.0f)  },     //3
                {   make_pair(0.0f, 0.333f),make_pair(0.0f, 0.0f),make_pair(0.333f, 0.333f), make_pair(0.333f, 0.0f) },       //0


                { make_pair(0.666f , 0.666f),make_pair(0.666f , 0.333f), make_pair(1.0f , 0.666f),make_pair(1.0f , 0.333f) },     //7
                {   make_pair(0.333f , 0.666f),make_pair(0.333f , 0.333f), make_pair(0.666f , 0.666f),make_pair(0.666f , 0.333f) },     //4
                {   make_pair(0.0f , 0.666f),make_pair(0.0f , 0.333f), make_pair(0.333f , 0.666f),make_pair(0.333f , 0.333f) },     //1                

                {   make_pair(0.666f , 1.0f),make_pair(0.666f , 0.666f), make_pair(1.0f , 1.0f), make_pair(1.0f , 0.666f) },          //8
                {   make_pair(0.333f , 1.0f),make_pair(0.333f , 0.666f),make_pair(0.666f , 1.0f),make_pair(0.666f , 0.666f) },         //5
                {   make_pair(0.0f , 1.0f),make_pair(0.0f , 0.666f), make_pair(0.333f , 1.0f),make_pair(0.333f , 0.666f) },         //2


                    };
                }
                else {
                    texturas = {
                    { make_pair(1.0f , 0.0f),make_pair(0.666f , 0.0f),  make_pair(1.0f , 0.333f),make_pair(0.666f , 0.333f) },         //6

                    { make_pair(0.333f , 0.0f),make_pair(0.666f , 0.0f), make_pair(0.333f , 0.333f),make_pair(0.666f , 0.333f)  },     //3
                    { make_pair(0.333f, 0.0f),make_pair(0.0f, 0.0f),make_pair(0.333f, 0.333f),  make_pair(0.0f, 0.333f) },       //0


                    { make_pair(1.0f , 0.333f), make_pair(0.666f , 0.333f), make_pair(1.0f , 0.666f),  make_pair(0.666f , 0.666f) },     //7
                    { make_pair(0.666f , 0.333f),make_pair(0.333f , 0.333f), make_pair(0.666f , 0.666f),  make_pair(0.333f , 0.666f) },     //4
                    { make_pair(0.333f , 0.333f),make_pair(0.0f , 0.333f), make_pair(0.333f , 0.666f),  make_pair(0.0f , 0.666f) },     //1                

                    {  make_pair(1.0f , 0.666f), make_pair(0.666f , 0.666f), make_pair(1.0f , 1.0f),  make_pair(0.666f , 1.0f) },          //8
                    {make_pair(0.666f , 0.666f),make_pair(0.333f , 0.666f),make_pair(0.666f , 1.0f),   make_pair(0.333f , 1.0f) },         //5
                    {make_pair(0.333f , 0.666f), make_pair(0.0f , 0.666f), make_pair(0.333f , 1.0f),   make_pair(0.0f , 1.0f) },         //2


                    };
                }
            }

        }
    }

    int indice = indexCara * 6; //colocando en la fila inicial de la cara   0 - 6 - 12 - ... - 30
    indice *= 8;    //colocando el índice correcto, ya que cada fila tiene 8 vértices.
    indice += 6;   //colocandolo en el primer color
    //cambiando los colores  en las 6 filas que pertenecen a la cara    estan en el índice  3(empezando con 0)
    vertices[indice] = texturas[index][0].first;            //I1
    vertices[indice + 1] = texturas[index][0].second;

    indice += 8;

    vertices[indice] = texturas[index][2].first;            //D1
    vertices[indice + 1] = texturas[index][2].second;

    indice += 8;

    vertices[indice] = texturas[index][3].first;            //I2
    vertices[indice + 1] = texturas[index][3].second;

    indice += 8;

    vertices[indice] = texturas[index][3].first;            //I2
    vertices[indice + 1] = texturas[index][3].second;

    indice += 8;

    vertices[indice] = texturas[index][1].first;            //D2
    vertices[indice + 1] = texturas[index][1].second;

    indice += 8;

    vertices[indice] = texturas[index][0].first;            //I1
    vertices[indice + 1] = texturas[index][0].second;
}



void cubie::configVertex() {
    glBindVertexArray(VAO[idVAO]);

    glBindBuffer(GL_ARRAY_BUFFER, VBO[idVAO]);
    glBufferData(GL_ARRAY_BUFFER, vertices0.size() * sizeof(float), &vertices.front(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color  attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}



class RubikCube
{
public:
    cubie* cubos[27];
    vector<vector<cubie*>> caras;                           //D U B F L R
    Shader* myShader;
    RubikCube(Shader& nuevo);
    void setInitialPoints();
    void drawing();

    //AVANCE
    int contador = 0;
    //PARA MOVER CARAS
    void setRotation(bool clock, int face);
    //PARA MOVER CARAS DEL CUBO
    void insertRotate(bool clock, int face);
    bool busy;

    //PARA VER SI ESTÁ ANIMANDO Y QUÉ CARA
    vector<pair<bool, bool>> face_state_direction;                    //clock? , animation?
    void rotate_all_face();

    //SENTIDOS DE GIRO
    void reloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices);    //cambiar en orden del reloj
    void contrarreloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices);


    //AVANCE SOLVING
    string solving;
    string disordered;
    bool solved, proceso;
    void solvingCube();
    void solve();

    void running();


private:

};
RubikCube* cuboPrincipal;


RubikCube::RubikCube(Shader& nuevo) {
    myShader = &nuevo;
    int carasCubo = 6, cubieCub = 9;
    //MATRIZ DE CUBITOS, manos a la obra
    vector<vector<cubie*>> matrix(carasCubo, vector<cubie*>(cubieCub));
    caras = matrix;

    //PARA NO PERDER LOS VERTICES ANTIGUOS DE CUBITOS
    vector<pair<bool, bool>> animacionesTemp(6, make_pair(false, false));
    face_state_direction = animacionesTemp;
    solved = true;
    proceso = false;
    busy = false;
   

    //empiezo a crear cubitos
    setInitialPoints();

}


void RubikCube::setInitialPoints() {
    //punto inicial de donde se dibuja
    vec3 init = vec3(-1.1, -1.1, -1.1);
    vector<vec3> puntos;
    vec3 capa = init;

    //generando 3 matrices de 3 x 3 para el cubo
    for (int k = 0; k < 3; k++) {
        vec3 fila = capa;
        for (int j = 0; j < 3; j++) {
            puntos.push_back(fila);
            vec3 columna = fila;
            //creando dos cubos avanzando en eje x
            for (int i = 0; i < 2; i++) {
                //avanza la columna
                columna = columna + vec3(espacioCub, 0.0, 0.0);
                puntos.push_back(columna);
            }
            fila = fila + vec3(0.0, espacioCub, 0.0);
        }
        capa = capa + vec3(0.0, 0.0, espacioCub);
    }

    //Creando 27 cubos pequeños
    for (int i = 0; i < puntos.size(); i++) {
        cubos[i] = new cubie(puntos[i], i);
    }

    //Colocando que tienen el lado Down activo      0 1 2 3 4 5... 8
    char lado = 'D';
    for (int i = 0, cont = 0; i < 9; i++, cont++) {
        cubos[i]->indexCaras(lado);
    }

    //Colocando que tienen el lado Up activo
    lado = 'U';
    for (int i = 18, cont = 0; i < 27; i++, cont++) {
        cubos[i]->indexCaras(lado);
    }

    //Colocando que tienen el lado Bot activo
    lado = 'B';
    for (int i = 0, cont = 0; i < 27; i += 3, cont++) {
        cubos[i]->indexCaras(lado);
    }

    //Colocando que tienen el lado Front activo
    lado = 'F';
    for (int i = 2, cont = 0; i < 27; i += 3, cont++) {
        cubos[i]->indexCaras(lado);
    }

    //Colocando que tienen el lado Left activo
    lado = 'L';
    for (int i = 0, cont = 0; i < 27; i += 9, cont++) {
        cubos[i]->indexCaras(lado);
        cubos[i + 1]->indexCaras(lado);
        cubos[i + 2]->indexCaras(lado);
    }

    //Colocando que tienen el lado Right activo
    lado = 'R';
    for (int i = 6, cont = 0; i < 27; i += 9, cont++) {
        cubos[i]->indexCaras(lado);
        cubos[i + 1]->indexCaras(lado);
        cubos[i + 2]->indexCaras(lado);
    }

    //Colocando los colores correctos de cada cubo  en los vértices (iniciaban con negro todos sus lados)
    for (int i = 0; i < 27; i++) {
        cubos[i]->setColors();
    }

    //colocar en orden los cubos en cada cara
    //DOWN
    caras[0][0] = cubos[0];
    caras[0][1] = cubos[1];
    caras[0][2] = cubos[2];
    caras[0][3] = cubos[3];
    caras[0][4] = cubos[4];
    caras[0][5] = cubos[5];
    caras[0][6] = cubos[6];
    caras[0][7] = cubos[7];
    caras[0][8] = cubos[8];

    //UP
    caras[1][0] = cubos[20];
    caras[1][1] = cubos[19];
    caras[1][2] = cubos[18];
    caras[1][3] = cubos[23];
    caras[1][4] = cubos[22];
    caras[1][5] = cubos[21];
    caras[1][6] = cubos[26];
    caras[1][7] = cubos[25];
    caras[1][8] = cubos[24];

    //BOT
    caras[2][0] = cubos[18];
    caras[2][1] = cubos[9];
    caras[2][2] = cubos[0];
    caras[2][3] = cubos[21];
    caras[2][4] = cubos[12];
    caras[2][5] = cubos[3];
    caras[2][6] = cubos[24];
    caras[2][7] = cubos[15];
    caras[2][8] = cubos[6];

    //FRONT
    caras[3][0] = cubos[2];
    caras[3][1] = cubos[11];
    caras[3][2] = cubos[20];
    caras[3][3] = cubos[5];
    caras[3][4] = cubos[14];
    caras[3][5] = cubos[23];
    caras[3][6] = cubos[8];
    caras[3][7] = cubos[17];
    caras[3][8] = cubos[26];

    //LEFT
    caras[4][0] = cubos[0];
    caras[4][1] = cubos[9];
    caras[4][2] = cubos[18];
    caras[4][3] = cubos[1];
    caras[4][4] = cubos[10];
    caras[4][5] = cubos[19];
    caras[4][6] = cubos[2];
    caras[4][7] = cubos[11];
    caras[4][8] = cubos[20];

    //RIGHT
    caras[5][0] = cubos[26];
    caras[5][1] = cubos[25];
    caras[5][2] = cubos[24];
    caras[5][3] = cubos[17];
    caras[5][4] = cubos[16];
    caras[5][5] = cubos[15];
    caras[5][6] = cubos[8];
    caras[5][7] = cubos[7];
    caras[5][8] = cubos[6];

    for (int i = 0; i < caras.size(); i++) {
        for (int j = 0; j < caras[i].size(); j++) {
            caras[i][j]->setTextures(i, j);
        }
    }

    vector<vec3>direcciones = { vec3(0.0, 0.0, -1.0) ,vec3(0.0, 0.0, 1.0),vec3(-1.0, 0.0, 0.0),vec3(1.0, 0.0, 0.0),vec3(0.0, -1.0, 0.0),vec3(0.0, 1.0, 0.0) };
    for (int i = 0; i < caras.size(); i++) {
        for (int j = 0; j < caras[i].size(); j++) {
            caras[i][j]->direccion = vec3(caras[i][j]->direccion.x + direcciones[i].x, caras[i][j]->direccion.y + direcciones[i].y, caras[i][j]->direccion.z + direcciones[i].z);
        }
    }

}

void RubikCube::drawing() {
    for (int i = 0; i < 27; i++) {
        //Sleep(50);
        cubos[i]->drawing(myShader);
    }
}


//ROTAR EN QUÉ SENTIDO Y QUÉ CARA
void RubikCube::setRotation(bool clock, int face) {
    if (busy) {
        return;
    }
    face_state_direction[face].first = clock;        //HORARIO
    face_state_direction[face].second = true;          //REALIZANDO ANIMACION
    busy = true;

}



void RubikCube::rotate_all_face() {

    vector<vec3> direcciones(6);                       //   D                B           F       L           R      INDICES
    vector< vector<int>> facesAroundIndex = {
        {0, 3, 6, 6, 7, 8, 8, 5, 2, 0, 3, 6},          //D  0
        {0, 3, 6, 2, 1, 0, 8, 5, 2, 8, 5, 2},          //U  1
        {0, 3, 6, 8, 5, 2, 8, 5, 2, 2, 1, 0},          //B  2
        {0, 3, 6, 0, 3, 6, 8, 5, 2, 6, 7, 8},          //F  3
        {2, 1, 0, 2, 1, 0, 2, 1, 0, 2, 1, 0},          //L  4
        {6, 7, 8, 6, 7, 8, 6, 7, 8, 6, 7, 8} };        //R  5

    vector< vector<int>> facesAround = {
        {3,5,2,4},     //D
        {2,5,3,4},     //U
        {0,5,1,4},     //B
        {1,5,0,4},     //F
        {1,3,0,2},     //L
        {2,0,3,1}      //R
    };



    for (int j = 0; j < face_state_direction.size(); j++) {
        if (face_state_direction[j].second == true) {        //ESTA OCUPADO ANIMANDO

            if (face_state_direction[j].first == true) {
                //GENERO UN VECTOR DE DIRECCIONES PARA MOVER CADA CARA
                direcciones = { vec3(0.0, 0.0, 1.0) ,vec3(0.0, 0.0, -1.0),vec3(1.0, 0.0, 0.0),vec3(-1.0, 0.0, 0.0),vec3(0.0, 1.0, 0.0),vec3(0.0, -1.0, 0.0) };
            }
            else {
                direcciones = { vec3(0.0, 0.0, -1.0) ,vec3(0.0, 0.0, 1.0),vec3(-1.0, 0.0, 0.0),vec3(1.0, 0.0, 0.0),vec3(0.0, -1.0, 0.0),vec3(0.0, 1.0, 0.0) };
            }


            //RECORRO LOS CUBOS DE CADA CARA en total 9 
            for (int i = 0; i < caras[j].size(); i++) {
                //ROTO CADA CUBITO DE CADA CARA Y LO VUELVO A DIBUJAR
                rotar_cubie(caras[j][i]->model, direcciones[j]);
                caras[j][i]->configVertex();
                caras[j][i]->drawing(myShader);

            }

            //cout << "contador: " << contador<< endl;
            contador++;

            // }
            if (contador == speed) {
                if (face_state_direction[j].first == true) {     //is is clock
                    reloj(caras[j], caras[facesAround[j][0]], caras[facesAround[j][1]], caras[facesAround[j][2]], caras[facesAround[j][3]], facesAroundIndex[j]);
                }
                else {
                    contrarreloj(caras[j], caras[facesAround[j][0]], caras[facesAround[j][1]], caras[facesAround[j][2]], caras[facesAround[j][3]], facesAroundIndex[j]);
                }
                contador = 0;
                presionado = false;
                face_state_direction[j].second = false;      //animation set false
                busy = false;


            }
        }
    }
}

//ROTACION EN 4 CARAS Y 1 DONDE GIRA
void RubikCube::reloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices) {
    vector<cubie*> temp(9);

    //COMO QUEDA EL CUBO SI GIRO EN SENTIDO HORARIO
    vector<int> index = {
        //2,5,8,1,4,7,0,3,6             //CONTRARELOJ
        6,3,0,7,4,1,8,5,2               //RELOJ
    };
    //CAMBIO EL ORDEN DE LOS CUBOS DE LA CARA COMPLETA DESPUÉS DE DAR LA VUELTA
    for (int i = 0; i < index.size(); i++) {
        temp[i] = cara[index[i]];
    }
    cara = temp;
    //LO MISMO PERO PARA LOS CUBITOS CHIQUITOS
    vector<cubie*> cara1Temp = cara1, cara2Temp = cara2, cara3Temp = cara3, cara4Temp = cara4;

    //ROTO, CAMBIO DE POSICIONES
    //cara 1 recibe 3 cubitos de la cara 4
    cara1Temp[indices[0]] = cara4[indices[9]];
    cara1Temp[indices[1]] = cara4[indices[10]];
    cara1Temp[indices[2]] = cara4[indices[11]];
    //cara 2 recibe 3 cubitos de la cara 1
    cara2Temp[indices[3]] = cara1[indices[0]];
    cara2Temp[indices[4]] = cara1[indices[1]];
    cara2Temp[indices[5]] = cara1[indices[2]];
    //cara 3 recibe 3 cubitos de la cara 2
    cara3Temp[indices[6]] = cara2[indices[3]];
    cara3Temp[indices[7]] = cara2[indices[4]];
    cara3Temp[indices[8]] = cara2[indices[5]];
    //cara 4 recibe 3 cubitos de la cara 3
    cara4Temp[indices[9]] = cara3[indices[6]];
    cara4Temp[indices[10]] = cara3[indices[7]];
    cara4Temp[indices[11]] = cara3[indices[8]];

    cara1 = cara1Temp;
    cara2 = cara2Temp;
    cara3 = cara3Temp;
    cara4 = cara4Temp;

}

void RubikCube::contrarreloj(vector<cubie*>& cara, vector<cubie*>& cara1, vector<cubie*>& cara2, vector<cubie*>& cara3, vector<cubie*>& cara4, vector<int> indices) {
    vector<cubie*> temp(9);
    vector<int> index = {
       2,5,8,1,4,7,0,3,6             //CONTRARELOJ
       //6,3,0,7,4,1,8,5,2               //RELOJ
    };
    //CAMBIO EL ORDEN DE LOS CUBOS DE LA CARA COMPLETA DESPUÉS DE DAR LA VUELTA
    for (int i = 0; i < index.size(); i++) {
        temp[i] = cara[index[i]];
    }
    cara = temp;
    vector<cubie*> cara1Temp = cara1, cara2Temp = cara2, cara3Temp = cara3, cara4Temp = cara4;

    //ROTO, CAMBIO DE POSICIONES
    //cara 1 recibe 3 cubitos de la cara 2
    cara1Temp[indices[0]] = cara2[indices[3]];
    cara1Temp[indices[1]] = cara2[indices[4]];
    cara1Temp[indices[2]] = cara2[indices[5]];
    //cara 2 recibe 3 cubitos de la cara 3
    cara2Temp[indices[3]] = cara3[indices[6]];
    cara2Temp[indices[4]] = cara3[indices[7]];
    cara2Temp[indices[5]] = cara3[indices[8]];
    //cara 3 recibe 3 cubitos de la cara 4
    cara3Temp[indices[6]] = cara4[indices[9]];
    cara3Temp[indices[7]] = cara4[indices[10]];
    cara3Temp[indices[8]] = cara4[indices[11]];
    //cara 4 recibe 3 cubitos de la cara 1
    cara4Temp[indices[9]] = cara1[indices[0]];
    cara4Temp[indices[10]] = cara1[indices[1]];
    cara4Temp[indices[11]] = cara1[indices[2]];




    cara1 = cara1Temp;
    cara2 = cara2Temp;
    cara3 = cara3Temp;
    cara4 = cara4Temp;

}


//LE PASAMOS UN STRING DEL ESTADO ACTUAL DEL CUBO Y EN BASE A ESO RESUELVE
//EVALÚA LETRA POR LETRA 
void RubikCube::solvingCube() {
    if (!busy && proceso) {
        if (solving.empty()) {   //SI ESTÁ VACÍO TERMINÓ DE RESOLVER
            proceso = false;        //ACABO
            solved = true;          //RESUELTO
        }
        else {
            //ONE MOVIMIENTO
            if (solving[0] == ' ') {        // " "
                solving = solving.substr(1);
                return;
            }
            //+ DE UN MOVIMIENTO -> ESTOY LEYENDO UNA LETRA -> GIRO
            if (solving[1] == ' ') {        //  "U"
                setRotation(true, getIndex(solving[0]));        //girar sentido horario
                solving = solving.substr(2);
                return;
            }

            //SI ES \ ES ANTIHORARIO
            if (solving[1] == '\'') {        //  "U'"
                setRotation(false, getIndex(solving[0]));       //girar sentido antihorario
                solving = solving.substr(3);
                return;
            }

            //DOBLE ROTACIÓN
            if (solving[1] == '2') {        //  "U2 "
                char temp = solving[0];
                solving = solving.substr(1);
                solving[0] = temp;
                setRotation(true, getIndex(solving[0]));        //girar sentido horario
                return;
            }

        }
    }

}
void RubikCube::solve()
{
    if (proceso || busy) {      // ESTOY RESOLVIENDO!!
        return;
    }

    //SI DEJA DE ESTAR DESORDENADO -> YA RESOLVÍ
    if (disordered.empty()) {
        solved = true;
        proceso = false;
    }

    else {
        proceso = true;
        solved = false;

        solving = Rubik::solve(disordered);
        disordered = "";
        cout << "Solving " << endl;
    }
}

void RubikCube::running()
{
    solvingCube();
    rotate_all_face();
  

}

void RubikCube::insertRotate(bool clock, int face)
{
    if (busy || proceso)       //si está ocupado animando alguna cara no lo hace
        return;

    vector<char> ffaces = { 'D', 'U', 'B', 'F', 'L', 'R' };
    if (clock) {
        disordered.push_back(ffaces[face]);
        disordered.push_back(' ');
    }
    else {
        disordered.push_back(ffaces[face]);
        disordered.push_back('\'');
    }
    setRotation(clock, face);
}

string condition_input = "N";

struct estrella {
    //VELOCIDAD DE SALIDA
    float velocidad_animacion = 0.01;
    int movimientos = 0;
    string ini = "M";

    vector <float> vertices_estrella{
        -0.6,  0,    0,       //A
        -0.4,      0.5,      0,                 //B
        -0.2,   0,    0,
        0.6,      0,    0,
        -0.01,    -0.4,   0,
        0.3,    -1.1,   0,
        -0.4,      -0.7,  0,
        -1.1,   -1.1,   0,
        -0.8,   -0.4,   0,
        -1.4,     0,    0,
        -0.6,  0,    0,
    };


    Particula* pol_estrella;
    estrella(float R, float G, float B) {
        pol_estrella = new Particula(this->vertices_estrella, R, G, B);
        //cout << "estrella creada " << endl;
    }
    
    string animacion_estrella(int pos_negativo, string eje) {
        if (ini == "M") {
            if (movimientos != 500) {
                pol_estrella->translateF(0, velocidad_animacion, 0);
                movimientos += 1;
                return "M";
            }
            movimientos = 0;
            velocidad_animacion = 0.2;
           
            return "G";
        }
        if (ini == "G") {
            if (movimientos < 500) {
                if (eje == "X") {
                    pol_estrella->rotation_x(pos_negativo * velocidad_animacion);
                }
                if (eje == "Z") {
                    pol_estrella->rotation_z(pos_negativo * velocidad_animacion);
                }
                movimientos += 1;
                return "G";
            }
            movimientos = 0;
            velocidad_animacion = 0.01;
           
            return "B";
        }
        if (ini == "B") {
            if (movimientos != 100) {
                pol_estrella->translateF(0, -velocidad_animacion, 0);
                movimientos += 1;
                return "B";
            }
            //cout << "ya acabo TERCERO" << endl;
            return "N";
        }
    }
    void draw(GLFWwindow* window) {
        pol_estrella->draw(window, true);
        
    }
};
int pos_vect_estrellas = 0;


vector<estrella*> estrellas;
float random() {
    std::random_device rd;
    std::default_random_engine eng(rd());
    std::uniform_real_distribution<float> distr(FLOAT_MIN, FLOAT_MAX);
    setprecision(1);

    return distr(eng);
}

int main()
{
    estrellas.reserve(12);
    float R, G, B;
    for (int i = 0; i < 12; ++i) {
        R = random();
        G = random();
        B = random();

        estrella* estrellas_point = new estrella(R,G,B);
        estrellas.push_back(estrellas_point);
    }
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    glfwSetWindowPos(window, 800, 100);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);


    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    string vs = mainPath + "3.3.shader.vs", fs = mainPath + "3.3.shader.fs";
    Shader ourShader(vs.c_str(), fs.c_str());


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------



    //unsigned int VBO[3], VAO[3];
    glGenVertexArrays(27, VAO);
    glGenBuffers(27, VBO);



    //TEXTURAS
    vector<string> nombresTexturas = {
        "U.jpg",
        "G.jpg",
        "S.jpg",
        "P.jpg",
        "C.jpg",
        "C.jpg",

    };

    for (int i = 0; i < 6; i++) {
        glGenTextures(1, &textures[i]);
        //ENLAZO TEXTURAS
        glBindTexture(GL_TEXTURE_2D, textures[i]);

        int width, height, nrChannels;
        //PARA QUE NO SE INVIERTA
        stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.

        //ACCEDO A LAS FIGURAS QUE USARÉ COMO TEXTURAS
        string path = mainPath + nombresTexturas[i];
        //CARGO LAS FIGURAS CON SU WIDTH Y HEIGHT
        unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

    }


    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();



    RubikCube CUBOOS(ourShader);

    cuboPrincipal = &CUBOOS;

    menu();

    int val = 0;
    while (!glfwWindowShouldClose(window))
    {

        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textures[0]);
        //draw
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, textures[1]);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, textures[2]);
        glActiveTexture(GL_TEXTURE3);
        glBindTexture(GL_TEXTURE_2D, textures[3]);
        glActiveTexture(GL_TEXTURE4);
        glBindTexture(GL_TEXTURE_2D, textures[4]);
        glActiveTexture(GL_TEXTURE5);
        glBindTexture(GL_TEXTURE_2D, textures[5]);


        // activate shader
        ourShader.use();

        // pass projection matrix to shader (note that in this case it could change every frame)
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourShader.setMat4("projection", projection);

        // camera/view transformation|
        glm::mat4 view = camera.GetViewMatrix();
        ourShader.setMat4("view", view);

        CUBOOS.running(); // mover 5 grados

        CUBOOS.drawing();


        //glDrawArrays(GL_TRIANGLE_FAN, 0, 4);   
        CUBOOS.drawing();
        for (int i = 0; i < 11; ++i) {
            estrellas[i]->draw(window);
        }



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(27, VAO);
    glDeleteBuffers(27, VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    //ACERCAR
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);

    //ALEJAR
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);

    //MOVER EN X LEFT
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);

    //MOVER EN X RIGHT
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    //MOVER EN Y POS
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        camera.ProcessKeyboard(LOOK_UP, deltaTime);

    //MOVER EN Y NEG
    /*if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        camera.ProcessKeyboard(LOOK_DOWN, deltaTime);
*/

//SALIR
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    //FUNCIONES DEL CUBO
    //ROTACIONES
    //SENTIDO HORARIO

    //MUEVE CARA AMARILLA 0
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 0);
        presionado = true;
    }


    //MUEVE CARA BLANCA 1
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 1);
        presionado = true;

    }

    //MUEVE CARA AZUL 2
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 2);
        presionado = true;

    }


    //MUEVE CARA VERDE 3
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 3);
        presionado = true;

    }


    //MUEVE CARA NARANJA 4
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 4);
        presionado = true;

    }

    //MUEVE CARA ROJA 5
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(false, 5);
        presionado = true;

    }
    //ANTIHORARIO

    //MUEVE CARA AMARILLA 0
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 0);
        presionado = true;
    }


    //MUEVE CARA BLANCA 1
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 1);
        presionado = true;

    }

    //MUEVE CARA AZUL 2
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 2);
        presionado = true;

    }


    //MUEVE CARA VERDE 3
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 3);
        presionado = true;

    }


    //MUEVE CARA NARANJA 4
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 4);
        presionado = true;

    }

    //MUEVE CARA ROJA 5
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
        cuboPrincipal->insertRotate(true, 5);
        presionado = true;

    }

    //SOLVER
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        cuboPrincipal->solve();
        condition_input == "E";
    }

    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && condition_input == "N") {
        float R, G, B;
        

        estrellas[pos_vect_estrellas]->ini = estrellas[pos_vect_estrellas]->animacion_estrella(1, "X");
        estrellas[pos_vect_estrellas + 1]->ini = estrellas[pos_vect_estrellas + 1]->animacion_estrella(-1, "X");
        estrellas[pos_vect_estrellas + 2]->ini = estrellas[pos_vect_estrellas + 2]->animacion_estrella(1, "Z");
        estrellas[pos_vect_estrellas + 3]->ini = estrellas[pos_vect_estrellas + 3]->animacion_estrella(-1, "Z");

        if (estrellas[pos_vect_estrellas]->ini == "N") {
            if (pos_vect_estrellas == 8) {
                estrellas.clear();
                for (int i = 0; i < 12; ++i) {
                    R = random();
                    G = random();
                    B = random();
                    estrella* estrellas_point = new estrella(R,G,B);
                    estrellas.push_back(estrellas_point);
                }
                pos_vect_estrellas = 0;
                condition_input = "N";
            }
            else
                pos_vect_estrellas += 4;
        }

    }
}



//CONO DE VISIÃ“N
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}
