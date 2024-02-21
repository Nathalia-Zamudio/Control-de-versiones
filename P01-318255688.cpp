#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h> 
const int WIDTH = 800, HEIGHT = 800; 
float rojo, verde, azul = 0.0f;
double lastColorChangeTime = 0.0;
GLuint VAO, VBO, shader;
float a = 1 * 0.083333;
float b = 2 * 0.083333, c = 3 * 0.083333, d= 4 * 0.083333, e= 5 * 0.083333, f= 6 * 0.083333, g= 7 * 0.083333, h= 8 * 0.083333, i= 9 * 0.083333, j= 10 * 0.083333, k= 11 * 0.083333;
static const char* vShader = " \n\
#version 330 \n\
layout (location =0) in vec3 pos; \n\
void main() \n\
{ \n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); \n\
}";

static const char* fShader = " \n\
#version 330 \n\
out vec4 color; \n\
void main() \n\
{ \n\
color = vec4(0.0f,0.0f,0.0f,1.0f); \n\
}";

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
	else if (x == 2) {
		rojo = 0.0f;
		verde = 0.0f;
		azul = 1.0f;
	}
}

bool tiempo(double currentTime) {
	return (currentTime - lastColorChangeTime) >= 3.0; 
}

void CrearTriangulo() 
{ 
	GLfloat vertices[] = {

		//N

		-k, a, 0.0f,	//1
		-k, k, 0.0f,
		-i, a, 0.0f,
		
		-k, k, 0.0f,	//2
		-i, a, 0.0f,
		-i, k, 0.0f,

		-i, k, 0.0f,	//3
		-i, g, 0.0f,
		-e, g, 0.0f,

		-i, g, 0.0f,	//4
		-e, g, 0.0f,
		-e, c, 0.0f,

		-e, c, 0.0f,		//5
		-c, e, 0.0f,
		-e, g, 0.0f,

		-c, e, 0.0f,		//6
		-e, c, 0.0f,
		-c, a, 0.0f,

		-c, a, 0.0f,		//7
		-a, k, 0.0f,
		-c, k, 0.0f,

		-c, a, 0.0f,		//8
		-a, k, 0.0f,
		-a, a, 0.0f,
		
		//D

		a, k, 0.0f,		//9
		c, k, 0.0f,
		a, a, 0.0f,

		c, k, 0.0f,		//10
		a, a, 0.0f,
		c, a, 0.0f,

		c, k, 0.0f,		//11
		f, k, 0.0f,
		c, i, 0.0f,

		c, i, 0.0f,		//12
		f, k, 0.0f,
		f, i, 0.0f,

		f, k, 0.0f,		//13
		f, i, 0.0f,
		h, j, 0.0f,

		h, j, 0.0f,		//14
		h, g, 0.0f,
		f, i, 0.0f,

		g, h, 0.0f,		//15
		h, g, 0.0f,
		h, f, 0.0f,

		g, d, 0.0f,		//16
		h, e, 0.0f,
		h, f, 0.0f,

		h, e, 0.0f,		//17
		h, d, 0.0f,
		f, c, 0.0f,

		0.6458f, h, 0.0f,		//18
		0.6458f, e, 0.0f,
		i, f, 0.0f,

		h, j, 0.0f,		//19
		h, g, 0.0f,
		0.7916f, g, 0.0f,

		h, g, 0.0f,		//20
		0.7916f, g, 0.0f,
		h, e, 0.0f,

		0.7916f, g, 0.0f,		//21
		h, e, 0.0f,
		0.7916f, e, 0.0f,

		0.7916f, e, 0.0f,		//22
		h, e, 0.0f,
		h, b, 0.0f,

		h, b, 0.0f,		//23
		h, d, 0.0f,
		f, a, 0.0f,

		f, a, 0.0f,		//24
		h, d, 0.0f,
		f, c, 0.0f,

		f, c, 0.0f,		//25
		f, a, 0.0f,
		c, c, 0.0f,

		c, c, 0.0f,		//26
		c, a, 0.0f,
		f, a, 0.0f,
		
		//Z

		-k, -a, 0.0f,		//27
		-k, -c, 0.0f,
		-a, -a, 0.0f,

		-k, -c, 0.0f,		//28
		-a, -c, 0.0f,
		-a, -a, 0.0f,

		-a, -c, 0.0f,		//29
		-e, -c, 0.0f,
		-e, -g, 0.0f,

		-e, -c, 0.0f,		//30
		-e, -g, 0.0f,
		-i, -g, 0.0f,

		-e, -g, 0.0f,		//31
		-i, -g, 0.0f,
		-g, -i, 0.0f,

		-i, -g, 0.0f,		//32
		-g, -i, 0.0f,
		-k, -i, 0.0f,

		-k, -i, 0.0f,		//33
		-a, -i, 0.0f,
		-k, -k, 0.0f,

		-a, -k, 0.0f,		//34
		-a, -i, 0.0f,
		-k, -k, 0.0f,
		
		// G

		k, -b, 0.0f,		//35
		k, -d, 0.0f,
		j, -c, 0.0f,

		j, -c, 0.0f,		//36
		k, -b, 0.0f,
		j, -a, 0.0f,

		j, -a, 0.0f,		//37
		j, -c, 0.0f,
		d, -c, 0.0f,

		d, -c, 0.0f,		//38
		j, -a, 0.0f,
		d, -a, 0.0f,

		d, -a, 0.0f,		//39
		d, -c, 0.0f,
		b, -c, 0.0f,

		b, -c, 0.0f,		//40
		0.3749f, -c, 0.0f,
		b, -0.4583f, 0.0f,

		c, -d, 0.0f,		//41
		b, -c, 0.0f,
		a, -d, 0.0f,

		a, -d, 0.0f,	//42
		c, -d, 0.0f,
		a, -h, 0.0f,

		a, -h, 0.0f,	//43
		c, -d, 0.0f,
		c, -h, 0.0f,

		a, -h, 0.0f,	//44
		c, -h, 0.0f,
		b, -i, 0.0f,

		b, -i, 0.0f, 	//45
		b, -0.5416f, 0.0f,
		0.3749f, -i, 0.0f,

		b, -i, 0.0f,		//46
		d, -i, 0.0f,
		d, -k, 0.0f,

		d, -i, 0.0f,		//47
		d, -k, 0.0f,
		i, -i, 0.0f,

		i, -k, 0.0f,		//48
		d, -k, 0.0f,
		i, -i, 0.0f,

		i, -i, 0.0f,		//49
		i, -k, 0.0f,
		k, -i, 0.0f,

		k, -i, 0.0f,		//50
		i, -i, 0.0f,
		k, -g, 0.0f,

		i, -i, 0.0f,		//51
		k, -g, 0.0f,
		i, -g, 0.0f,

		h, -i, 0.0f,		//52
		i, -i, 0.0f,
		i, -0.7083f, 0.0f,

		f, -g, 0.0f,		//53
		k, -g, 0.0f,
		k, -0.46f, 0.0f,

		f, -g, 0.0f,		//54
		f, -0.46, 0.0f,
		k, -0.46, 0.0f,

		i, -c, 0.0f,		//55
		j, -c, 0.0f,
		k, -d, 0.0f
	
	}; //x    y    z
	glGenVertexArrays(1, &VAO); 
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);
	glEnableVertexAttribArray(0); 
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) 


{
	GLuint theShader = glCreateShader(shaderType);
	const GLchar* theCode[1];
	theCode[0] = shaderCode;
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);
	glShaderSource(theShader, 1, theCode, codeLength);
	glCompileShader(theShader);
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);
}

void CompileShaders() { 
	shader = glCreateProgram(); 
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);

	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}
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

	glViewport(0, 0, BufferWidth, BufferHeight);

	CrearTriangulo(); 
	CompileShaders();

	while (!glfwWindowShouldClose(mainWindow)) 
	{
		glfwPollEvents(); 
		

		glUseProgram(0);
		while (!glfwWindowShouldClose(mainWindow)) {
			double currentTime = glfwGetTime();
			glfwPollEvents();

			if (tiempo(currentTime)) {
				determinarColor();
				lastColorChangeTime = currentTime;
			}

			glClearColor(rojo, verde, azul, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glUseProgram(shader); 

			glBindVertexArray(VAO); 
			glDrawArrays(GL_TRIANGLES, 0, 165); 
			glBindVertexArray(0); 

			glfwSwapBuffers(mainWindow);
		}

	}
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	return 0;
}