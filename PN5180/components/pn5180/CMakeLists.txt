idf_component_register(
    SRCS
        "src/pn5180.c"
        "src/pn5180-15693.c"
    INCLUDE_DIRS
        "include"
    REQUIRES
        driver freertos esp_timer
)