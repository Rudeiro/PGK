

#include "Mesh.hpp"



GLuint Mesh::programID;
GLint Mesh::t;
GLint Mesh::s;
GLint Mesh::c;
GLint Mesh::r_y;
GLint Mesh::mvp;
GLint Mesh::m;
GLint Mesh::v;
GLint Mesh::p;
GLint Mesh::PLightColor;
GLint Mesh::PLightPos;
GLint Mesh::BubLigWorldSpace;
GLint Mesh::BubLigCol;
GLint Mesh::NumOfLights;
GLint Mesh::isInstanced;
int Mesh::LightBubbles;
vec3 Mesh::BubbleLightsPos[15];
vec3 Mesh::BubbleLightsCol[15];
glm::mat4 Mesh::Projection;
GLfloat a = (sqrt(5) + 1)/2;
GLfloat b = 1;
GLfloat Mesh::vertex[100000] =
{
    b/2,  0.0f, a/2,
    a/2,  -b/2, 0.0f,
     0.0f, -a/2, b/2, // 9
    0.0f, -a/2, -b/2,
    -a/2, -b/2, 0.0f,
    0.0f, -a/2,  b/2, //19
    0.0f, -a/2,  b/2,
    a/2, -b/2, 0.0f,
    0.0f, -a/2, -b/2, // 20
    -a/2, -b/2, 0.0f,
    -b/2, 0.0f, a/2,
    0.0f, -a/2,  b/2,  // 11
    a/2,  b/2, 0.0f,
    b/2, 0.0f, -a/2,
    a/2, -b/2, 0.0f,    // 8
    0.0f,  a/2, -b/2,
    b/2, 0.0f, -a/2,
    a/2,  b/2, 0.0f,   // 7
    b/2,  0.0f, -a/2,
    0.0f, -a/2, -b/2,
    a/2,  -b/2, 0.0f,  // 1
    0.0f, -a/2, -b/2,
    b/2,  0.0f, -a/2,
    -b/2, 0.0f, -a/2, // 2
    -a/2, -b/2, 0.0f,
    0.0f, -a/2, -b/2,
    -b/2, 0.0f, -a/2,  // 3
    -a/2,  b/2, 0.0f,
    -a/2, -b/2, 0.0f,
    -b/2, 0.0f, -a/2, // 4
    -a/2,  b/2, 0.0f,
    -b/2, 0.0f, -a/2,
    0.0f,  a/2, -b/2,  // 5
    0.0f,  a/2, -b/2,
    -b/2, 0.0f, -a/2,
    b/2, 0.0f, -a/2,  // 6
    -b/2, 0.0f,  a/2,
    b/2,  0.0f,  a/2,
    0.0f, -a/2,  b/2,  // 10
    -a/2, -b/2, 0.0f,
    -a/2,  b/2, 0.0f,
    -b/2, 0.0f, a/2,  // 12
    0.0f,  a/2,  b/2,
    -b/2, 0.0f,  a/2,
    -a/2,  b/2, 0.0f,    // 13
    -b/2, 0.0f, a/2,
    0.0f,  a/2, b/2,
    b/2, 0.0f, a/2,      // 14
    a/2,  b/2, 0.0f,
    b/2, 0.0f,  a/2,
    0.0f,  a/2, b/2,      // 15
    a/2, -b/2, 0.0f,
    b/2, 0.0f, a/2,
    a/2,  b/2, 0.0f,     // 16
    0.0f, a/2,  b/2,
    -a/2, b/2, 0.0f,
     0.0f, a/2, -b/2,   // 17
    0.0f, a/2, -b/2,
     a/2, b/2, 0.0f,
     0.0f, a/2,  b/2,    // 18
    //////////////////////////////////// sphere
};

