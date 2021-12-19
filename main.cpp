
#include <SDL.h>
#include "Camera.h"
#include "Scene.h"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/fetch.h>
#endif

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define SCALE 2

SDL_Renderer *renderer;
SDL_Surface *surface;
Scene *scene;

unsigned int lastRender;
int numFrames = 0;

void render() {
    auto *pixels = (Uint8 *) surface->pixels;
    scene->render(pixels);

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(texture);

    auto currentTime = SDL_GetTicks();
    auto renderTime = currentTime-lastRender;
    lastRender = currentTime;

    std::cout << ++numFrames << ": " << renderTime << std::endl;
}

#ifdef __EMSCRIPTEN__
void downloadFile(string file) {
    string url = "http://localhost:3000/" + file;

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS | EMSCRIPTEN_FETCH_REPLACE;
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, url.c_str()); // Blocks here until the operation is complete
    if (fetch->status == 200) {
        printf("Finished downloading %llu bytes from URL %s.\n", fetch->numBytes, fetch->url);
        // The data is now available at fetch->data[0] through fetch->data[fetch->numBytes-1];
      } else {
        printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
      }
      emscripten_fetch_close(fetch);
}
#endif

int main(int argc, char* args[]) {
    SDL_Window* window;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "could not initialize sdl2: " << SDL_GetError() << std::endl;
        return 1;
    }
    window = SDL_CreateWindow(
            "ray tracer",
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
    );
    if (window == nullptr) {
        std::cerr << "could not create window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto *pixels = new Uint8[SCREEN_WIDTH*SCALE * SCREEN_HEIGHT*SCALE * 3];

    surface = SDL_CreateRGBSurfaceFrom(pixels, SCREEN_WIDTH*SCALE, SCREEN_HEIGHT*SCALE,
                                       24,
                                       SCREEN_WIDTH*SCALE * 3,
                                       0x0000FF,
                                       0x00FF00,
                                       0xFF0000,
                                       0);
    renderer = SDL_CreateRenderer(window, -1, 0);
    scene = new Scene(
            Camera(SCREEN_WIDTH*SCALE, SCREEN_HEIGHT*SCALE, 45, Vector3f(0.0, 3.0, 0.0), Vector3f(0.0, 1.8, 10)),
            vector<Sphere> {
                Sphere(
                        Vector3f(0, 3.5, -3),
                        Vector3f(0, 150, 0),
                        0.2, 0.7, 0.1, 3),
                Sphere(
                        Vector3f(-1.5, 2.0, 1.5),
                        Vector3f(150, 0, 0),
                        0.05, 0.75, 0.2, 1) },
            vector<Light> {
                Light(Vector3f(-10, -5, 20))
            });

#ifdef __EMSCRIPTEN__
    downloadFile("start");
#endif

    lastRender = SDL_GetTicks();

    while(numFrames < 100) {
        SDL_Event event;

        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    goto exit;
            }
        }

        render();
    }

    exit:
    SDL_DestroyWindow(window);
    SDL_Quit();

#ifdef __EMSCRIPTEN__
    downloadFile("stop");
#endif
    return 0;
}