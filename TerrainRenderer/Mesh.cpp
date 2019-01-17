#include "Mesh.hpp"

GLuint Mesh::programID;
GLuint Mesh::programID_3D;
GLint Mesh::mvp;
GLint Mesh::mvp2D;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
GLint Mesh::c;
glm::mat4 Mesh::Projection;
GLuint Mesh::vertexbuffer;
GLuint Mesh::orderbuffer[6];
GLuint Mesh::orderbuffer2;
GLuint Mesh::orderbuffer4;


GLint Mesh::pX;
GLint Mesh::pY;
GLint Mesh::siX;
GLint Mesh::siY;
int Mesh::szerokosc;
int Mesh::dlugosc;
int Mesh::lvl;

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
std::vector<GLuint> Mesh::LODD;
std::vector<GLuint> Mesh::LOD_sizes;

std::vector<GLuint> Mesh::CreateLOD(int a)
{
    std::vector<GLuint> LODD;
    for(int k = 0; k < 1200; k += a)
    {
        for(int i = 0; i < 1201; i += a)
        {
            LODD.push_back(i + 1201*k);
            LODD.push_back(i + 1201*a + 1201*k);
        }
        LODD.push_back(1500000);
    }
    return LODD;
}

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
    mvp2D = glGetUniformLocation(programID, "MVP");

    glUniform1i(siX, kdl - pdl);
    glUniform1i(siY, ksz - psz);

    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 10000.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

     
    
    //std::string path = "/home/konrad/repositories/PGK/TerrainRenderer/maps";
    DIR *dir;
    struct dirent *ent;
    std::string d = "./" + dirname;
    if ((dir = opendir (d.c_str())) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
        
        std::string filename = ent->d_name;
        
        int sz;
        int dl;
        if(filename.size() == 11)
        {
            if(filename[0] == 'N') sz = std::stoi(filename.substr(1, 2));
            else sz = -std::stoi(filename.substr(1, 2));
            if(filename[3] == 'E') dl = std::stoi(filename.substr(4, 3));
            else dl = -std::stoi(filename.substr(4, 3));
            if(sz >= psz && sz < ksz && dl >= pdl && dl < kdl)
            { 
                std::cout << filename << std::endl;
                heights.push_back(DataReader::ReadBinaryFile(dirname + filename));
                GridPosX.push_back(dl - pdl);
                GridPosY.push_back(-sz + ksz-1);
            }
        }
        
        }
    closedir (dir);
    }
    
    LODD = CreateLOD(1);
    LOD_sizes.push_back(LODD.size());
    glGenBuffers(1, &orderbuffer[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*LODD.size(), &LODD[0], GL_STATIC_DRAW);

    LODD = CreateLOD(2);
    LOD_sizes.push_back(LODD.size());
    glGenBuffers(2, &orderbuffer[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*LODD.size(), &LODD[0], GL_STATIC_DRAW);
    lvl = 3;
    LODD = CreateLOD(4);
    LOD_sizes.push_back(LODD.size());
    glGenBuffers(3, &orderbuffer[2]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*LODD.size(), &LODD[0], GL_STATIC_DRAW);

    LODD = CreateLOD(8);
    LOD_sizes.push_back(LODD.size());
    glGenBuffers(4, &orderbuffer[3]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*LODD.size(), &LODD[0], GL_STATIC_DRAW);

    /*LODD = CreateLOD(16);
    LOD_sizes.push_back(LODD.size());
    glGenBuffers(5, &orderbuffer[4]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[4]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*LODD.size(), &LODD[0], GL_STATIC_DRAW);*/
    

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
     glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   
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


int Mesh::DrawElem(Camera camera, bool type, int s, int d)
{
    glm:mat4 MVP = Projection*camera.View()*glm::mat4(1.0f);
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(mvp2D, 1, GL_FALSE, &MVP[0][0]);
    int k = heights.size();
    int vertices = 0;
    int fragmentLT;
    int fragmentLN;
    
    for(int i = 0; i < k; i++)
    {
        fragmentLT = szerokosc - GridPosY[i];
        fragmentLN = GridPosX[i] + dlugosc;
        if(type)
        {
            //std::cout << GridPosX[i] << " " << -GridPosY[i] << std::endl;
            
            glUniform1i(pX, GridPosX[i]);
            glUniform1i(pY, -GridPosY[i]);
        }
        else
        {
            glUniform1i(pX_3D, fragmentLN);
            glUniform1i(pY_3D, fragmentLT);
            //std::cout << GridPosX[i] + dlugosc << " " << szerokosc - GridPosY[i] << std::endl;
        }
        
        
        //std::cout << s << " " << d << std::endl;
        if(abs(fragmentLT - s) <= 3 && abs(fragmentLN - d) <= 3)
        {
            glBufferData(GL_ARRAY_BUFFER, sizeof(short)*heights[i].size(), &heights[i][0], GL_STATIC_DRAW);
            glDrawElements(GL_TRIANGLE_STRIP, LOD_sizes[lvl], GL_UNSIGNED_INT, (void*)0);
            vertices += LOD_sizes[lvl];
        }
    }
    return vertices;
}

void Mesh::SwitchView(bool type)
{
    if(type) glUseProgram(programID);
    else glUseProgram(programID_3D);
}

void Mesh::SwitchLOD(int l)
{
    lvl = l;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, orderbuffer[lvl]);
}