GLfloat Mesh::cube[1000] =
{
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f,  0.5f,
     0.5f, -0.5f,  0.5f,

    -0.5f, -0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f,  0.5f, -0.5f,
    -0.5f,  0.5f,  0.5f,
    -0.5f, -0.5f, -0.5f,

    -0.5f,  0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
    -0.5f,  0.5f, -0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f, -0.5f,

     0.5f, -0.5f, -0.5f,
     0.5f, -0.5f,  0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f, -0.5f, -0.5f,
     0.5f,  0.5f,  0.5f,
     0.5f,  0.5f, -0.5f,

    -0.5f, -0.5f, 0.5f,
    -0.5f,  0.5f, 0.5f,
     0.5f, -0.5f, 0.5f,
     0.5f, -0.5f, 0.5f,
     -0.5f,  0.5f, 0.5f,
     0.5f,  0.5f, 0.5f,

    -0.5f, 0.5f,  0.5f,
    -0.5f, 0.5f, -0.5f,
     0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f,  0.5f,
     0.5f, 0.5f, -0.5f,
     0.5f, 0.5f,  0.5f,
};
GLfloat Mesh::Normals[100000];
GLuint Mesh::vertexbuffer;
GLuint Mesh::vertexnormal;
GLuint Mesh::posbuffer;
GLuint Mesh::colbuffer;

