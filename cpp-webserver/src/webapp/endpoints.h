#ifndef ENDPOINTS_H
#define ENDPOINTS_H

#include "thread_safe_map.h"
#include "dtos.h"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/core/data/mapping/type/Map.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) ///< Begin Codegen

using KvMap = ThreadSafeMap<std::string, std::string>;

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
private:
    // TODO : Mutex this map
    std::shared_ptr<KvMap> items;

public:
    /**
     * Constructor with object mapper.
     * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
     */
    MyController(std::shared_ptr<KvMap> items, OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper), items{items}
    {}

  
    ENDPOINT("POST", "item/{name}/{value}", set_item,
            PATH(String, name, "name"),
            PATH(String, value, "value"))
    {
        auto const item_name = name.getValue("undefined");
        auto const item_value = value.getValue("undefined");


        if (!items->add_item(item_name, item_value)) {
            auto error_response = ErrorResponse::createShared();
            error_response->error_code = 500;
            error_response->error_msg = "could not add item to the map";
            return createDtoResponse(Status::CODE_500, error_response);
        }
        
        // Return the ItemResponse as json
        auto response = ItemResponse::createShared();
        response->name = item_name;
        response->value = item_value;
        return createDtoResponse(Status::CODE_200, response);
    }

    ENDPOINT("GET", "item/{name}", show_item,
            PATH(String, name, "name"))
    {
        auto const item_name = name.getValue("undefined");

        auto maybe_value = items->get_item(item_name);
        if (!maybe_value) {
            // return an error here (item not found)
            auto error_response = ErrorResponse::createShared();
            error_response->error_code = 404;
            error_response->error_msg = "could not find request item";
            return createDtoResponse(Status::CODE_404, error_response);
        }

        auto item_response = ItemResponse::createShared();
        item_response->name = item_name;
        item_response->value = *maybe_value;
        return createDtoResponse(Status::CODE_200, item_response);
    }

    ENDPOINT("DELETE", "item/{name}", delete_item,
            PATH(String, name, "name"))
    {
        auto const item_name = name.getValue("undefined");

        auto const maybe_value = items->remove_item(item_name);
        if (!maybe_value)
        {
            // return an error here (item not found)
            auto error_response = ErrorResponse::createShared();
            error_response->error_code = 404;
            error_response->error_msg = "could not delete item";
            return createDtoResponse(Status::CODE_404, error_response);
        }

        auto item_response = ItemResponse::createShared();
        item_response->name = item_name;
        item_response->value = *maybe_value;
        return createDtoResponse(Status::CODE_200, item_response);
    }

    ENDPOINT("GET", "items", show_items)
    {
        auto const all_items = items->get_items();

        auto items = ItemsResponse::createShared();
        items->items = Fields<String>::createShared();

        for (auto& [key, value] : all_items) {
            items->items->push_back({key, value});
        }
        
        return createDtoResponse(Status::CODE_200, items);
    }
  
  // TODO Insert Your endpoints here !!!
  
};

#include OATPP_CODEGEN_END(ApiController) ///< End Codegen

#endif // ENDPOINTS_H