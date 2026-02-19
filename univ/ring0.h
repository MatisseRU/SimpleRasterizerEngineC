#ifndef RING0_H
#define RING0_H


#include "./univ.h"

/* Global Variables */
// DEBUG FLAG
extern uint8_t SRE_DEBUGGING;


/* OpenGL Shaders */

unsigned int SRE_ring0_CreateDefaultShaderProgram(void);
unsigned int SRE_ring0_CreateDefaultCornerColoredShaderProgram(void);
unsigned int SRE_ring0_CreateDefaultTexturedShaderProgram(void);

unsigned int SRE_ring0_3D_CreateDefaultCornerColoredShaderProgram(void);
unsigned int SRE_ring0_3D_CreateDefaultTexturedShaderProgram(void);
int SRE_ring0_Get_Uniform_TransformationMatrix_From_ShaderProgram(unsigned int shaderProgram);
// Creates a shader program from OpenGL Shader Code; requires vertex shader file path and fragment shader code path.
unsigned int SRE_ring0_3D_CreateShaderProgram_From_File(char *vshaderpath, char *fshaderpath);

/* OpenGL VAO / VBO / EBO manipulations */

int SRE_ring0_SaveModel_TO_GLBuffers(GLuint VAO, GLuint VBO, GLuint EBO, float *vertices, unsigned int *indices, GLsizeiptr vert_size, uint16_t vert_nbr, GLsizeiptr ind_size, uint16_t ind_nbr, unsigned int vert_pos_layout_in_shader, int vert_pos_size_per_point, GLenum vert_pos_data_type, GLsizei vert_pos_stride, const void *vert_pos_pointer, unsigned int vert_color_layout_in_shader, int vert_color_size_per_point, GLenum vert_color_data_type, GLsizei vert_color_stride, const void *vert_color_pointer);


/* OpenGL texture manipulations */

int SRE_ring0_CreateTextureFromFile(const char *texture_file_path, GLuint gl_texture_id);




/* Reads/writes */

float* SRE_ring0_read_floats_from_file(const char* path, size_t* outCount);
int SRE_ring0_write_floats_to_file(const char* path, const float* data, size_t count);
unsigned int* SRE_ring0_read_uints_from_file(const char* path, size_t* outCount);
int SRE_ring0_write_uints_to_file(const char* path, const unsigned int* data, size_t count);
char *SRE_ring0_read_char_to_buffer(const char* path);


/* logging system */
// where the engine should save debugging logs
#define SRE_LOG_PATH "sre_logs.txt"
// Logging/debugging/printing function, you should replace fprintf with this implementation, pass NULL to auxiliary_output if not necessary.
int SRE_Log(const char *in_buffer, FILE *auxiliary_output);


/* example shapes */
// exports the vertices / indices of a 3D model cube to a file you can open and load the model from.
int SRE_ring0_3D_ExportDefaultTexturedCube(void);


#endif
