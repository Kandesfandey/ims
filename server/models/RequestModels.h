#include "string"

struct Request {
    std::string request_id;
    std::string name;
    std::string project_owner;
    std::string assigned_manager;

    std::string item_id;

    int quantity;
    int expense;
};