#include <iostream>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h" //support for stdout logging
#include "spdlog/sinks/rotating_file_sink.h" // support for rotating file logging

#define NUKLEAR_IMPLEMENTATION
#include "nuklear.h"

#define LOG_FILE "nuked-dashboard.log"

int main(int argc, char ** argv)
{
    // apparently this makes the console multithreaded somehow
    auto console = spdlog::stdout_color_mt("console");
    console->info("-- Nuked Dashboard --");

    // log file init
    try
    {
        // rotate when it gets too big
        auto file_logger = spdlog::rotating_logger_mt("file_logger", LOG_FILE, 1024 * 1024 * 5, 3);
    }
    catch (const spdlog::spdlog_ex& ex)
    {
        std::cerr << "Log initialization failed: " << ex.what() << std::endl;
        return 1;
    }
    
    // GUI init
    console->info("GUI Initializing");

    //std::cout << "Hello, world!" << std::endl;
    return 0;
}