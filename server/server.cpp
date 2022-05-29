#include "crow.h"

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        return "<h1>Hello World</h1>";
    });

    app.port(5000).multithreaded().run();
}

// To run:
// g++ server.cpp -lpthread -lboost_system