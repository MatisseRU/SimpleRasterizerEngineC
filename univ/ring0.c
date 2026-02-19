#include "./ring0.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

/* Global Variables */
// DEBUG FLAG
uint8_t SRE_DEBUGGING;


/* OpenGL Shaders */

unsigned int SRE_ring0_CreateDefaultShaderProgram(void)
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
unsigned int SRE_ring0_CreateDefaultCornerColoredShaderProgram(void)
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
unsigned int SRE_ring0_3D_CreateDefaultCornerColoredShaderProgram(void)
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
int SRE_ring0_Get_Uniform_TransformationMatrix_From_ShaderProgram(unsigned int shaderProgram)
{
    return glGetUniformLocation(shaderProgram, "uMVP");
}
unsigned int SRE_ring0_CreateDefaultTexturedShaderProgram(void)
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
unsigned int SRE_ring0_3D_CreateDefaultTexturedShaderProgram(void)
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


/* OpenGL VAO / VBO / EBO manipulations */

int SRE_ring0_SaveModel_TO_GLBuffers(GLuint VAO, GLuint VBO, GLuint EBO, float *vertices, unsigned int *indices, GLsizeiptr vert_size, uint16_t vert_nbr, GLsizeiptr ind_size, uint16_t ind_nbr, unsigned int vert_pos_layout_in_shader, int vert_pos_size_per_point, GLenum vert_pos_data_type, GLsizei vert_pos_stride, const void *vert_pos_pointer, unsigned int vert_color_layout_in_shader, int vert_color_size_per_point, GLenum vert_color_data_type, GLsizei vert_color_stride, const void *vert_color_pointer)
{
    // Bind VAO and VBO and EBO
    // VAO
    glBindVertexArray(VAO);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);


    // Store vertices postitions and indices, also specify the size of the vector and the starting pointer to the position data.
    glBufferData(GL_ARRAY_BUFFER, vert_size, vertices, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ind_size, indices, GL_STATIC_DRAW);
    glVertexAttribPointer(vert_pos_layout_in_shader, vert_pos_size_per_point, vert_pos_data_type, GL_FALSE, vert_pos_stride, vert_pos_pointer); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(vert_pos_layout_in_shader);
    // Store the vertices color, also specify the size of the vector and the starting pointer to the texture coords.
    glVertexAttribPointer(vert_color_layout_in_shader, vert_color_size_per_point, vert_color_data_type, GL_FALSE, vert_color_stride, vert_color_pointer); // valable for VAO VBO and EBO
    glEnableVertexAttribArray(vert_color_layout_in_shader);

    
    // log out how many vertices are loaded
    char tempBuff[100];
    SRE_Log("Saved data in buffers for VAO n°", NULL);
    sprintf(tempBuff, "%u", VAO);
    SRE_Log(tempBuff, NULL);
    SRE_Log("\n", NULL);

    SRE_Log("Successfully loaded model with ", NULL);
    sprintf(tempBuff, "%u", vert_nbr);
    SRE_Log(tempBuff, NULL);
    SRE_Log(" vertices and ", NULL);
    sprintf(tempBuff, "%u", ind_nbr);
    SRE_Log(tempBuff, NULL);
    SRE_Log(" indices\n", NULL);

    SRE_Log("Vertices:\n", NULL);
    for (uint16_t i = 0; i < vert_nbr; i++)
    {
        sprintf(tempBuff, "%f", vertices[i]);
        SRE_Log(tempBuff, NULL);
        SRE_Log(" ; ", NULL);
    }
    
    SRE_Log("\nIndices:\n", NULL);
    for (uint16_t i = 0; i < ind_nbr; i++)
    {
        sprintf(tempBuff, "%u", indices[i]);
        SRE_Log(tempBuff, NULL);
        SRE_Log(" ; ", NULL);
    }
    SRE_Log("\n", NULL);


    // Clean up bindings, preventing from unwanted changes.
    // VAO
    glBindVertexArray(0);
    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return 0;
}


/* OpenGL texture manipulations */

int SRE_ring0_CreateTextureFromFile(const char *texture_file_path, GLuint gl_texture_id)
{
    // Load texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *textureLoaded = stbi_load(texture_file_path, &width, &height, &nrChannels, 0);

    if (textureLoaded == NULL)
    {
        SRE_Log("\nFailed to load texture : \n", NULL);
        SRE_Log(stbi_failure_reason(), NULL);
        SRE_Log("\n", NULL);
    }else
    {
        char tempbuff[100];

        SRE_Log("Image texture loaded:\nwidth: ", NULL);
        // width
        sprintf(tempbuff, "%d", width);
        SRE_Log(tempbuff, NULL);
        SRE_Log("\n", NULL);
        // height
        SRE_Log("height: ", NULL);
        sprintf(tempbuff, "%d", height);
        SRE_Log(tempbuff, NULL);
        SRE_Log("\n", NULL);
        // channels
        SRE_Log("channels: ", NULL);
        sprintf(tempbuff, "%d", nrChannels);
        SRE_Log(tempbuff, NULL);
        SRE_Log("\n", NULL);
    }


    // Create an OpenGL texture
    glBindTexture(GL_TEXTURE_2D, gl_texture_id);

    // Wrapping settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering settings
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Format RGB
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureLoaded);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(textureLoaded);

    // Clean unbinding
    glBindTexture(GL_TEXTURE_2D, 0);


    return 0;
}



