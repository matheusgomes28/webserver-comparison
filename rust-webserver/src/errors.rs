use rocket::{
    http::{ContentType, Status},
    response::{self, Responder},
    serde::{json::Json, Serialize},
    Request, Response,
};

#[derive(Serialize)]
#[serde(crate = "rocket::serde")]
pub(crate) enum ErrorType {
    ItemNotFound,
    ItemAlreadyexists,
}

#[derive(Serialize)]
#[serde(crate = "rocket::serde")]
pub(crate) struct MyError {
    pub error: ErrorType,
    pub msg: String,
}

impl<'r> Responder<'r, 'static> for MyError {
    fn respond_to(self, req: &'r Request<'_>) -> response::Result<'static> {
        let status = match self.error {
            ErrorType::ItemNotFound => 404,
            ErrorType::ItemAlreadyexists => 409,
        };

        let json_response = Json(self);
        Response::build_from(json_response.respond_to(req)?)
            .header(ContentType::new("application", "json"))
            .status(Status::new(status))
            .ok()
    }
}
