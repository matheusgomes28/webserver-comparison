use rocket::{delete, get, post, serde::json::Json, State};

use crate::{
    common::{ItemResponse, MapPtr},
    errors::{ErrorType, MyError},
};

#[get("/item/<name>")]
pub(crate) async fn get_item(
    name: String,
    map: &State<MapPtr>,
) -> Result<Json<ItemResponse>, MyError> {
    let map = map.read().await;

    let value = map.get(&name).cloned();

    value
        .map(|v| Json(ItemResponse { name, value: v }))
        .ok_or(MyError {
            error: ErrorType::ItemNotFound,
            msg: String::from("requested item was not found"),
        })
}

#[post("/item/<name>/<value>")]
pub(crate) async fn set_item(
    name: String,
    value: String,
    map: &State<MapPtr>,
) -> Result<Json<ItemResponse>, MyError> {
    // TODO : Set the value to the map
    let mut map = map.write().await;

    if let Some(_) = map.get(&name) {
        return Err(MyError {
            error: ErrorType::ItemAlreadyexists,
            msg: String::from("item already exists"),
        });
    }

    map.insert(name.clone(), value.clone());
    Ok(Json(ItemResponse {
        name: name,
        value: value,
    }))
}

#[delete("/item/<name>")]
pub(crate) async fn delete_item(
    name: String,
    map: &State<MapPtr>,
) -> Result<Json<ItemResponse>, MyError> {
    let mut map = map.write().await;

    map.remove(&name)
        .map(|v| Json(ItemResponse { name, value: v }))
        .ok_or(MyError {
            error: ErrorType::ItemNotFound,
            msg: String::from("cannot delete item"),
        })
}

#[get("/items")]
pub(crate) async fn show_items(map: &State<MapPtr>) -> String {
    let map = map.read().await;
    format!("{:#?}", map)
}