void Mesh::init()
{

    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    glUseProgram(programID);

	c = glGetUniformLocation(programID, "col");
	m = glGetUniformLocation(programID, "M");
	v = glGetUniformLocation(programID, "V");
	p = glGetUniformLocation(programID, "P");
	t = glGetUniformLocation(programID, "LightPosition_worldspace");
	isInstanced = glGetUniformLocation(programID, "isInstanced");
	PLightColor = glGetUniformLocation(programID, "PlayerLightCol");
	PLightPos = glGetUniformLocation(programID, "PlayerLightPos_worldspace");
    BubLigCol = glGetUniformLocation(programID, "BubblesLightColor");
    BubLigWorldSpace = glGetUniformLocation(programID, "BubblesLightPos_worldspace");
	NumOfLights = glGetUniformLocation(programID, "NumberOfLight");
    mvp = glGetUniformLocation(programID, "MVP");
    Projection = glm::perspective(glm::radians(45.0f), (float) 4/ (float) 4, 0.1f, 100.0f);
    glUniformMatrix4fv(p, 1, GL_FALSE, &Projection[0][0]);

    ////////////////////////////////////////////////////////////////////////////////
    GLfloat sphere[100000];
	GLfloat new_sphere[100000];
	int n = 60*9;
	for(int i = 0; i < n; i++) sphere[i] = vertex[i];

	vec3 verA;
    vec3 verB;
    vec3 verC;
    vec3 mid_ab;
    vec3 mid_bc;
    vec3 mid_ac;
    float sto;
    int k;
    for(int p = 0; p < 3; p++) // creating spher out of icosahedron
    {
        verA = vec3(sphere[0], sphere[1], sphere[2]);
        verB = vec3(sphere[3], sphere[4], sphere[5]);
        verC = vec3(sphere[6], sphere[7], sphere[8]);
        mid_ab = vec3((verA[0] + verB[0])/2, (verA[1] + verB[1])/2, (verA[2] + verB[2])/2);
        sto = sqrt((a/2)*(a/2) + (b/2)*(b/2))/sqrt(mid_ab[0]*mid_ab[0] + mid_ab[1]*mid_ab[1] + mid_ab[2]*mid_ab[2]);
        k = 0;
        for(int i = 0; i < n; i += 9)
        {
            verA = vec3(sphere[i], sphere[i+1], sphere[i+2]);
            verB = vec3(sphere[i+3], sphere[i+4], sphere[i+5]);
            verC = vec3(sphere[i+6], sphere[i+7], sphere[i+8]);
            mid_ab = vec3((verA[0] + verB[0])/2, (verA[1] + verB[1])/2, (verA[2] + verB[2])/2);
            mid_ac = vec3((verA[0] + verC[0])/2, (verA[1] + verC[1])/2, (verA[2] + verC[2])/2);
            mid_bc = vec3((verC[0] + verB[0])/2, (verC[1] + verB[1])/2, (verC[2] + verB[2])/2);
            mid_ab *= sto;
            mid_bc *= sto;
            mid_ac *= sto;

            //////////////////////// first new triangle
            new_sphere[k+27] = mid_ab[0];
            new_sphere[k+28] = mid_ab[1];
            new_sphere[k+29] = mid_ab[2];

            new_sphere[k+33] = verA[0];
            new_sphere[k+34] = verA[1];
            new_sphere[k+35] = verA[2];

            new_sphere[k+30] = mid_ac[0];
            new_sphere[k+31] = mid_ac[1];
            new_sphere[k+32] = mid_ac[2];


            ///////////////////////// second new triangle
            new_sphere[k+18] = mid_ab[0];
            new_sphere[k+19] = mid_ab[1];
            new_sphere[k+20] = mid_ab[2];

            new_sphere[k+24] = mid_bc[0];
            new_sphere[k+25] = mid_bc[1];
            new_sphere[k+26] = mid_bc[2];

            new_sphere[k+21] = verB[0];
            new_sphere[k+22] = verB[1];
            new_sphere[k+23] = verB[2];


            ///////////////////////////// third new triangle
            new_sphere[k+9] = mid_bc[0];
            new_sphere[k+10] = mid_bc[1];
            new_sphere[k+11] = mid_bc[2];

            new_sphere[k+12] = verC[0];
            new_sphere[k+13] = verC[1];
            new_sphere[k+14] = verC[2];

            new_sphere[k+15] = mid_ac[0];
            new_sphere[k+16] = mid_ac[1];
            new_sphere[k+17] = mid_ac[2];


            ///////////////////////////// fourth new triangle
            new_sphere[k+0] = mid_bc[0];
            new_sphere[k+1] = mid_bc[1];
            new_sphere[k+2] = mid_bc[2];

            new_sphere[k+6] = mid_ab[0];
            new_sphere[k+7] = mid_ab[1];
            new_sphere[k+8] = mid_ab[2];

            new_sphere[k+3] = mid_ac[0];
            new_sphere[k+4] = mid_ac[1];
            new_sphere[k+5] = mid_ac[2];


            k += 36;
        }
        for(int i = 0; i < n*4; i++) sphere[i] = new_sphere[i];
        for(int i = 0; i < n*4; i++) vertex[i] = sphere[i];

        n *= 4;
    }
    /////////////////////////////////////////////////////////////
    for(int i = 0; i < 108; i++) vertex[n + i] = cube[i];
    for(int i = 0; i < n; i++) Normals[i] =vertex[i];

    ///////////////////////////////////////////////////////////// Counting normals of the cube
    for(int i = 0; i < 108; i += 9)
    {
        vec3 a, b, c;
        a = vec3(cube[i],cube[i+1], cube[i+2]) - vec3(cube[i+3],cube[i+4], cube[i+5]);
        b = vec3(cube[i],cube[i+1], cube[i+2]) - vec3(cube[i+6],cube[i+7], cube[i+8]);
        Normals[n+i] = cross(b,  a)[0];
        Normals[n+i+1] = cross(b,  a)[1];
        Normals[n+i+2] = cross(b,  a)[2];


        a = vec3(cube[i+3],cube[i+4], cube[i+5]) - vec3(cube[i],cube[i+1], cube[i+2]);
        b = vec3(cube[i+3],cube[i+4], cube[i+5]) - vec3(cube[i+6],cube[i+7], cube[i+8]);
        Normals[n+i+3] = cross(a  , b)[0];
        Normals[n+i+4] = cross(a  , b)[1];
        Normals[n+i+5] = cross(a  , b)[2];

        a = vec3(cube[i+6],cube[i+7], cube[i+8]) - vec3(cube[i],cube[i+1], cube[i+2]);
        b = vec3(cube[i+6],cube[i+7], cube[i+8])- vec3(cube[i+3],cube[i+4], cube[i+5]);
        Normals[n+i+6] = cross(b, a)[0];
        Normals[n+i+7] = cross(b, a)[1];
        Normals[n+i+8] = cross(b, a)[2];
    }

    glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

	glGenBuffers(1, &vertexnormal);
	glBindBuffer(GL_ARRAY_BUFFER, vertexnormal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Normals), Normals, GL_STATIC_DRAW);

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
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vertexnormal);

    glVertexAttribPointer(
        1,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );

    glGenBuffers(1, &colbuffer);
    glGenBuffers(1, &posbuffer);

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, posbuffer);
    glVertexAttribPointer(
        2,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glEnableVertexAttribArray(3);
    glBindBuffer(GL_ARRAY_BUFFER, colbuffer);

    glVertexAttribPointer(
        3,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
        4,                  // size
        GL_FLOAT,           // type
        GL_FALSE,           // normalized?
        0,                  // stride
        (void*)0            // array buffer offset
    );
    glVertexAttribDivisor(2, 1); // positions : one per quad (its center) -> 1
    glVertexAttribDivisor(3, 1);
}
void Mesh::clear()
{
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
}

