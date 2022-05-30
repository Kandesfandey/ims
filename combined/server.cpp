#include "string"
#include "vector"
#include "unordered_set"

#include "crow.h"
#include "crow/middlewares/cors.h"

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

struct Request {
    std::string request_id;
    std::string name;
    std::string project_owner;
    std::string assigned_manager;
    std::string status;
    std::string item_id;

    int quantity;
    int expense;

    std::string convertString() {
        std::string alpha = "{'request_id': '" + request_id + "', 'name': '" + name + "', 'project_owner': '" + project_owner + "', 'assigned_manager': '" + assigned_manager + "', 'status': '" + status + "', 'item_id': '" + item_id + ", 'quantity': " + std::to_string(int(quantity)) + ", 'expense': " + std::to_string(int(expense)) + "}|";
        ;

        return alpha;
    }
};

struct Owner {
    std::string owner_id;
};

struct Inventory_Lists {
    std::string name;
    std::string type;
    std::string inventory_id;
    std::string priority;
    std::string expense_type;

    int available;
    int quantity;
    int life;

    std::string convertString() {
        std::string alpha = "{ 'name': '" + name + "', 'inventory_id': '" + inventory_id + "', 'type':'" + type + "', 'priority': '" + priority + "', 'quantity': '" + std::to_string(int(quantity)) + "', 'available': '" + std::to_string(int(available)) + ", 'expense_type': '" + expense_type + "', 'life': '" + std::to_string(int(life)) + "'}|";

        return alpha;
    }
};

struct Billing {
    std::string bill_id;
    std::string item_id;
    std::string user_id;
    std::string manager_id;

    int price;
    int quantity;

    std::string convertString() {
        std::string alpha = "{'bill_id': '" + bill_id + "', 'item_id': '" + item_id + "', 'user_id': '" + user_id + "', 'manager_id': '" + manager_id + "', 'price': '" + std::to_string(int(price)) + "', 'quantity': '" + std::to_string(int(quantity)) + "' }|";

        return alpha;
    }
};

void LiveHandlerModule(crow::App<crow::CORSHandler> *server, mongocxx::database *db_loc, std::unordered_set<crow::websocket::connection *> *request_list_users, std::unordered_set<crow::websocket::connection *> *inventory_list_users) {
    crow::App<crow::CORSHandler> &app = *server;
    mongocxx::database &db = *db_loc;

    std::mutex mtx;
    std::unordered_set<crow::websocket::connection *> &iusers = *inventory_list_users;
    std::unordered_set<crow::websocket::connection *> &rusers = *request_list_users;

    CROW_ROUTE(app, "/api/list/view/live")
        .websocket()
        .onopen([&](crow::websocket::connection &conn) {
            CROW_LOG_INFO << "new websocket connection from " << conn.get_remote_ip();
            std::lock_guard<std::mutex> _(mtx);
            iusers.insert(&conn);
        })
        .onclose([&](crow::websocket::connection &conn, const std::string &reason) {
            CROW_LOG_INFO << "websocket connection closed: " << reason;
            std::lock_guard<std::mutex> _(mtx);
            iusers.erase(&conn);
        })
        .onmessage([&](crow::websocket::connection &conn, const std::string &data, bool is_binary) {
            std::lock_guard<std::mutex> _(mtx);
            for (auto u : iusers)
                if (is_binary)
                    u->send_binary(data);
                else
                    u->send_text(data);
        });
}

