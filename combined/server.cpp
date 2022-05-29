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

    std::string convertString()
    {
        std::string alpha = "{'request_id': '" + request_id + "', 'name': '" + name + "', 'project_owner': '" + project_owner+ "', 'assigned_manager': '" + assigned_manager + "', 'status': '" + status + "', 'item_id': '"+ item_id+ ", 'quantity': " + std::to_string(int(quantity)) + ", 'expense': "+ std::to_string(int(expense)) +"}|"; ;

        return alpha;
    }
};

struct Owner{
    std::string owner_id;
};

struct Inventory_Lists{
    std::string name;
    std::string type;
    std::string inventory_id;
    std::string priority;
    std::string expense_type;

    int available;
    int quantity;
    int life;

    std::string convertString()
    {
        std::string alpha = "{ 'name': '" + name + "', 'inventory_id': '" + inventory_id + "', 'type':'" + type + "', 'priority': '" + priority + "', 'quantity': '"+ std::to_string(int(quantity)) + "', 'available': '" + std::to_string(int(available)) + ", 'expense_type': '" + expense_type + "', 'life': '"+std::to_string(int(life))+"'}|" ;

        return alpha;
    }

};

struct Billing{
    std::string bill_id;
    std::string item_id;
    std::string user_id;
    std::string manager_id;

    int price;
    int quantity;

    std::string convertString()
    {
        std::string alpha =  "{'bill_id': '"+ bill_id + "', 'item_id': '" + item_id + "', 'user_id': '" + user_id + "', 'manager_id': '"+ manager_id + "', 'price': '" + std::to_string(int(price)) + "', 'quantity': '" + std::to_string(int(quantity)) +"' }|";

        return alpha;
    }
};

std::vector<Billing> billing_db;
std::vector<Request> requests_db;
std::vector<Inventory_Lists> inventory_lists_db;

void RequestManagementModule(crow::SimpleApp *server) {
    crow::SimpleApp &app = *server;

    CROW_ROUTE(app, "/api/request/add")
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

    CROW_ROUTE(app, "/api/request/accept")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            for(auto &x:requests_db){
                if(x.item_id==reqj["request_id"].s()){
                    x.status = "Pass";
                }
            }


            // CROW_LOG_INFO << "Pushed: " << *requests_db.end();

            return crow::response(crow::status::ACCEPTED);
        });

    CROW_ROUTE(app, "/api/request/reject")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            for(auto &x:requests_db){
                if(x.item_id==reqj["request_id"].s()){
                    x.status = "Failed";
                }
            }


            return crow::response(crow::status::ACCEPTED);
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
                reqj["priority"].s(),
                reqj["expense_type"].s(),
                int(reqj["available"].i()),
                int(reqj["life"].i()),
                int(reqj["quantity"].i()),
            };

            inventory_lists_db.push_back(new_request);

            // CROW_LOG_INFO << "Pushed: " << *requests_db.end();

            return crow::response(crow::status::ACCEPTED);
        });

    CROW_ROUTE(app, "/api/bill/add")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            Billing new_request{
                reqj["bill_id"].s(),
                reqj["item_id"].s(),
                reqj["user_id"].s(),
                reqj["manager_id"].s(),
                int(reqj["price"].i()),
                int(reqj["quantity"].i()),
            };

            billing_db.push_back(new_request);

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
                reqj["priority"].s(),
                reqj["expense_type"].s(),
                int(reqj["available"].i()),
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

    CROW_ROUTE(app, "/api/list/priority")
        .methods("POST"_method)([](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);


            for(auto &x:inventory_lists_db){
                if(x.inventory_id==reqj["inventory_id"].s()){
                    x.priority = reqj["priority"].s();
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

    CROW_ROUTE(app, "/api/list/assign_server")
    ([]() {
        std::string main_str;

        for(auto &x:inventory_lists_db){
            if(x.available == 0){
                x.available = 1;
                main_str = "Server Assigned " +x.inventory_id;
                break;
            } else {
                main_str = "No Server are currently Free";
            }
        }

        return main_str;
    });

    CROW_ROUTE(app, "/api/request/view")
    ([]() {
        std::string main_str = "[";

        crow::json::wvalue x;

        for(auto &x:requests_db){
            main_str+=x.convertString();
        }

        main_str+="]";

        return main_str;
    });

    CROW_ROUTE(app, "/api/bill/view")
    ([]() {
        std::string main_str = "[";

        crow::json::wvalue x;

        for(auto &x:billing_db){
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