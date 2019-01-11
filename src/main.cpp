#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#include <SFML/Window.hpp> // nuklear backend
#include "glad/glad.h"     // opengl stuff

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" // support for stdout logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging

#define MAX_VERTEX_BUFFER 512 * 1024 // opengl stuff
#define MAX_ELEMENT_BUFFER 128 * 1024
const std::string log_file = "nuked-dashboard.log";
const std::string window_title = "Nuked Dashboard";
const bool vsync = true;
const sf::VideoMode video_mode = sf::VideoMode(800, 800);

int main(int argc, char **argv)
{
    // apparently this makes the console multithreaded somehow
    auto console = spdlog::stdout_color_mt("console");
    console->info("-- Nuked Dashboard --");

    // log file init
    console->info("Setting up log file");
    try
    {
        // rotate when it gets too big
        auto file_logger = spdlog::rotating_logger_mt("file_logger", log_file, 1024 * 1024 * 5, 3);
    }
    catch (const spdlog::spdlog_ex &ex)
    {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        return 1;
    }

    //sf::Window win;
    // GUI init
    console->info("GUI Initializing");
    sf::ContextSettings settings(24, 8, 4, 3, 3); //TODO figure out what these numbers do and make constants
    sf::Window win(video_mode, window_title, sf::Style::Default, settings);
    win.setVerticalSyncEnabled(vsync);
    win.setActive(true);
    if (!gladLoadGL())
    {
        console->error("Failed to load OpenGL extensions");
        return -1;
    }
    glViewport(0, 0, win.getSize().x, win.getSize().y);

    // GUI input polling
    console->info("Polling for input");
    while (win.isOpen())
    {
        sf::Event evt;
        while (win.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                win.close();
            }
            else if (evt.type == sf::Event::Resized)
            {
                glViewport(0, 0, evt.size.width, evt.size.height);
            }
        }
    }

    return 0;
}