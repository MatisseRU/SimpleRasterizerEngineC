#include <SDL3/SDL.h>
#include "./glad.h"
#include <stdio.h>


unsigned int SRE_CreateDefaultShaderProgram(void)
{
    /*
        Only requires to pass the xyz coordinates of the vertices to an OpenGL vec3 vertex attribute at layout location 0.
        I.E.:
        float vertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
       -0.5f, -0.5f, 0.0f,  // bottom left
       -0.5f,  0.5f, 0.0f   // top left
        };

        unsigned int indices[] = {  // facultative
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        // facultative: glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0); <- the location 0
    */

    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);\n"
    "}\n\0";


    // OPENGL: create the Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource_default, NULL);
    glCompileShader(vertexShader);

    // OPENGL: create the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource_default, NULL);
    glCompileShader(fragmentShader);

    // OPENGL: shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // OPENGL: clean up things and return the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
unsigned int SRE_CreateDefaultCornerColoredShaderProgram(void)
{
    /*
        Requires to pass the xyz coordinates and the respective color of each vertices to 2 OpenGL vec3 vertex attribute at layout location 0 for position and location 1 for color.
    */
    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "void main()\n"
    "{\n"
    "   vertexColor = aColor;\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "in vec3 vertexColor;\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(vertexColor, 1.0);\n"
    "}\n\0";


    // OPENGL: create the Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource_default, NULL);
    glCompileShader(vertexShader);

    // OPENGL: create the Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource_default, NULL);
    glCompileShader(fragmentShader);

    // OPENGL: shader program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // OPENGL: clean up things and return the shader program
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}