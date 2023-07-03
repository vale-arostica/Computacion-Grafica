#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // the position variable has attribute position 0
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
// Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
" FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";


int main() {
	//Inicializar GLFW
	glfwInit();

	//Configurar GLFW, qué version estamos usando
	// En este caso, usamos OpenGl 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Decirle a GLF que use el CORE profile
	//Esto es para que no use funciones viejas de OpenGL (sólo modernas)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Definir los vertices del triangulo
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3))/3, 0.0f, // bottom left corner
		 0.5f, -0.5f * float(sqrt(3))/3, 0.0f, // bottom right corner
		 0.0f,  0.5f * float(sqrt(3)) * 2 / 3, 0.0f  // top   
	};


	// Crear una ventana de GLFW, de 800x800, con el nombre "pruebita"
	GLFWwindow* window = glfwCreateWindow(800, 800, "pruebita", NULL, NULL);
	if (window == NULL) // Checkeo de errores al abrir la window
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Hacer que la ventana se introduzca en el contexto principal
	glfwMakeContextCurrent(window);

	// Inicializar GLAD, que es el que maneja los punteros a funciones de OpenGL
	gladLoadGL();

	// Definir el viewport de OpenGL
	// En este caso, va desde x=0, y=0, hasta x=800, y=800
	glViewport(0, 0, 800, 800);

	// crear los shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Asignarle el codigo fuente al shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compilar el shader
	glCompileShader(vertexShader);

	// Repetir para el fragment shader
	GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// Crear el shader program
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);

	// Linkear todos los shaders juntos en el shader program
	glLinkProgram(shaderProgram);

	// Borrar los shaders, ya que no los necesitamos más
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Crear cointainers para el Vertez Aarray Object y el VBO (Vertex Buffer Object)
	GLuint VAO, VBO;
	// Generar los objetos
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bindear el VAO primero, luego el VBO, y luego especificar los datos del vertice
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Especificar los atributos de los vertices, así OpenGL sabe cómo interpretar el VBO
	glVertexAttribPointer(
		0, // atributo 0. No hay atributos en este caso, pero es necesario ponerlo
		3, // tamaño de los atributos
		GL_FLOAT, // tipo de los atributos
		GL_FALSE, // si los atributos deben ser normalizados
		3 * sizeof(float), // stride
		(void*)0 // offset de los atributos en el VBO
	);
	// Habilitar el atributo 0, así OnenGL sabe que debe usarlo
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// Especificar el color de fondo
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	// Limpiar el back buffer y asignarle el nuevo color
	glClear(GL_COLOR_BUFFER_BIT);
	// Intercambiar el back buffer con el front buffer
	glfwSwapBuffers(window);

	// Bucle del main
	while (!glfwWindowShouldClose(window))
	{
		// Especificar el color de fondo
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
		// Limpiar el back buffer y asignarle el nuevo color
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		// Se ocupa de los eventos de GLFW
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// Terminar GLFW, limpiar todos los recursos
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
