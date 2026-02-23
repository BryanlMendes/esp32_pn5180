#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "pn5180.h"
#include "pn5180-15693.h"

#define PIN_SCK   18
#define PIN_MISO  19
#define PIN_MOSI  23
#define PIN_NSS   5
#define PIN_BUSY  21
#define PIN_RST   22

void app_main(void)
{
    pn5180_spi_t *spi = pn5180_spi_init(
        SPI2_HOST,
        PIN_SCK,
        PIN_MISO,
        PIN_MOSI,
        1000000
    );

    pn5180_t *pn = pn5180_init(spi, PIN_NSS, PIN_BUSY, PIN_RST);

    pn5180_proto_t *iso = pn5180_15693_init(
        pn,
        PN5180_15693_26KASK100
    );

    iso->setup_rf(iso);

    while (1)
    {
        nfc_uids_array_t *uids = iso->get_all_uids(iso);

        if (uids)
        {
            for (int i = 0; i < uids->uids_count; i++)
            {
                printf("TAG %d: ", i);

                for (int j = 0; j < uids->uids[i].uid_length; j++)
                {
                    printf("%02X ", uids->uids[i].uid[j]);
                }

                printf("\n");
            }

            free(uids);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}