void BillingManagementModule(crow::App<crow::CORSHandler> *server, mongocxx::database *db_loc) {
    crow::App<crow::CORSHandler> &app = *server;
    mongocxx::database &db = *db_loc;

    CROW_ROUTE(app, "/api/bill/add")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["billing"];

            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::document::value doc_value = builder
                                                 << "bill_id"
                                                 << reqj["bill_id"].s()
                                                 << "item_id"
                                                 << reqj["item_id"].s()
                                                 << "user_id"
                                                 << reqj["user_id"].s()
                                                 << "manager_id"
                                                 << reqj["manager_id"].s()
                                                 << "price"
                                                 << int(reqj["price"].i())
                                                 << "quantity"
                                                 << int(reqj["quantity"].i())
                                                 << bsoncxx::builder::stream::finalize;
            bsoncxx::document::view docview = doc_value.view();

            bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one(docview);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/bill/view")
    ([db]() {
        mongocxx::collection collection = db["billing"];

        mongocxx::cursor cursor = collection.find({});

        std::string main_str = "[";

        crow::json::wvalue x;

        for (auto doc : cursor) {
            main_str += (bsoncxx::to_json(doc)) + ",";
        }
        main_str.pop_back();

        main_str += "]";

        return main_str;
    });
}

void InventoryManagementModule(crow::App<crow::CORSHandler> *server, mongocxx::database *db_loc, std::unordered_set<crow::websocket::connection *> *inventory_list_users) {
    crow::App<crow::CORSHandler> &app = *server;
    mongocxx::database &db = *db_loc;
    std::unordered_set<crow::websocket::connection *> &users = *inventory_list_users;

    CROW_ROUTE(app, "/api/list/add")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["inventory"];

            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::document::value doc_value = builder
                                                 << "name"
                                                 << reqj["name"].s()
                                                 << "type"
                                                 << reqj["type"].s()
                                                 << "inventory_id"
                                                 << reqj["inventory_id"].s()
                                                 << "priority"
                                                 << reqj["priority"].s()
                                                 << "expense_type"
                                                 << reqj["expense_type"].s()
                                                 << "available"
                                                 << int(reqj["available"].i())
                                                 << "life"
                                                 << int(reqj["life"].i())
                                                 << "quantity"
                                                 << int(reqj["quantity"].i())
                                                 << bsoncxx::builder::stream::finalize;
            bsoncxx::document::view docview = doc_value.view();

            bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one(docview);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/list/edit")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["inventory"];

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/list/priority")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["inventory"];

            bsoncxx::builder::stream::document query{};

            collection.update_one(query << "inventory_id" << reqj["inventory_id"].s() << bsoncxx::builder::stream::finalize,
                                  query << "$set" << open_document << "priority" << reqj["priority"].s() << close_document << bsoncxx::builder::stream::finalize);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/list/delete")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["inventory"];

            auto builder = bsoncxx::builder::stream::document{};

            collection.delete_one(builder << "id" << reqj["id"].s() << bsoncxx::builder::stream::finalize);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/list/view")
    ([db]() {
        mongocxx::collection collection = db["inventory"];

        mongocxx::cursor cursor = collection.find({});

        std::string main_str = "[";

        crow::json::wvalue x;

        for (auto doc : cursor) {
            main_str += (bsoncxx::to_json(doc)) + ",";
        }
        main_str.pop_back();

        main_str += "]";

        return main_str;
    });

    CROW_ROUTE(app, "/api/list/assign_server")
    ([db]() {
        std::string main_str;

        mongocxx::collection collection = db["inventory"];

        mongocxx::cursor cursor = collection.find({});

        return main_str;
    });
}

