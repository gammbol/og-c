#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define SCR_WIDTH 800
#define SCR_HEIGHT 600

const char* readShader(char *path);
void processInput(GLFWwindow *window);
void windowResize(GLFWwindow *window, int width, int height);

int main(void) {
	// GLFW initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// this makes opengl work on mac :)
#ifdef APPLE
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// creating a window
	GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LOGL", NULL, NULL);
	if (!window) {
		printf("ERROR: Failed to create GLFW window\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, windowResize);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		printf("ERROR: Failed to initialize GLAD\n");
		return -1;
	}

	// vertices and indices
	float vertices[] = {
		0.0f, -0.5f, -0.5f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,  // top left
		0.5f, -0.5f, 0.0f,  // bottom right
		0.5f, 0.5f, 0.0f,   // top right
	};
	unsigned int indices[] = {
		0, 1, 2,	// first triangle
		1, 2, 3,	// second triangle
	};

	//vertex array object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// vertex buffer object
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// element buffer object
	unsigned int EBO;       
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// linking vertex attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) sizeof(float));

	// unbinding VAO
	glBindVertexArray(0);


	// compiling vertex shader
	const char *vert = readShader("shaders/shader.vert");

	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vert, NULL);
	glCompileShader(vertexShader);

	// compiling fragment shader
	const char *frag = readShader("shaders/shader.frag");

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	glShaderSource(fragmentShader, 1, &frag, NULL);
	glCompileShader(fragmentShader);

	// checking shaders compilation status
	int success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		printf("ERROR: Vertex Shader\n%s\n", infoLog);
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		printf("ERROR: Fragment Shader\n%s\n", infoLog);
	}

	// shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// deleting shaders after linking
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// checking shader program linking status
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		printf("ERROR: Linking shader program\n%s\n", infoLog);
	}

	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.6f, 1.0f, 0.9f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);		


		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

const char* readShader(char *path) {
	fflush(stdin);

	FILE *fp;
	fp = fopen(path, "r");

	char *res = 0;
	int length = 0;
	char buffer[256];

	if(fp) {
		while (fgets(buffer, 256, fp)) {
			res = realloc(res, strlen(buffer) + length + 1);
			memcpy(res+length, buffer, strlen(buffer));
			length += strlen(buffer);
			res[length] = '\0';
		}
	}
	else
		printf("ERROR: Reading shader!\n");

	fclose(fp);

	fflush(stdin);
	return res;

}
		

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void windowResize(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}
