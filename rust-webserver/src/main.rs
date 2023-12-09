mod common;
mod endpoints;
mod errors;

use common::Map;
use endpoints::{delete_item, get_item, set_item, show_items};

use rocket::{get, launch, routes, tokio::sync::RwLock};
use std::sync::Arc;

#[get("/")]
fn index() -> &'static str {
    "Hello, world!"
}

#[launch]
fn rocket() -> _ {
    let global_map = RwLock::from(Map::new());
    let global_map = Arc::new(global_map);

    rocket::build()
        .mount(
            "/",
            routes![index, delete_item, get_item, set_item, show_items],
        )
        .manage(global_map)
}
