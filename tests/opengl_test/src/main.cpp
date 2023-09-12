#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <SDL2/SDL.h>
#include <iostream>
#include "include/shader.h"
#include "SOIL/SOIL.h"

int main()
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute (SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //OpenGL core profile
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MAJOR_VERSION, 3); //OpenGL 3+
    SDL_GL_SetAttribute (SDL_GL_CONTEXT_MINOR_VERSION, 3); //OpenGL 3.3
	SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

	

	SDL_Window *window = SDL_CreateWindow("OpenGL + SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);

	SDL_GLContext glcontext = SDL_GL_CreateContext(window);

	if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
	{
    	std::cout << "Failed to initialize GLAD" << std::endl;
    	return -1;
	}

	Shader shader("/home/slavkotm/projects/mystery/tests/opengl_test/shaders/ss_v.glsl", "/home/slavkotm/projects/mystery/tests/opengl_test/shaders/ss_f.glsl");

	GLfloat vertices[] = {
    	0.5f, 0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
    	0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   -0.5f, 0.5f, 0.0f,   0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};  

	GLuint indices[] = {  // Помните, что мы начинаем с 0!
	    0, 1, 3,   // Первый треугольник
    	1, 2, 3    // Второй треугольник
	};  
	
	GLuint EBO;
	glGenBuffers(1, &EBO);

	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT,GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);  
	
	glBindVertexArray(0);

	GLint nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	std::cout << sizeof(vertices) << std::endl;


	GLuint texture;
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height;
	unsigned char* image = SOIL_load_image("/home/slavkotm/projects/mystery/tests/game_sdl/assets/aaa.png", &width, &height, 0, SOIL_LOAD_RGB);	

	std::cout << width << ", " << height << std::endl;	
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

	SDL_Event event;
	bool running = true;
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	while (running)
	{
    	while (SDL_PollEvent(&event) != 0)
    	{
        	if (event.type == SDL_QUIT)
        	{
            	running = false;
        	}
    	}
   	    // Заливка кадра чёрным цветом средствами OpenGL
    	glClearColor(0,0,0,1);
    	glClear(GL_COLOR_BUFFER_BIT);
	
		glBindTexture(GL_TEXTURE_2D, texture);		

        shader.use();
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the screen buffers

    	// Обновление и рисование сцены
    	//UpdateCurrentScene();
    	//DrawCurrentScene();
    	// В конце - вывод нарисованного кадра в окно на экране
    	SDL_GL_SwapWindow(window);
	}
	

	SDL_GL_DeleteContext(glcontext);

	return 0;
}
