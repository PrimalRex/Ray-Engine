#include <chrono>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>

#include "cpu_renderer.h"

int main() {
    std::cout << "Renderer Warming Up..." << std::endl;

    // Just timestamp each render via filename
    const time_t t = time(nullptr);
    const struct tm *tm = localtime(&t);
    char filename[80];
    strftime(filename, sizeof(filename), "%Y%m%d%H%M%S.ppm", tm);
    std::ofstream image (filename);

    // Tracks rendering duration
    auto wholeprocess_s = std::chrono::high_resolution_clock::now();

    if(image.is_open()) {
        cpu_renderer renderer;

        // PPM header
        image << "P3" << std::endl;
        image << cpu_renderer::GetOutputWidth() << " " << cpu_renderer::GetOutputHeight() << std::endl;
        image << "255" << std::endl;

        Scene main_scene;
        main_scene.Objects.emplace_back(new sphere({0,0,0}, {255,0,0}, {.5,.5,.5}));
        main_scene.Objects.emplace_back(new sphere({0,.2,.2}, {0,0,255}, {1,1,1}));

        // Render
        auto render_s = std::chrono::high_resolution_clock::now();

        renderer.Render(main_scene);

        auto render_e = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_seconds = render_e - render_s;
        std::cout << "Rendering Took " << elapsed_seconds.count() * 1000 << " MS!" << std::endl;

        // Reads the buffer and writes to the PPM file
        for (unsigned int i = 0; i < cpu_renderer::GetOutputHeight() * cpu_renderer::GetOutputWidth(); i++) {
            RGB& pixel = renderer.GetimgBuffer()[i];
            image << int(pixel.r) << " " << int(pixel.g) << " " << int(pixel.b) << '\n';
        }

        image.close();
    }

    auto wholeprocess_e = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_seconds = wholeprocess_e - wholeprocess_s;
    std::cout << "Renderer & Write took " << elapsed_seconds.count() * 1000 << " MS!" << std::endl;

    return 0;
}