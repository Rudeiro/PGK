#include "Mesh.hpp"

GLuint Mesh::programID;
GLint Mesh::mvp;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
GLint Mesh::c;
glm::mat4 Mesh::Projection;
GLuint Mesh::vertexbuffer;

GLfloat Mesh::vertex[100000] =
{
   0.0f, 0.0f, 0.0f,
   -0.5f, 0.0f, 0.0f,
   -0.5f, 0.5f, 0.0f
};

void Mesh::init()
{
    glEnable(GL_DEPTH_TEST);

    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    glUseProgram(programID);

	mvp = glGetUniformLocation(programID, "MVP");
    c = glGetUniformLocation(programID, "col");
    glUniform3f(c, 1, 0, 0);
    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 100.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

    glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
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

void Mesh::draw(glm::mat4 model, Camera camera)
{
    glm:mat4 MVP = Projection*camera.View()*model;
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    glUniform3f(c, color[0], color[1], color[2]);

    glDrawArrays(GL_TRIANGLES, shape, v_num);
}


