use std::{collections::HashMap, sync::Arc};

use rocket::{serde::Serialize, tokio::sync::RwLock};

pub(crate) type Map = HashMap<String, String>;
pub(crate) type MapPtr = Arc<RwLock<Map>>;

#[derive(Serialize)]
#[serde(crate = "rocket::serde")]
pub(crate) struct ItemResponse {
    pub name: String,
    pub value: String,
}
