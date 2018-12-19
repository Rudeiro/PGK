#include "Mesh.hpp"

GLuint Mesh::programID;
GLint Mesh::mvp;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
glm::mat4 Mesh::Projection;
GLuint Mesh::vertexbuffer;

GLfloat Mesh::vertex[100000] =
{
   
};

void Mesh::init()
{
    glEnable(GL_DEPTH_TEST);

    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    glUseProgram(programID);

	mvp = glGetUniformLocation(programID, "MVP");
    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 100.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
}
void Mesh::clear()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
}


