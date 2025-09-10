#include "./ring0.h"

/* OpenGL Shaders */

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
unsigned int SRE_3D_CreateDefaultCornerColoredShaderProgram(void)
{
    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 vertexColor;\n"
    "uniform mat4 uMVP;\n"
    "void main()\n"
    "{\n"
    "   vertexColor = aColor;\n"
    "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
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
int SRE_Get_Uniform_TransformationMatrix_From_ShaderProgram(unsigned int shaderProgram)
{
    return glGetUniformLocation(shaderProgram, "uMVP");
}

unsigned int SRE_CreateDefaultTexturedShaderProgram(void)
{
    /*
        Requires to pass the xyz coordinates of the vertices to an OpenGL vec3 vertex attribute at layout location 0,
        the xy coordinates of the texture to an OpenGL vec2 vertex attribute at layout location 1 (very similar to corner colored thing),
        and the 2D sampler of the texture.
    */

    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "void main()\n"
    "{\n"
    "   TexCoord = aTexCoord;\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D ourTexture;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, TexCoord);\n"
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

unsigned int SRE_3D_CreateDefaultTexturedShaderProgram(void)
{
    /*
        Requires to pass the xyz coordinates of the vertices to an OpenGL vec3 vertex attribute at layout location 0,
        the xy coordinates of the texture to an OpenGL vec2 vertex attribute at layout location 1 (very similar to corner colored thing),
        and the 2D sampler of the texture.
    */

    const char* vertexShaderSource_default =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "out vec2 TexCoord;\n"
    "uniform mat4 uMVP;\n"
    "void main()\n"
    "{\n"
    "   TexCoord = aTexCoord;\n"
    "   gl_Position = uMVP * vec4(aPos, 1.0);\n"
    "}\0";

    const char* fragmentShaderSource_default =
    "#version 330 core\n"
    "in vec2 TexCoord;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D ourTexture;\n"
    "void main()\n"
    "{\n"
    "   FragColor = texture(ourTexture, TexCoord);\n"
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

/* Reads/writes */
float* read_floats_from_file(const char* path, size_t* outCount)
{
    FILE* f = fopen(path, "r");
    if (!f)
    {
        fprintf(stderr, "Error: cannot open file %s\n", path);
        return NULL;
    }

    size_t capacity = 16;
    size_t count = 0;
    float* buffer = malloc(capacity * sizeof(float));
    if (!buffer)
    {
        fprintf(stderr, "Error: cannot allocate memory\n");
        fclose(f);
        return NULL;
    }

    while (1)
    {
        float value;
        if (fscanf(f, "%f", &value) != 1) break;
        if (count >= capacity)
        {
            capacity *= 2;
            float* tmp = realloc(buffer, capacity * sizeof(float));
            if (!tmp)
            {
                fprintf(stderr, "Error: cannot reallocate memory\n");
                free(buffer);
                fclose(f);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[count++] = value;
    }

    fclose(f);
    *outCount = count;
    return buffer;
}
int write_floats_to_file(const char* path, const float* data, size_t count)
{
    FILE* f = fopen(path, "w");
    if (!f)
    {
        fprintf(stderr, "Error: cannot open file %s for writing\n", path);
        return -1;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (fprintf(f, "%f\n", data[i]) < 0)
        {
            fprintf(stderr, "Error: failed to write to file %s\n", path);
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}
unsigned int* read_uints_from_file(const char* path, size_t* outCount)
{
    FILE* f = fopen(path, "r");
    if (!f)
    {
        fprintf(stderr, "Error: cannot open file %s\n", path);
        return NULL;
    }

    size_t capacity = 16;
    size_t count = 0;
    unsigned int* buffer = malloc(capacity * sizeof(unsigned int));
    if (!buffer)
    {
        fprintf(stderr, "Error: cannot allocate memory\n");
        fclose(f);
        return NULL;
    }

    while (1)
    {
        unsigned int value;
        if (fscanf(f, "%u", &value) != 1) break;
        if (count >= capacity)
        {
            capacity *= 2;
            unsigned int* tmp = realloc(buffer, capacity * sizeof(unsigned int));
            if (!tmp)
            {
                fprintf(stderr, "Error: cannot reallocate memory\n");
                free(buffer);
                fclose(f);
                return NULL;
            }
            buffer = tmp;
        }
        buffer[count++] = value;
    }

    fclose(f);
    *outCount = count;
    return buffer;
}
int write_uints_to_file(const char* path, const unsigned int* data, size_t count)
{
    FILE* f = fopen(path, "w");
    if (!f)
    {
        fprintf(stderr, "Error: cannot open file %s for writing\n", path);
        return -1;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (fprintf(f, "%u\n", data[i]) < 0)
        {
            fprintf(stderr, "Error: failed to write to file %s\n", path);
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}
char *read_char_to_buffer(const char* path)
{
    FILE* f = fopen(path, "rb");
    if (!f) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    rewind(f);

    if (size < 0) {
        perror("ftell failed");
        fclose(f);
        return NULL;
    }

    char* buffer = malloc(size + 1);
    if (!buffer) {
        perror("malloc failed");
        fclose(f);
        return NULL;
    }

    size_t read = fread(buffer, 1, size, f);
    buffer[read] = '\0';
    fclose(f);

    return buffer;
}

