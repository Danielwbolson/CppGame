
#include "glad/glad.h"  //Include order can matter here
#include "glad/glad.c"

#include <SDL.h>
#include <SDL_opengl.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Parse.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Scene.h"
#include "Utility.h"

#define GLM_FORCE_RADIANS //ensure we are using radians
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#define GLM_FORCE_RADIANS //ensure we are using radians
bool fullscreen = false;
int screenWidth = 800;
int screenHeight = 600;

int main(int argc, char* argv[])
{
    SDL_Init(SDL_INIT_VIDEO);  //Initialize Graphics (for OpenGL)

    //Print the version of SDL we are using
    SDL_version comp; SDL_version linked;
    SDL_VERSION(&comp); SDL_GetVersion(&linked);
    printf("\nCompiled against SDL version %d.%d.%d\n", comp.major, comp.minor, comp.patch);
    printf("Linked SDL version %d.%d.%d.\n", linked.major, linked.minor, linked.patch);

    //Ask SDL to get a recent version of OpenGL (3.2 or greater)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    //Create a window (offsetx, offsety, width, height, flags)
    SDL_Window* window = 
        SDL_CreateWindow("My OpenGL Program", 100, 100,
            screenWidth, screenHeight, SDL_WINDOW_OPENGL);
    if (!window) {
        printf("Could not create window: %s\n", SDL_GetError());
        return EXIT_FAILURE; //Exit as SDL failed
    }
    float aspect = screenWidth / (float)screenHeight; //aspect ratio needs update on resize
    SDL_GLContext context = SDL_GL_CreateContext(window); //Bind OpenGL to the window

    if (gladLoadGLLoader(SDL_GL_GetProcAddress)) {
        printf("OpenGL loaded\n");
        printf("Vendor:   %s\n", glGetString(GL_VENDOR));
        printf("Renderer: %s\n", glGetString(GL_RENDERER));
        printf("Version:  %s\n", glGetString(GL_VERSION));
    }
    else {
        printf("ERROR: Failed to initialize OpenGL context.\n");
        return -1;
    }

    // Get input map and scene files
    Map map = Map();
    Scene scene = Scene();
    std::string mapFile = "maps_scenes/Map1.map";
    std::string sceneFile = "maps_scenes/Scene1.scn";

    scene = SceneParse(scene, sceneFile);
    map = MapParse(map, mapFile, &scene);
    // End file parsing

    SDL_Event windowEvent;
    bool quit = false;

    SDL_SetRelativeMouseMode(SDL_TRUE);
    const Uint8* keyboard = SDL_GetKeyboardState(NULL);
    float xRel = 0;
    float yRel = 0;

    glEnable(GL_DEPTH_TEST);
    float startTime = SDL_GetTicks() / 1000.0f;

    while (!quit) {
        SDL_PumpEvents();
        xRel = 0;
        yRel = 0;

        while (SDL_PollEvent(&windowEvent)) {
            if (windowEvent.type == SDL_QUIT) quit = true; //Exit Game Loop
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_ESCAPE)
                quit = true; //Exit Game Loop
            if (windowEvent.type == SDL_KEYUP && windowEvent.key.keysym.sym == SDLK_f) {
                fullscreen = !fullscreen;
                SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);
            }
            if (windowEvent.type == SDL_MOUSEMOTION) {
                xRel = windowEvent.motion.xrel * 0.01f;
                yRel = windowEvent.motion.yrel * 0.01f;
            }
        }

        // Clear the screen to default color
        glClearColor(.2f, 0.4f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float dt = (SDL_GetTicks() / 1000.0f) - startTime;
        startTime = SDL_GetTicks() / 1000.0f;

        scene.SDLInput(keyboard, xRel, yRel);
        scene.CollisionChecks(dt);
        scene.Update(dt);
        scene.Render();

        SDL_GL_SwapWindow(window); //Double buffering
    }

    SDL_GL_DeleteContext(context);
    SDL_Quit();

    return 0;
}
