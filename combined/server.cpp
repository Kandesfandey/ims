#include "crow.h"
#include "string"
#include "vector"

struct Request {
    std::string request_id;
    std::string name;
    std::string project_owner;
    std::string assigned_manager;

    std::string item_id;

    int quantity;
    int expense;
};

std::vector<Request> requests_db;

void RequestManagementModule(crow::SimpleApp *server) {
    crow::SimpleApp &app = *server;

    CROW_ROUTE(app, "/api/request/new")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            Request new_request{
                reqj["request_id"].s(),
                reqj["name"].s(),
                reqj["project_owner"].s(),
                reqj["assigned_manager"].s(),
                reqj["item_id"].s(),

                reqj["quantity"].i(),
                reqj["expense"].i(),
            };

            requests_db.push_back(new_request);

            // CROW_LOG_INFO << "Pushed: " << *requests_db.end();

            return crow::response(crow::status::ACCEPTED);
        });
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        return "<h1>Hello World</h1>";
    });

    RequestManagementModule(&app);

    app.port(5000)
        .multithreaded()
        .run();
}

// To run:
// g++ server.cpp -lpthread -lboost_system -o app.out