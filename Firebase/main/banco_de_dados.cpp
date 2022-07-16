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

ESPFirebase::config_t config = {API_KEY, DATABASE_URL};
ESPFirebase::user_account_t account = {USER_EMAIL, USER_PASSWORD};

ESPFirebase::Firebase fb_client(config);
Json::Value data;

void BancoDeDados::banco_de_dados_init(void)
{
    std::string mac_addr = get_mac_address();

    // Config and Authentication
    // ESPFirebase::config_t config = {API_KEY, DATABASE_URL};
    // ESPFirebase::user_account_t account = {USER_EMAIL, USER_PASSWORD};

    // ESPFirebase::Firebase fb_client(config);

    fb_client.loginUserAccount(account);

    // R"()" allow us to write string as they are without escaping the characters with backslash

    std::string json_str = R"({"dispositivo":"", "nome_vaso": "", "luminosidade_lida": "", "umidade_lida_solo": "", "umidade_lida_ar": "", "temperatura_lida": "", "status_planta": "", "status_bateria": ""})";

    std::string json_ids = mac_addr;

    std::string path_ids_dispositivos = "/dispositivos/ids/";
    std::string path_vaso = "/dispositivos/vasos/vaso1_parametros_lidos";
    // path_vaso.append(mac_addr);
    // path_vaso.append("vaso1");
    path_ids_dispositivos.append(mac_addr);

    std::string teste = "123456789";

    fb_client.putData(path_vaso.c_str(), json_str.c_str());
    fb_client.putData(path_ids_dispositivos.c_str(), json_ids.c_str());
    fb_client.putData("/dispositivos/ids/teste", teste.c_str());

    // We can parse the json_str and access the members and edit them
    // Json::Value data;
    Json::Reader reader;
    reader.parse(json_str, data);

    std::string device = data["dispositivo"].asString(); // convert value to primitives (read jsoncpp docs for more of these

    data["dispositivo"] = mac_addr.c_str();
    fb_client.putData(path_vaso.c_str(), data);

    // Json::Value teste_leitura = fb_client.getData("/tags_plantas/1");

    //  printf("teste leitura: %s ",teste_leitura.asCString());

    // data["ids"] = device + "," + mac_addr.c_str();
    // fb_client.putData(path_ids_dispositivos.c_str(), data);

    // //------------teste para simular dois dispositivos para o app------
    // std::string json_test_str = R"({"dispositivo": "teste1234" ,"especie": "rosa", "nome_planta": "Zé", "umidade_ideal_solo": 50, "temperatura_ideal": 25, "luminosidade_ideal": 30000, "umidade_regar": 0, "umidade_solo_lida": 10, "temperatura_lida" : 26.5, "luminosidade_lida": 20000, "status": "com sede"})";

    // fb_client.putData("/teste", json_test_str.c_str());

    //-----------------------------------------------------------------
}

int BancoDeDados::publish_temperature_info(float temp, float humi)
{

    std::string path_temp = "/dispositivos/vasos/vaso1_parametros_lidos/temperatura_lida";
    std::string path_umid = "/dispositivos/vasos/vaso1_parametros_lidos/umidade_lida_ar";
    temperatura = std::to_string(temp);
    umidade = std::to_string(humi);

    if (fb_client.putData(path_temp.c_str(), temperatura.c_str()) == ESP_FAIL)
    {
        fb_client.loginUserAccount(account);
    }
    else
    {
        printf("Temperatura registrada!");
    }
    if (fb_client.putData(path_umid.c_str(), umidade.c_str()) == ESP_FAIL)
    {
        fb_client.loginUserAccount(account);
    }
    else
    {
        printf("Umidade registrada!");
    }

    return 0;
}

int BancoDeDados::publish_battery_info(uint16_t mV, uint8_t percentage)
{
    std::string path_vaso = "/dispositivos/vasos/vaso1_parametros_lidos";
    static uint8_t old_percentage = 0;

    if (old_percentage != percentage)
    {
#define LEN 4    // length of the string w/ null terminator
#define BASE 10  // string as a decimal base
#define FILL '0' // character to fill non-used algarisms.

        uint8_t i = LEN - 1;    // index for each char of the string
        char str[LEN] = {FILL}; // ascii zero filled array
        str[i] = '\0';          // adds string null terminator
        while (i--)
        {
            str[i] = FILL + (percentage % BASE); // gets each algarism}
            percentage /= BASE;                  // prepare the next
        }
        printf("publicado");
        old_percentage = percentage;

        data["status_bateria"] = str;
        fb_client.putData(path_vaso.c_str(), data);

#undef LEN
#undef BASE
#undef FILL
    }
    return 0;
}