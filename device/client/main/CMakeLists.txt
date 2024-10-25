set(srcs 
    "main.c"
    "camera/camera.c"
    "communications/network.c"
    "communications/wifi.c"
    "communications/requests/alarm.c"
    "communications/requests/connect.c"
    "communications/requests/rfid.c"
    "communications/requests/utils.c"
    "communications/server/server.c"
    "communications/server/handlers/index.c"
    "communications/server/handlers/picture.c"
    "communications/server/handlers/enabled.c"
    "communications/server/handlers/network_configuration.c"
    "communications/uart.c"
    "storage/spiffs.c"
    "storage/nvs_helpers.c"
    "storage/wifi_password.c"
    "storage/wifi_ssid.c"
    "storage/id.c"
    "storage/enabled.c"
    "storage/server_address.c"
)

idf_component_register(
    SRCS "${srcs}"
    INCLUDE_DIRS "."
)

spiffs_create_partition_image(spiffs spiffs FLASH_IN_PROJECT)