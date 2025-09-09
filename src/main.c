/*
 * DFRobot FireBeetle 2 ESP32-C6 LED Blink Application
 * 
 * Diese Anwendung lässt die onboard LED an GPIO15 blinken.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(led_blink_app, LOG_LEVEL_INF);

/* LED Konfiguration */
#define LED0_NODE DT_ALIAS(led0)

#if !DT_NODE_HAS_STATUS_OKAY(LED0_NODE)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;
    bool led_state = true;

    LOG_INF("DFRobot FireBeetle 2 ESP32-C6 LED Blink App gestartet");

    /* Prüfen ob LED Device verfügbar ist */
    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED device %s ist nicht bereit", led.port->name);
        return -ENODEV;
    }

    /* LED Pin als Output konfigurieren */
    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        LOG_ERR("Fehler beim Konfigurieren der LED: %d", ret);
        return ret;
    }

    LOG_INF("LED Pin %d erfolgreich konfiguriert", led.pin);

    while (1) {
        /* LED umschalten */
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0) {
            LOG_ERR("Fehler beim Umschalten der LED: %d", ret);
        }

        led_state = !led_state;
        LOG_INF("LED ist jetzt: %s", led_state ? "AN" : "AUS");

        /* 1 Sekunde warten */
        k_msleep(1000);
    }

    return 0;
}
