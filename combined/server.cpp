#include "crow.h"
#include "string"
#include "vector"

struct Request {
    std::string request_id;
    std::string name;
    std::string project_owner;
    std::string assigned_manager;
    std::string status;
    std::string item_id;

    int quantity;
    int expense;
};

struct Inventory_Lists{
    std::string name;
    std::string type;
    std::string inventory_id;
    int quantity;
    int life;

    std::string convertString()
    {
        std::string alpha = "{ name: " + name + ", inventory_id " + inventory_id + ", type:" + type + ", quantity"+ std::to_string(int(quantity)) + ", life: "+std::to_string(int(life))+"}," ;

        return alpha;
    }

};

std::vector<Request> requests_db;
std::vector<Inventory_Lists> inventory_lists_db;

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
                "Pending",
                reqj["item_id"].s(),

                int(reqj["quantity"].i()),
                int(reqj["expense"].i()),
            };

            requests_db.push_back(new_request);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/list/add")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            Inventory_Lists new_request{
                reqj["name"].s(),
                reqj["type"].s(),
                reqj["inventory_id"].s(),
                int(reqj["life"].i()),
                int(reqj["quantity"].i()),
            };

            inventory_lists_db.push_back(new_request);

            // CROW_LOG_INFO << "Pushed: " << *requests_db.end();

            return crow::response(crow::status::ACCEPTED);
        });

    CROW_ROUTE(app, "/api/list/edit")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            Inventory_Lists new_request{
                reqj["name"].s(),
                reqj["type"].s(),
                reqj["inventory_id"].s(),
                int(reqj["life"].i()),
                int(reqj["quantity"].i()),
            };

            for(auto &x:inventory_lists_db){
                if(x.inventory_id==reqj["inventory_id"].s()){
                    x = new_request;
                }
            }

            // CROW_LOG_INFO << "Pushed: " << *requests_db.end();

            return crow::response(crow::status::ACCEPTED);
        });

    CROW_ROUTE(app, "/api/list/delete")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            for (auto i = inventory_lists_db.begin(); i != inventory_lists_db.end(); ++i) {
                if ((*i).inventory_id==reqj["inventory_id"].s()) {
                    inventory_lists_db.erase(i);
                    i--;
                }
            }

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

    CROW_ROUTE(app, "/api/list/view")
    ([]() {
        std::string main_str = "[";

        crow::json::wvalue x;

        for(auto &x:inventory_lists_db){
            main_str+=x.convertString();
        }

        main_str+="]";

        return main_str;
    });

    RequestManagementModule(&app);

    app.port(5000)
        .multithreaded()
        .run();
}

// To run:
// g++ combined/server.cpp -lpthread -lboost_system -o app.out