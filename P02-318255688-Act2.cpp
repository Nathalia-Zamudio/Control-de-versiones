//Práctica 2 semestre 2024-2: índices, mesh, proyecciones, transformaciones geométricas

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
float b = 2 * 0.083333, c = 3 * 0.083333, d = 4 * 0.083333, e = 5 * 0.083333, q = 6 * 0.083333, g = 7 * 0.083333, h = 8 * 0.083333, i = 9 * 0.083333, j = 10 * 0.083333, k = 11 * 0.083333, l = 12 * 0.083333, m = 13 * 0.083333;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
static const char* vrojo = "shaders/shaderRojo.vert";
static const char* frojo = "shaders/shaderRojo.frag";
static const char* vazul = "shaders/shaderAzul.vert";
static const char* fazul = "shaders/shaderAzul.frag";
static const char* vcafe = "shaders/shaderCafe.vert";
static const char* fcafe = "shaders/shaderCafe.frag";
static const char* vverde2 = "shaders/shaderVerdeOscuro.vert";
static const char* fverde2 = "shaders/shaderVerdeOscuro.frag";

float angulo = 0.0f;

void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,4,
		0,3,4,
		3,0,2,
		1,0,2,
		1,2,3,
		1,3,4

	};
	GLfloat vertices[] = {
		0.0f, 0.5f, 0.0f,	//0
		0.5f, -0.5f, 0.5f,	//1
		-0.5f, -0.5f, 0.5f,	//2
		-0.5f, -0.5f, -0.5f,	//3
		0.5f, -0.5f, -0.5f, //4
	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 15, 18);
	meshList.push_back(obj1);
}

void CrearCubo()	
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);	//vertices
	meshList.push_back(cubo);
}


void CreateShaders()
{

	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);

	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vrojo, frojo);
	shaderList.push_back(*shader3);

	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vazul, fazul);
	shaderList.push_back(*shader4);

	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vcafe, fcafe);
	shaderList.push_back(*shader5);

	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vverde2, fverde2);
	shaderList.push_back(*shader6);
}


int main()
{
	mainWindow = Window(800, 800);
	mainWindow.Initialise();
	CreaPiramide();
	CrearCubo();
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	glm::mat4 projection = glm::ortho(-2.5f, 2.5f, -1.5f, 5.0f, 0.1f, 100.0f); // proyeccion ortogonal 

	glm::mat4 model(1.0);

	while (!mainWindow.getShouldClose())
	{
		glfwPollEvents();
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//techo
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::scale(model, glm::vec3(2.0f, 2.0, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 1.125f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();
		

		//principal

		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();

		model = glm::mat4(1.0);

		model = glm::scale(model, glm::vec3(1.7f, 2.5f, 1.0f));
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Ventana izquierda
		
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.5f, 0.6f, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.65f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();
		
		//Ventana derecha

		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.5f, 0.6f, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.65f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//Puerta

		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.92f, -2.0f));
		model = glm::scale(model, glm::vec3(0.5f, 0.65f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		//Tonco derecho

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.7f, -0.92f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.65f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		//Tonco izquierdo

		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.7f, -0.92f, -2.0f));
		model = glm::scale(model, glm::vec3(0.4f, 0.65f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();


		//Arbol derecho

		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(1.7f, -0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.19f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		//Arbol izquierdp

		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-1.7f, -0.0f, -2.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.19f, 1.0f));

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();


		glUseProgram(0);
		mainWindow.swapBuffers();

	}
	return 0;
}