/* Reads/writes */

float* SRE_ring0_read_floats_from_file(const char* path, size_t* outCount)
{
    FILE* f = fopen(path, "r");
    if (!f)
    {
        SRE_Log("Error: cannot open file ", NULL);
        SRE_Log(path, NULL);
        SRE_Log("\n", NULL);
        return NULL;
    }

    size_t capacity = 16;
    size_t count = 0;
    float* buffer = malloc(capacity * sizeof(float));
    if (!buffer)
    {
        SRE_Log("Error: cannot allocate memory\n", NULL);
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
                SRE_Log("Error: cannot reallocate memory\n", NULL);
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
int SRE_ring0_write_floats_to_file(const char* path, const float* data, size_t count)
{
    FILE* f = fopen(path, "w");
    if (!f)
    {
        SRE_Log("Error: cannot open file ", NULL);
        SRE_Log(path, NULL);
        SRE_Log("\n", NULL);
        return -1;
    }

    for (size_t i = 0; i < count; i++)
    {
        if (fprintf(f, "%f\n", data[i]) < 0)
        {
            SRE_Log("Error: cannot write to file ", NULL);
            SRE_Log(path, NULL);
            SRE_Log("\n", NULL);
            fclose(f);
            return -1;
        }
    }

    fclose(f);
    return 0;
}
unsigned int* SRE_ring0_read_uints_from_file(const char* path, size_t* outCount)
{
    FILE* f = fopen(path, "r");
    if (!f)
    {
        SRE_Log("Error: cannot open file ", NULL);
        SRE_Log(path, NULL);
        SRE_Log("\n", NULL);
        return NULL;
    }

    size_t capacity = 16;
    size_t count = 0;
    unsigned int* buffer = malloc(capacity * sizeof(unsigned int));
    if (!buffer)
    {
        SRE_Log("Error: cannot allocate memory\n", NULL);
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
                SRE_Log("Error: cannot reallocate memory\n", NULL);
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
int SRE_ring0_write_uints_to_file(const char* path, const unsigned int* data, size_t count)
{
    FILE* f = fopen(path, "w");
    if (!f)
    {
        SRE_Log("Error: cannot open file ", NULL);
        SRE_Log(path, NULL);
        SRE_Log(" for writing\n", NULL);
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
char *SRE_ring0_read_char_to_buffer(const char* path)
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




/* logging system */
// Logging/debugging/printing function, you should replace fprintf with this implementation, pass NULL to auxiliary_output if not necessary.
int SRE_Log(const char *in_buffer, FILE *auxiliary_output)
{
    FILE *logOutput = fopen(SRE_LOG_PATH, "a");
    fprintf(logOutput, in_buffer);

    if (auxiliary_output != NULL)
    {
        fprintf(auxiliary_output, in_buffer);
    }

    // if we're debugging
    if (SRE_DEBUGGING == 1)
    {
        fprintf(stderr, in_buffer);
    }

    fclose(logOutput);

    return 0;
}




/* example shapes */
// exports the vertices / indices of a 3D model cube to a file you can open and load the model from.
int SRE_ring0_3D_ExportDefaultTexturedCube(void)
{
    unsigned int nbr_of_vertices = 24*5;
    float vertices[24*5] =
    {
        // behind (-Z)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f, -1.0f,   0.0f, 1.0f,

        // forward (+Z)
        -1.0f, -1.0f,  1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,  1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,

        // left (-X)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
        -1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f,

        // right (+X)
        1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
        1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        1.0f, -1.0f,  1.0f,   0.0f, 1.0f,

        // up (+Y)
        -1.0f,  1.0f, -1.0f,   0.0f, 0.0f,
         1.0f,  1.0f, -1.0f,   1.0f, 0.0f,
         1.0f,  1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f,  1.0f,  1.0f,   0.0f, 1.0f,

        // bottom (-Y)
        -1.0f, -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,   1.0f, 0.0f,
         1.0f, -1.0f,  1.0f,   1.0f, 1.0f,
        -1.0f, -1.0f,  1.0f,   0.0f, 1.0f
    };

    unsigned int nbr_of_indices = 36;
    unsigned int indices[36] =
    {
        0, 1, 2, 2, 3, 0,       // behind
        4, 5, 6, 6, 7, 4,       // forward
        8, 9,10,10,11, 8,       // left
        12,13,14,14,15,12,       // right
        16,17,18,18,19,16,       // up
        20,21,22,22,23,20        // bottom
    };

    if (SRE_ring0_write_floats_to_file("3D_cube.vert", vertices, nbr_of_vertices) < 0)
    {
        SRE_Log("Failed to write to file cube vertices\n", NULL);
        return -1;
    }

    if (SRE_ring0_write_uints_to_file("3D_cube.indi", indices, nbr_of_indices))
    {
        SRE_Log("Failed to write to file cube indices\n", NULL);
        return -1;
    }


    return 0;
}