void RequestManagementModule(crow::App<crow::CORSHandler> *server, mongocxx::database *db_loc, std::unordered_set<crow::websocket::connection *> *request_list_users) {
    crow::App<crow::CORSHandler> &app = *server;
    mongocxx::database &db = *db_loc;
    std::unordered_set<crow::websocket::connection *> &users = *request_list_users;

    CROW_ROUTE(app, "/api/request/add")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);
            mongocxx::collection collection = db["request"];

            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::document::value doc_value = builder
                                                 << "request_id"
                                                 << reqj["request_id"].s()
                                                 << "name"
                                                 << reqj["name"].s()
                                                 << "project_owner"
                                                 << reqj["project_owner"].s()
                                                 << "assigned_manager"
                                                 << reqj["assigned_manager"].s()
                                                 << "status"
                                                 << "Pending"
                                                 << "item_id"
                                                 << reqj["item_id"].s()
                                                 << "quantity"
                                                 << int(reqj["quantity"].i())
                                                 << "expense"
                                                 << int(reqj["expense"].i())
                                                 << bsoncxx::builder::stream::finalize;
            bsoncxx::document::view docview = doc_value.view();

            bsoncxx::stdx::optional<mongocxx::result::insert_one> result = collection.insert_one(docview);

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/request/accept")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["request"];

            bsoncxx::builder::stream::document query{};

            collection.update_one(query << "request_id" << reqj["request_id"].s() << bsoncxx::builder::stream::finalize,
                                  query << "$set" << open_document << "status"
                                        << "Pass" << close_document << bsoncxx::builder::stream::finalize);

            // for (auto &x : requests_db) {
            //     if (x.item_id == reqj["request_id"].s()) {
            //         x.status = "Pass";
            //     }
            // }

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/request/reject")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["request"];

            bsoncxx::builder::stream::document query{};

            collection.update_one(query << "request_id" << reqj["request_id"].s() << bsoncxx::builder::stream::finalize,
                                  query << "$set" << open_document << "status"
                                        << "Fail" << close_document << bsoncxx::builder::stream::finalize);

            // for (auto &x : requests_db) {
            //     if (x.item_id == reqj["request_id"].s()) {
            //         x.status = "Failed";
            //     }
            // }

            return crow::response(crow::status::OK);
        });

    CROW_ROUTE(app, "/api/request/view")
        .methods("GET"_method)([db]() {
            mongocxx::collection collection = db["request"];

            mongocxx::cursor cursor = collection.find({});

            std::string main_str = "[";

            crow::json::wvalue x;

            for (auto doc : cursor) {
                main_str += (bsoncxx::to_json(doc)) + ",";
            }
            main_str.pop_back();

            main_str += "]";

            return main_str;
        });

    CROW_ROUTE(app, "/api/request/delete")
        .methods("POST"_method)([db](const crow::request &req) {
            auto reqj = crow::json::load(req.body);
            if (!reqj)
                return crow::response(crow::status::BAD_REQUEST);

            mongocxx::collection collection = db["request"];

            auto builder = bsoncxx::builder::stream::document{};

            bsoncxx::stdx::optional<mongocxx::result::delete_result> result = collection.delete_one(builder << "request_id" << reqj["id"].s() << bsoncxx::builder::stream::finalize);

            if (result) {
                std::cout << result->deleted_count() << "\n";
            }

            return crow::response(crow::status::OK);
        });
}

int main() {
    crow::App<crow::CORSHandler> app;

    // Customize CORS
    auto &cors = app.get_middleware<crow::CORSHandler>();

    // clang-format off
    cors
      .global()
        .headers("X-Custom-Header", "Upgrade-Insecure-Requests")
        .methods("POST"_method, "GET"_method)
      .prefix("/")
        .origin("*");
    // clang-format on

    // Database
    mongocxx::instance inst{};
    const auto uri = mongocxx::uri{"mongodb+srv://ims-backend:imsbackend@cluster0.i1jrs.mongodb.net/?retryWrites=true&w=majority"};
    mongocxx::client conn{uri};
    mongocxx::database db = conn["IMS"];

    // WS
    std::unordered_set<crow::websocket::connection *> inventory_list_users;
    std::unordered_set<crow::websocket::connection *> request_list_users;

    CROW_ROUTE(app, "/")
    ([db]() {
        return "<h1>IMS Status OK</h1>";
    });

    LiveHandlerModule(&app, &db, &request_list_users, &inventory_list_users);
    BillingManagementModule(&app, &db);
    RequestManagementModule(&app, &db, &request_list_users);
    InventoryManagementModule(&app, &db, &inventory_list_users);

    app.port(5000)
        .multithreaded()
        .run();
}

// To run:
/*
c++ --std=c++11 combined/server.cpp -I/usr/local/include/mongocxx/v_noabi -I/usr/local/include/libmongoc-1.0 -I/usr/local/include/bsoncxx/v_noabi -I/usr/local/include/libbson-1.0 -L/usr/local/lib -lmongocxx -lbsoncxx -lpthread -lboost_system -o app.out
*/