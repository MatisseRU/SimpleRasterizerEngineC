#ifndef RING0_H
#define RING0_H


#include "./univ.h"



/* OpenGL Shaders */

unsigned int SRE_CreateDefaultShaderProgram(void);
unsigned int SRE_CreateDefaultCornerColoredShaderProgram(void);
unsigned int SRE_CreateDefaultTexturedShaderProgram(void);

unsigned int SRE_3D_CreateDefaultCornerColoredShaderProgram(void);
unsigned int SRE_3D_CreateDefaultTexturedShaderProgram(void);
int SRE_Get_Uniform_TransformationMatrix_From_ShaderProgram(unsigned int shaderProgram);

/* Reads/writes */
float* read_floats_from_file(const char* path, size_t* outCount);
int write_floats_to_file(const char* path, const float* data, size_t count);
unsigned int* read_uints_from_file(const char* path, size_t* outCount);
int write_uints_to_file(const char* path, const unsigned int* data, size_t count);
char *read_char_to_buffer(const char* path);

#endif
