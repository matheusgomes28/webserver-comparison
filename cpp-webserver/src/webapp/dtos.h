#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

/* Begin DTO code-generation */
#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Message Data-Transfer-Object
 */
class MessageDto : public oatpp::DTO {
    DTO_INIT(MessageDto, DTO /* Extends */)

    DTO_FIELD(Int32, statusCode);   // Status code field
    DTO_FIELD(String, message);     // Message field

};

class ItemResponse : public oatpp::DTO {
    DTO_INIT(ItemResponse, DTO)

    DTO_FIELD(String, name);
    DTO_FIELD(String, value);
};

class ItemsResponse : public oatpp::DTO {
    DTO_INIT(ItemsResponse, DTO)

    DTO_FIELD(Fields<String>, items);
};

class ErrorResponse : public oatpp::DTO {
    DTO_INIT(ErrorResponse, DTO)

    DTO_FIELD(Int32, error_code);
    DTO_FIELD(String, error_msg);
};

/* End DTO code-generation */
#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */