#include "banco_de_dados.h"

void BancoDeDados::read_mac_address(void)
{
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