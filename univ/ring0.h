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

#endif
