#include <iostream>

#include "gtk_app.h"
#include "logger.h"


int main(int argc, char * argv[]) {
    LOG("Hello world!")

    for (int i = 0; i < argc; ++i) {
        std::cout << "arg[" << i << "] : " << argv[i] << std::endl;
    }
    std::cout << std::endl;

    auto app = gtk_app::create();
    return app->run(argc, argv);
}