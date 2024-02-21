#include <stdio.h> 
#include <stdlib.h>
#include <glew.h>
#include <glfw3.h> 

const int WIDTH = 800, HEIGHT = 600; 
float rojo, verde, azul = 0.0f;
double cambio = 0.0;

void determinarColor() {
	int x = rand() % 3;
	if (x == 0) {
		rojo = 1.0f;
		verde = 0.0f;
		azul = 0.0f;
	}
	else if (x == 1) {
		rojo = 0.0f;
		verde = 1.0f;
		azul = 0.0f;
	}
	else {
		rojo = 0.0f;
		verde = 0.0f;
		azul = 1.0f;
	}
}

bool tiempo(double currentTime) {
	return (currentTime - cambio) >= 0.5; 
}

int main()
{
	
	if (!glfwInit()) 
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Practica 1", NULL, NULL); 

	if (!mainWindow) 
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	
	int BufferWidth, BufferHeight; 
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight); 

	glfwMakeContextCurrent(mainWindow); 

	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)  
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	
	glViewport(0, 0, BufferWidth, BufferHeight); 
	printf("Version de Opengl: %s \n", glGetString(GL_VERSION)); 
	printf("Marca: %s \n", glGetString(GL_VENDOR)); 
	printf("Renderer: %s \n", glGetString(GL_RENDERER)); 
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION)); 
	while (!glfwWindowShouldClose(mainWindow)) 
	{
		glfwPollEvents(); 
		while (!glfwWindowShouldClose(mainWindow)) {
			double currentTime = glfwGetTime();
			glfwPollEvents();

			if (tiempo(currentTime)) {
				determinarColor();
				cambio = currentTime;
			}

			glClearColor(rojo, verde, azul, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(mainWindow);
		}
	}
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}