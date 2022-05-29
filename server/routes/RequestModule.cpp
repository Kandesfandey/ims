#include "crow.h"
#include "vector"
#include "../controllers/RequestController.h"

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