#include <iostream>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "jsoncpp/value.h"
#include "jsoncpp/json.h"
#include "esp_firebase/esp_firebase.h"
#include "wifi_utils.h"
#include "firebase_config.h"

#include "tarefas.h"


extern "C" void app_main(void)
{
    xTaskCreate(task_display, "task_display", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);
    xTaskCreate(task_dht, "task_dht", configMINIMAL_STACK_SIZE * 5, NULL, 5, NULL);

    wifiInit(SSID, PASSWORD); // blocking until it connects

    // Config and Authentication
    ESPFirebase::config_t config = {API_KEY, DATABASE_URL};
    ESPFirebase::user_account_t account = {USER_EMAIL, USER_PASSWORD};

    ESPFirebase::Firebase fb_client(config);

    fb_client.loginUserAccount(account);

    // R"()" allow us to write string as they are without escaping the characters with backslash

    // We can put a json str directly at /person1
    std::string json_str = R"({"name": "Madjid", "age": 20, "random_float": 8.56})";
    fb_client.putData("/person1", json_str.c_str());
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // We can parse the json_str and access the members and edit them
    Json::Value data;
    Json::Reader reader;
    reader.parse(json_str, data);

    std::string madjid_name = data["name"].asString(); // convert value to primitives (read jsoncpp docs for more of these)

    ESP_LOGI("MAIN", "name: %s", madjid_name.c_str());

    data["name"] = "teste 123";

    ESP_LOGI("MAIN", "edited name from %s to: %s", madjid_name.c_str(), data["name"].asString().c_str());

    data["age"] = 1234;
    data["random_float"] = 3.14;

    // put json object directly
    fb_client.putData("/person2", data);

    vTaskDelay(500 / portTICK_PERIOD_MS);
    // Construct a new json object manually
    Json::Value new_data;
    new_data["name"] = "dsgisg";
    new_data["age"] = 23;
    new_data["random_float"] = 5.95;

    fb_client.putData("person3", new_data);
    vTaskDelay(500 / portTICK_PERIOD_MS);

    // Edit person2 data in the database by patching
    data["age"] = 23;
    fb_client.patchData("person2", data);

    Json::Value root = fb_client.getData("person3"); // retrieve person3 from database, set it to "" to get entire database

    Json::FastWriter writer;
    std::string person3_string = writer.write(root); // convert it to json string

    ESP_LOGI("MAIN", "person3 as json string: \n%s", person3_string.c_str());

    // You can also print entire Json Value object with std::cout with converting to string
    // you cant print directly with printf or LOGx because Value objects can have many type. << is overloaded and can print regardless of the type of the Value
    std::cout << root << std::endl;

    // print the members (Value::Members is a vector)
    Json::Value::Members members = root.getMemberNames();
    for (auto member : members)
    {
        std::cout << member << ", ";
    }
    std::cout << std::endl;
}