void Mesh::draw(glm::mat4 model, float angle, Camera camera, Light light)
{
    glm:mat4 MVP = Projection*camera.View()*model;
    glUniformMatrix4fv(mvp, 1, GL_FALSE, &MVP[0][0]);
    glUniform3f(t, 4.0f, 30.0f, 15.0f); // sun light position
    glUniformMatrix4fv(v, 1, GL_FALSE, &camera.View()[0][0]);
    glUniformMatrix4fv(m, 1, GL_FALSE, &model[0][0]);
    glUniform3f(c, color[0], color[1], color[2]);


    if(light.GetType() == 1) // if object is our player
    {
        glUniform3f(PLightColor, light.GetCol()[0], light.GetCol()[1], light.GetCol()[2]);
        glUniform3f(PLightPos, light.GetPos()[0], light.GetPos()[1], light.GetPos()[2]);
    }

    glUniform3fv(BubLigCol, LightBubbles, value_ptr(BubbleLightsCol[0]));
    glUniform3fv(BubLigWorldSpace, LightBubbles, value_ptr(BubbleLightsPos[0]));

    glUniform1i(isInstanced, 0);
    glUniform1i(NumOfLights, LightBubbles);

    glDrawArrays(GL_TRIANGLES, shape, v_num);
}

void Mesh::ChangeBubbleLight(int n, vec3 Pos[15], vec3 Col[15])
{
    LightBubbles = n;
    for(int i = 0; i < n; i++)
    {
        BubbleLightsPos[i] = Pos[i];
        BubbleLightsCol[i] = Col[i];
    }
}

void Mesh::DrawInstanced(GLfloat PosAndSize[100000], GLfloat ColorAndLight[100000], Camera camera, int n)
{

    glUniform3f(c, color[0], color[1], color[2]);
    glUniform3fv(BubLigCol, LightBubbles, value_ptr(BubbleLightsCol[0]));
    glUniform3fv(BubLigWorldSpace, LightBubbles, value_ptr(BubbleLightsPos[0]));
    glUniform1i(isInstanced, 1);
    GLfloat BubblePosAndSize[n*4];
    GLfloat BubbleColAndLight[n*4];
    for(int i = 0; i < n*4; i++)
    {
        BubblePosAndSize[i] = PosAndSize[i];
        BubbleColAndLight[i] = ColorAndLight[i];
    }

    glBindBuffer(GL_ARRAY_BUFFER, posbuffer);
    glBufferData(GL_ARRAY_BUFFER,  sizeof(BubblePosAndSize), BubblePosAndSize, GL_STREAM_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colbuffer);
    glBufferData(GL_ARRAY_BUFFER,sizeof(BubbleColAndLight), BubbleColAndLight, GL_STREAM_DRAW);

    glUniform3f(t, 4.0f, 30.0f, 15.0f);
    glUniformMatrix4fv(v, 1, GL_FALSE, &camera.View()[0][0]);

    glDrawArraysInstanced(GL_TRIANGLES, shape, v_num, n);
}
