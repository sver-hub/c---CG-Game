#include "common.h"
#include "Image.h"
#include "Field.h"
#include "FadeController.h"
#include <iostream>
#include <vector>

#define GLFW_DLL
#include <GLFW/glfw3.h>

struct InputState {
    bool keys[1024]{}; //массив состояний кнопок - нажата/не нажата
    GLfloat lastX = 400, lastY = 300; //исходное положение мыши
    bool firstMouse = true;
    bool captureMouse         = true;  // Мышка захвачена нашим приложением или нет?
    bool capturedMouseJustNow = false;
} static Input;

const GLfloat frameTime = 1./fps;
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
GLfloat sinceLastAction = 0.0f;
GLfloat frameTimer = .0f;
FadeController fade;
Sprites *sprites;
std::vector<Field*> levels;
int currentLevel = 0;


void OnKeyboardPressed(GLFWwindow* window, int key, int scancode, int action, int mode) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS)
			glfwSetWindowShouldClose(window, GL_TRUE);
		break;

    case GLFW_KEY_1:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        break;

    case GLFW_KEY_2:
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        break;

	default:
		if (action == GLFW_PRESS)
            Input.keys[key] = true;
		else if (action == GLFW_RELEASE)
            Input.keys[key] = false;
	}
}

void processPlayerMovement(Field &field) {
    if (sinceLastAction < turnDelay) return;

    if (Input.keys[GLFW_KEY_W])
        field.ProcessInput(MovementDir::UP);
    else if (Input.keys[GLFW_KEY_S])
        field.ProcessInput(MovementDir::DOWN);
    else if (Input.keys[GLFW_KEY_A])
        field.ProcessInput(MovementDir::LEFT);
    else if (Input.keys[GLFW_KEY_D])
        field.ProcessInput(MovementDir::RIGHT);
    else return;

    sinceLastAction = .0f;
}

void OnMouseButtonClicked(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        Input.captureMouse = !Input.captureMouse;

    if (Input.captureMouse) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        Input.capturedMouseJustNow = true;
    } else
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

}

void OnMouseMove(GLFWwindow* window, double xpos, double ypos) {
    if (Input.firstMouse) {
        Input.lastX = float(xpos);
        Input.lastY = float(ypos);
        Input.firstMouse = false;
    }

    GLfloat xoffset = float(xpos) - Input.lastX;
    GLfloat yoffset = Input.lastY - float(ypos);

    Input.lastX = float(xpos);
    Input.lastY = float(ypos);
}


void OnMouseScroll(GLFWwindow* window, double xoffset, double yoffset) {
  // ...
}


int initGL() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return -1;
	}

	std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    std::cout << "Controls: "<< std::endl;
    std::cout << "press right mouse button to capture/release mouse cursor  "<< std::endl;
    std::cout << "W, A, S, D - movement  "<< std::endl;
    std::cout << "press ESC to exit" << std::endl;

	return 0;
}

void doFadeOut(Image &screen) {
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            screen.multPixel(x,y, fade.outCurve());
        }
    }
    fade.state--;

    if (fade.finished()) {
        if (fade.showLabel) {
            screen.putScreen(currentLevel == 0 ? sprites->level1 : sprites->level2);
        } else {
            levels[currentLevel]->draw(screen);
        }
        fade.setFadedOut();
    }
}

void doFadeIn(Image &screen) {
    if (fade.showLabel) {
        screen.putScreen(currentLevel == 0 ? sprites->level1 : sprites->level2);
    } else {
        levels[currentLevel]->draw(screen);
        levels[currentLevel]->redraw(screen);
    }

    for (int y = 0; y < SCREEN_HEIGHT; y++) {
        for (int x = 0; x < SCREEN_WIDTH; x++) {
            screen.multPixel(x,y, fade.inCurve());
        }
    }
    fade.state--;

    if (fade.finished()) {
        fade.setFadedIn();
    }
}

int main(int argc, char** argv) {
	if(!glfwInit())
        return -1;

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);

    GLFWwindow*  window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "gachi dungeon", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window); 

	glfwSetKeyCallback        (window, OnKeyboardPressed);  
	glfwSetCursorPosCallback  (window, OnMouseMove); 
    glfwSetMouseButtonCallback(window, OnMouseButtonClicked);
	glfwSetScrollCallback     (window, OnMouseScroll);

	if(initGL() != 0) 
		return -1;
	
  //Reset any OpenGL errors which could be present for some reason
	GLenum gl_error = glGetError();
	while (gl_error != GL_NO_ERROR)
		gl_error = glGetError();
  
  
  // initialize
	Image tiles("./resources/tiles.png");
    Image words("./resources/words.png");
    sprites = Sprites::GetInstance();
    sprites->load(tiles, words);

	Image screenBuffer(SCREEN_WIDTH, SCREEN_HEIGHT, 4);

    levels.push_back(new Field("resources/level1.txt"));
    levels.push_back(new Field("resources/level2.txt"));
  
    // levels[currentLevel]->draw(screenBuffer);
    screenBuffer.putScreen(sprites->level1);

    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);  GL_CHECK_ERRORS;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); GL_CHECK_ERRORS;

  //game loop
	while (!glfwWindowShouldClose(window)) {
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
        sinceLastAction += deltaTime;
        frameTimer += deltaTime;

        glfwPollEvents();
    
        if (!fade.inProgress()) processPlayerMovement(*levels[currentLevel]);

        if (frameTimer < frameTime) continue;

        if (!fade.inProgress()) levels[currentLevel]->redraw(screenBuffer);

        if (fade.out) doFadeOut(screenBuffer); 

        if (fade.in) doFadeIn(screenBuffer);
        
        frameTimer = .0f;

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); GL_CHECK_ERRORS;
        glDrawPixels (SCREEN_WIDTH, SCREEN_HEIGHT, GL_RGBA, GL_UNSIGNED_BYTE, screenBuffer.getData()); GL_CHECK_ERRORS;

        glfwSwapBuffers(window);

        if (levels[currentLevel]->isExited()) {
            fade.start();
            currentLevel++;
        }
	}

	glfwTerminate();
	return 0;
}
