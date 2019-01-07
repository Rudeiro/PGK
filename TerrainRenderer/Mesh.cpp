#include "Mesh.hpp"

GLuint Mesh::programID;
GLuint Mesh::programID_3D;
GLint Mesh::mvp;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
GLint Mesh::c;
glm::mat4 Mesh::Projection;
GLuint Mesh::vertexbuffer;
GLuint Mesh::orderbuffer;

GLint Mesh::pX;
GLint Mesh::pY;
GLint Mesh::siX;
GLint Mesh::siY;
int Mesh::szerokosc;
int Mesh::dlugosc;

GLint Mesh::pX_3D;
GLint Mesh::pY_3D;
GLint Mesh::siX_3D;
GLint Mesh::siY_3D;
std::vector<std::vector<short>> Mesh::heights;
std::vector<int> Mesh::GridPosX;
std::vector<int> Mesh::GridPosY;

GLfloat Mesh::vertex[100000] =
{
   0.0f, 0.0f, 0.0f,
   -0.5f, 0.0f, 0.0f,
   -0.5f, 0.5f, 0.0f
};
GLfloat Mesh::map[4500000];
GLuint Mesh::Order[4500000];
void Mesh::init(std::string dirname, int psz, int ksz, int pdl, int kdl)
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_PRIMITIVE_RESTART);
    glPrimitiveRestartIndex(1500000);
    programID_3D = LoadShaders( "3DView.vertexshader", "Terrain.fragmentshader" );
    glUseProgram(programID_3D);

	mvp = glGetUniformLocation(programID_3D, "MVP");
    
    pX_3D = glGetUniformLocation(programID_3D, "dl");
    pY_3D = glGetUniformLocation(programID_3D, "sz");
    
    szerokosc = ksz-1;
    dlugosc = pdl;
    

    programID = LoadShaders( "FlatView.vertexshader", "Terrain.fragmentshader" );
    glUseProgram(programID);

	//mvp = glGetUniformLocation(programID, "MVP");
    c = glGetUniformLocation(programID, "col");
    pX = glGetUniformLocation(programID, "gridPosX");
    pY = glGetUniformLocation(programID, "gridPosY");
    siY = glGetUniformLocation(programID, "sizeY");
    siX = glGetUniformLocation(programID, "sizeX");

    glUniform1i(siX, kdl - pdl);
    glUniform1i(siY, ksz - psz);

    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 1000.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

     
    
    //std::string path = "/home/konrad/repositories/PGK/TerrainRenderer/maps";
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("/home/konrad/repositories/PGK/TerrainRenderer/maps")) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
        
        std::string filename = ent->d_name;
        int sz;
        int dl;
        if(filename.size() == 11)
        {
            sz = std::stoi(filename.substr(1, 2));
            dl = std::stoi(filename.substr(5, 3));
            if(sz >= psz && sz < ksz && dl >= pdl && dl < kdl)
            { 
                heights.push_back(DataReader::ReadBinaryFile(dirname + filename));
                GridPosX.push_back(dl - pdl);
                GridPosY.push_back(-sz + ksz-1);
            }
        }
        
        }
    closedir (dir);
    }
    
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(short)*heights[0].size(), &heights[0][0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        1,                  // size
        GL_SHORT,           // type
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


void Mesh::DrawElem(Camera camera, bool type)
{
    glm:mat4 MVP = Projection*camera.View()*glm::mat4(1.0f);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    
    int k = heights.size();

    //glDrawArrays(GL_TRIANGLES, 0, 9);
    for(int i = 0; i < k; i++)
    {
        if(type)
        {
            glUniform1i(pX, GridPosX[i]);
            glUniform1i(pY, -GridPosY[i]);
        }
        else
        {
            glUniform1i(pX_3D, GridPosX[i] + dlugosc);
            glUniform1i(pY_3D, szerokosc - GridPosY[i]);
        }
        
        glBufferData(GL_ARRAY_BUFFER, sizeof(short)*heights[i].size(), &heights[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glDrawElements(GL_TRIANGLE_STRIP, 2403*1200, GL_UNSIGNED_INT, (void*)0);
        //glDrawElements(GL_TRIANGLE_STRIP, 2403, GL_UNSIGNED_INT, (void*)0);
    }
    //glDrawRangeElements(GL_TRIANGLE_STRIP, 2402, 4804, 2402, GL_UNSIGNED_INT, (void*)0);
}

void Mesh::SwitchView(bool type)
{
    if(type) glUseProgram(programID);
    else glUseProgram(programID_3D);
}