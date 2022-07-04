#include "banco_de_dados.h"

void BancoDeDados::read_mac_address(void)
{
    // o endereço mac identificará as esp32 no firebase
    uint8_t base_mac_addr[6] = {0};
    esp_err_t ret = ESP_OK;

    ret = esp_efuse_mac_get_default(base_mac_addr);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to get base MAC address from EFUSE BLK0. (%s)", esp_err_to_name(ret));
        ESP_LOGE(TAG, "Aborting");
        abort();
    }
    else
    {
        ESP_LOGI(TAG, "Base MAC Address read from EFUSE BLK0");
    }

    // Set the base MAC address using the retrieved MAC address
    ESP_LOGI(TAG, "Using \"0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x\" as base MAC address",
             base_mac_addr[0], base_mac_addr[1], base_mac_addr[2], base_mac_addr[3], base_mac_addr[4], base_mac_addr[5]);
    esp_base_mac_addr_set(base_mac_addr);

    int i;

    for (i = 0; i < 6; i++)
    {
        mac = mac + std::to_string(base_mac_addr[i]);
    }

    std::cout << mac;
}

std::string BancoDeDados::get_mac_address(void)
{
    read_mac_address();
    return mac;
}

void BancoDeDados::banco_de_dados_init(void)
{
    std::string mac_addr = get_mac_address();

    // Config and Authentication
    ESPFirebase::config_t config = {API_KEY, DATABASE_URL};
    ESPFirebase::user_account_t account = {USER_EMAIL, USER_PASSWORD};

    ESPFirebase::Firebase fb_client(config);

    fb_client.loginUserAccount(account);

    // R"()" allow us to write string as they are without escaping the characters with backslash

    // We can put a json str directly at /person1
    std::string json_str = R"({"especie": "cacto", "nome_planta": "Zé", "umidade_ideal_solo": 50, "temperatura_ideal": 25, "luminosidade_ideal": 30000, "umidade_regar": 0, "umidade_solo_lida": 10, "temperatura_lida" : 26.5, "luminosidade_lida": 20000, "status": "com sede"})";

    std::string path = "/";
    path.append(mac_addr);

    fb_client.putData(path.c_str(), json_str.c_str());

    // We can parse the json_str and access the members and edit them
    Json::Value data;
    Json::Reader reader;
    reader.parse(json_str, data);

    //  std::string madjid_name = data["name"].asString(); // convert value to primitives (read jsoncpp docs for more of these)
}