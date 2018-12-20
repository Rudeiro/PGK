#include "Mesh.hpp"

GLuint Mesh::programID;
GLint Mesh::mvp;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
GLint Mesh::c;
glm::mat4 Mesh::Projection;
GLuint Mesh::vertexbuffer;
GLuint Mesh::orderbuffer;

GLfloat Mesh::vertex[100000] =
{
   0.0f, 0.0f, 0.0f,
   -0.5f, 0.0f, 0.0f,
   -0.5f, 0.5f, 0.0f
};
GLfloat Mesh::map[4500000];
GLuint Mesh::Order[4500000];
void Mesh::init()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(1500000);
    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    glUseProgram(programID);

	mvp = glGetUniformLocation(programID, "MVP");
    c = glGetUniformLocation(programID, "col");
    glUniform3f(c, 1, 0, 0);
    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 100.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

    std::vector<short> heights = DataReader::ReadBinaryFile();
    for(int i = 0; i < heights.size(); i++)
        map[i] = heights[i];
    /*map[0] = heights[0];
    map[1] = heights[1];
    map[2] = heights[1201];*/
    /*map[0] = 0;
    map[1] = 0;
    map[3] = 0;
    map[4] = 1;
    map[5] = heights[1];
    map[6] = 1;
    map[7] = 0;
    map[8] = heights[1201];*/
    int a = 0;
    for(int k = 0; k < 1199; k++)
    {
        for(int i = 0; i < 1201; i++)
        {
            Order[2*i+k*2403] = i +1201*k;

            Order[2*i+1 + k*2403] = i + 1201 + 1201*k;
        }
        Order[2403*(k+1) - 1] = 1500000;
    }
    //for(int i = 2402; i < 2410; i++) std::cout << Order[i] << std::endl;
    //for(int i = 0; i < 2402; i++) std::cout << Order[i] << std::endl;

    /*int k = 1201*1201;
    for(int i = 0; i < k; i++)*/
    /*for(int i = 0; i < k; i++)
    {
        map[i]
    }*/
        
    //std::cout << heights[500] << std::endl;
    glGenBuffers(1, &orderbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Order), Order, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer);
    

    glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(map), map, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        1,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    /*glGenBuffers(1, &vertexbuffer);
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
    );*/
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


void Mesh::DrawElem(Camera camera)
{
    glm:mat4 MVP = Projection*camera.View()*glm::mat4(1.0f);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    glUniform3f(c, 1, 0, 0);

    //glDrawArrays(GL_TRIANGLES, 0, 9);
    glDrawElements(GL_TRIANGLE_STRIP, 2403*1200, GL_UNSIGNED_INT, (void*)0);
    //glDrawRangeElements(GL_TRIANGLE_STRIP, 2402, 4804, 2402, GL_UNSIGNED_INT, (void*)0);
}