//Ejercicio 1: Dibujar las iniciales de sus nombres, cada letra de un color diferente

#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp> 

#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

const float toRadians = 3.14159265f / 180.0;

float a = 1 * 0.083333;
float b = 2 * 0.083333f, c = 3 * 0.083333, d = 4 * 0.083333, e = 5 * 0.083333, v = 6 * 0.083333, g = 7 * 0.083333, h = 8 * 0.083333, i = 9 * 0.083333, j = 10 * 0.083333, k = 11 * 0.083333;

Window mainWindow; 
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";


float angulo = 0.0f; 

void CrearLetrasyFiguras()
{
	GLfloat vertices_letrasG[] = {

		//N

		-k, a, 0.5f,	1.0f,	0.0f,	0.0f,//1
		-k, k, 0.5f,	1.0f,	0.0f,	0.0f,
		-i, a, 0.5f,	1.0f,	0.0f,	0.0f,

		-k, k, 0.5f,	1.0f,	0.0f,	0.0f,	//2
		-i, a, 0.5f,	1.0f,	0.0f,	0.0f,
		-i, k, 0.5f,	1.0f,	0.0f,	0.0f,

		-i, k, 0.5f,	1.0f,	0.0f,	0.0f,	//3
		-i, g, 0.5f,	1.0f,	0.0f,	0.0f,
		-e, g, 0.5f,	1.0f,	0.0f,	0.0f,

		-i, g, 0.5f,	1.0f,	0.0f,	0.0f,	//4
		-e, g, 0.5f,	1.0f,	0.0f,	0.0f,
		-e, c, 0.5f,	1.0f,	0.0f,	0.0f,

		-e, c, 0.5f,	1.0f,	0.0f,	0.0f,		//5
		-c, e, 0.5f,	1.0f,	0.0f,	0.0f,
		-e, g, 0.5f,	1.0f,	0.0f,	0.0f,

		-c, e, 0.5f,	1.0f,	0.0f,	0.0f,		//6
		-e, c, 0.5f,	1.0f,	0.0f,	0.0f,
		-c, a, 0.5f,	1.0f,	0.0f,	0.0f,

		-c, a, 0.5f,	1.0f,	0.0f,	0.0f,		//7
		-a, k, 0.5f,	1.0f,	0.0f,	0.0f,
		-c, k, 0.5f,	1.0f,	0.0f,	0.0f,

		-c, a, 0.5f,	1.0f,	0.0f,	0.0f,		//8
		-a, k, 0.5f,	1.0f,	0.0f,	0.0f,
		-a, a, 0.5f,	1.0f,	0.0f,	0.0f,


		//D

		a, k, 0.5f,		0.0f,	1.0f,	0.0f,	//9
		c, k, 0.5f,		0.0f,	1.0f,	0.0f,
		a, a, 0.5f,		0.0f,	1.0f,	0.0f,

		c, k, 0.5f,		0.0f,	1.0f,	0.0f,	//10
		a, a, 0.5f,		0.0f,	1.0f,	0.0f,
		c, a, 0.5f,		0.0f,	1.0f,	0.0f,

		c, k, 0.5f,		0.0f,	1.0f,	0.0f,		//11
		v, k, 0.5f,		0.0f,	1.0f,	0.0f,
		c, i, 0.5f,		0.0f,	1.0f,	0.0f,

		c, i, 0.5f,		0.0f,	1.0f,	0.0f,	//12
		v, k, 0.5f,		0.0f,	1.0f,	0.0f,
		v, i, 0.5f,		0.0f,	1.0f,	0.0f,

		v, k, 0.5f,		0.0f,	1.0f,	0.0f,	//13
		v, i, 0.5f,		0.0f,	1.0f,	0.0f,
		h, j, 0.5f,		0.0f,	1.0f,	0.0f,

		h, j, 0.5f,		0.0f,	1.0f,	0.0f,	//14
		h, g, 0.5f,		0.0f,	1.0f,	0.0f,
		v, i, 0.5f,		0.0f,	1.0f,	0.0f,

		g, h, 0.5f,		0.0f,	1.0f,	0.0f,	//15
		h, g, 0.5f,		0.0f,	1.0f,	0.0f,
		h, v, 0.5f,		0.0f,	1.0f,	0.0f,

		g, d, 0.5f,		0.0f,	1.0f,	0.0f,		//16
		h, e, 0.5f,		0.0f,	1.0f,	0.0f,
		h, v, 0.5f,		0.0f,	1.0f,	0.0f,

		h, e, 0.5f,		0.0f,	1.0f,	0.0f,		//17
		h, d, 0.5f,		0.0f,	1.0f,	0.0f,
		v, c, 0.5f,		0.0f,	1.0f,	0.0f,

		0.6458f, h, 0.5f,		0.0f,	1.0f,	0.0f,		//18
		0.6458f, e, 0.5f,		0.0f,	1.0f,	0.0f,
		i, v, 0.5f,		0.0f,	1.0f,	0.0f,

		h, j, 0.5f,		0.0f,	1.0f,	0.0f,		//19
		h, g, 0.5f,		0.0f,	1.0f,	0.0f,
		0.7916f, g, 0.5f,		0.0f,	1.0f,	0.0f,

		h, g, 0.5f,		0.0f,	1.0f,	0.0f,		//20
		0.7916f, g, 0.5f,		0.0f,	1.0f,	0.0f,
		h, e, 0.5f,		0.0f,	1.0f,	0.0f,

		0.7916f, g, 0.5f,		0.0f,	1.0f,	0.0f,		//21
		h, e, 0.5f,		0.0f,	1.0f,	0.0f,
		0.7916f, e, 0.5f,		0.0f,	1.0f,	0.0f,

		0.7916f, e, 0.5f,		0.0f,	1.0f,	0.0f,		//22
		h, e, 0.5f,		0.0f,	1.0f,	0.0f,
		h, b, 0.5f,		0.0f,	1.0f,	0.0f,

		h, b, 0.5f,		0.0f,	1.0f,	0.0f,		//23
		h, d, 0.5f, 0.0f, 1.0f, 0.0f,
		v, a, 0.5f, 0.0f, 1.0f, 0.0f,

		v, a, 0.5f, 0.0f, 1.0f, 0.0f,		//24
		h, d, 0.5f, 0.0f, 1.0f, 0.0f,
		v, c, 0.5f, 0.0f, 1.0f, 0.0f,

		v, c, 0.5f, 0.0f, 1.0f, 0.0f,		//25
		v, a, 0.5f, 0.0f, 1.0f, 0.0f,
		c, c, 0.5f, 0.0f, 1.0f, 0.0f,

		c, c, 0.5f, 0.0f, 1.0f, 0.0f,		//26
		c, a, 0.5f, 0.0f, 1.0f, 0.0f,
		v, a, 0.5f, 0.0f, 1.0f, 0.0f,



		//Z

		-k, -a, 0.5f,	0.0f, 0.0f, 1.0f,		//27
		-k, -c, 0.5f, 0.0f, 0.0f, 1.0f,
		-a, -a, 0.5f, 0.0f, 0.0f, 1.0f,

		-k, -c, 0.5f, 0.0f, 0.0f, 1.0f,		//28
		-a, -c, 0.5f, 0.0f, 0.0f, 1.0f,
		-a, -a, 0.5f, 0.0f, 0.0f, 1.0f,

		-a, -c, 0.5f, 0.0f, 0.0f, 1.0f,		//29
		-e, -c, 0.5f, 0.0f, 0.0f, 1.0f,
		-e, -g, 0.5f, 0.0f, 0.0f, 1.0f,

		-e, -c, 0.5f, 0.0f, 0.0f, 1.0f,		//30
		-e, -g, 0.5f, 0.0f, 0.0f, 1.0f,
		-i, -g, 0.5f, 0.0f, 0.0f, 1.0f,

		-e, -g, 0.5f, 0.0f, 0.0f, 1.0f,		//31
		-i, -g, 0.5f, 0.0f, 0.0f, 1.0f,
		-g, -i, 0.5f, 0.0f, 0.0f, 1.0f,

		-i, -g, 0.5f, 0.0f, 0.0f, 1.0f,		//32
		-g, -i, 0.5f, 0.0f, 0.0f, 1.0f,
		-k, -i, 0.5f, 0.0f, 0.0f, 1.0f,

		-k, -i, 0.5f, 0.0f, 0.0f, 1.0f,		//33
		-a, -i, 0.5f, 0.0f, 0.0f, 1.0f,
		-k, -k, 0.5f, 0.0f, 0.0f, 1.0f,

		-a, -k, 0.5f, 0.0f, 0.0f, 1.0f,		//34
		-a, -i, 0.5f, 0.0f, 0.0f, 1.0f,
		-k, -k, 0.5f, 0.0f, 0.0f, 1.0f,



		// G

		k, -b, 0.5f,	1.0f, 1.0f, 0.0f,		//35
		k, -d, 0.5f, 1.0f, 1.0f, 0.0f,
		j, -c, 0.5f, 1.0f, 1.0f, 0.0f,

		j, -c, 0.5f, 1.0f, 1.0f, 0.0f,		//36
		k, -b, 0.5f, 1.0f, 1.0f, 0.0f,
		j, -a, 0.5f, 1.0f, 1.0f, 0.0f,

		j, -a, 0.5f, 1.0f, 1.0f, 0.0f,		//37
		j, -c, 0.5f, 1.0f, 1.0f, 0.0f,
		d, -c, 0.5f, 1.0f, 1.0f, 0.0f,

		d, -c, 0.5f, 1.0f, 1.0f, 0.0f,		//38
		j, -a, 0.5f, 1.0f, 1.0f, 0.0f,
		d, -a, 0.5f, 1.0f, 1.0f, 0.0f,

		d, -a, 0.5f, 1.0f, 1.0f, 0.0f,		//39
		d, -c, 0.5f, 1.0f, 1.0f, 0.0f,
		b, -c, 0.5f, 1.0f, 1.0f, 0.0f,

		b, -c, 0.5f, 1.0f, 1.0f, 0.0f,		//40
		0.3749f, -c, 0.5f, 1.0f, 1.0f, 0.0f,
		b, -0.4583f, 0.5f, 1.0f, 1.0f, 0.0f,

		c, -d, 0.5f, 1.0f, 1.0f, 0.0f,	//41
		b, -c, 0.5f, 1.0f, 1.0f, 0.0f,
		a, -d, 0.5f, 1.0f, 1.0f, 0.0f,

		a, -d, 0.5f, 1.0f, 1.0f, 0.0f,	//42
		c, -d, 0.5f, 1.0f, 1.0f, 0.0f,
		a, -h, 0.5f, 1.0f, 1.0f, 0.0f,

		a, -h, 0.5f, 1.0f, 1.0f, 0.0f,	//43
		c, -d, 0.5f, 1.0f, 1.0f, 0.0f,
		c, -h, 0.5f, 1.0f, 1.0f, 0.0f,

		a, -h, 0.5f, 1.0f, 1.0f, 0.0f,	//44
		c, -h, 0.5f, 1.0f, 1.0f, 0.0f,
		b, -i, 0.5f, 1.0f, 1.0f, 0.0f,

		b, -i, 0.5f, 1.0f, 1.0f, 0.0f,	//45
		b, -0.5416f, 0.5f, 1.0f, 1.0f, 0.0f,
		0.3749f, -i, 0.5f, 1.0f, 1.0f, 0.0f,

		b, -i, 0.5f, 1.0f, 1.0f, 0.0f,	//46
		d, -i, 0.5f, 1.0f, 1.0f, 0.0f,
		d, -k, 0.5f, 1.0f, 1.0f, 0.0f,

		d, -i, 0.5f, 1.0f, 1.0f, 0.0f,		//47
		d, -k, 0.5f, 1.0f, 1.0f, 0.0f,
		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,

		i, -k, 0.5f, 1.0f, 1.0f, 0.0f,		//48
		d, -k, 0.5f, 1.0f, 1.0f, 0.0f,
		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,

		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,	//49
		i, -k, 0.5f, 1.0f, 1.0f, 0.0f,
		k, -i, 0.5f, 1.0f, 1.0f, 0.0f,

		k, -i, 0.5f, 1.0f, 1.0f, 0.0f,	//50
		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,
		k, -g, 0.5f, 1.0f, 1.0f, 0.0f,

		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,		//51
		k, -g, 0.5f, 1.0f, 1.0f, 0.0f,
		i, -g, 0.5f, 1.0f, 1.0f, 0.0f,

		h, -i, 0.5f, 1.0f, 1.0f, 0.0f,		//52
		i, -i, 0.5f, 1.0f, 1.0f, 0.0f,
		i, -0.7083f, 0.5f, 1.0f, 1.0f, 0.0f,

		v, -g, 0.5f, 1.0f, 1.0f, 0.0f,	//53
		k, -g, 0.5f, 1.0f, 1.0f, 0.0f,
		k, -0.46f, 0.5f, 1.0f, 1.0f, 0.0f,

		v, -g, 0.5f, 1.0f, 1.0f, 0.0f,	//54
		v, -0.46, 0.5f, 1.0f, 1.0f, 0.0f,
		k, -0.46, 0.5f, 1.0f, 1.0f, 0.0f,

		i, -c, 0.5f, 1.0f, 1.0f, 0.0f,	//55
		j, -c, 0.5f, 1.0f, 1.0f, 0.0f,
		k, -d, 0.5f, 1.0f, 1.0f, 0.0f,
	};
	MeshColor* letrasG = new MeshColor();
	letrasG->CreateMeshColor(vertices_letrasG, 990);
	meshColorList.push_back(letrasG);
}


void CreateShaders()
{
	Shader* shader1 = new Shader(); 
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise(); 

	CrearLetrasyFiguras(); 
	CreateShaders();
	GLuint uniformProjection = 0; 
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-2.5f, 2.5f, -1.5f, 5.0f, 0.1f, 100.0f);
	

	while (!mainWindow.getShouldClose())
	{

		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		glm::mat4 model(1.0);

		model = glm::scale(model, glm::vec3(2.5f, 3.0f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();

		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}
