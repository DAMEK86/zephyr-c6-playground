/*
 * DFRobot FireBeetle 2 ESP32-C6 Servo Motor Application
 * 
 * Diese Anwendung steuert einen WS-SG90 Servo Motor direkt über PWM auf GPIO15
 * und eine LED auf GPIO14. Gibt zusätzlich Akku-Informationen aus.
 */

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/logging/log.h>
#include <stdio.h>

LOG_MODULE_REGISTER(servo_app, LOG_LEVEL_INF);

/* LED Konfiguration */
#define LED0_NODE DT_ALIAS(led0)

#if !DT_NODE_HAS_STATUS_OKAY(LED0_NODE)
#error "Unsupported board: led0 devicetree alias is not defined"
#endif

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

/* PWM Device für Servo */
static const struct device *pwm_dev;

/* Servo Konfiguration */
#define SERVO_PWM_CHANNEL   0
#define SERVO_MIN_PULSE_NS  500000   /* 0.5ms = 0 Grad */
#define SERVO_MID_PULSE_NS  1500000  /* 1.5ms = 90 Grad */
#define SERVO_MAX_PULSE_NS  2500000  /* 2.5ms = 180 Grad */
#define SERVO_PERIOD_NS     20000000 /* 20ms Periode */

int main(void)
{
    int ret;
    bool led_state = true;
    int servo_position = 0; /* 0=min, 1=mid, 2=max */
    uint32_t servo_pulse_widths[] = {SERVO_MIN_PULSE_NS, SERVO_MID_PULSE_NS, SERVO_MAX_PULSE_NS};
    const char* servo_position_names[] = {"0°", "90°", "180°"};

    LOG_INF("DFRobot FireBeetle 2 ESP32-C6 Servo Motor App gestartet");

    /* LED Device prüfen */
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

    /* PWM Device für Servo holen */
    pwm_dev = DEVICE_DT_GET(DT_NODELABEL(ledc0));
    if (!device_is_ready(pwm_dev)) {
        LOG_ERR("PWM device %s ist nicht bereit", pwm_dev->name);
        return -ENODEV;
    }

    LOG_INF("LED Pin %d und PWM device erfolgreich konfiguriert", led.pin);
    LOG_INF("Servo Motor wird auf Pin 15 (PWM Kanal %d) gesteuert", SERVO_PWM_CHANNEL);

    /* Zähler für verschiedene Aktionen */
    int battery_counter = 0;
    int servo_counter = 0;

    while (1) {
        /* LED umschalten */
        ret = gpio_pin_toggle_dt(&led);
        if (ret < 0) {
            LOG_ERR("Fehler beim Umschalten der LED: %d", ret);
        }

        led_state = !led_state;
        LOG_INF("LED ist jetzt: %s", led_state ? "AN" : "AUS");

        /* Alle 3 Sekunden Servo Position ändern */
        if (++servo_counter >= 3) {
            servo_counter = 0;
            
            /* Servo Position setzen */
            ret = pwm_set(pwm_dev, SERVO_PWM_CHANNEL, SERVO_PERIOD_NS, servo_pulse_widths[servo_position], 0);
            if (ret < 0) {
                LOG_ERR("Fehler beim Setzen der Servo Position: %d", ret);
            } else {
                LOG_INF("Servo Position: %s (%d ns)", 
                       servo_position_names[servo_position], 
                       servo_pulse_widths[servo_position]);
            }
            
            /* Nächste Position für nächstes Mal */
            servo_position = (servo_position + 1) % 3;
        }

        /* Alle 5 Sekunden Akku-Daten ausgeben */
        if (++battery_counter >= 5) {
            battery_counter = 0;
            
            /* Simulierte Batterie-Daten */
            float battery_voltage = 3.7f + (float)(k_uptime_get() % 1000) / 10000.0f;
            int battery_percentage = (int)((battery_voltage - 3.0f) / 1.2f * 100);
            if (battery_percentage > 100) battery_percentage = 100;
            if (battery_percentage < 0) battery_percentage = 0;
            
            printf("=== STATUS ===\n");
            printf("Akku: %.2f V (%d%%)\n", battery_voltage, battery_percentage);
            printf("Servo: %s\n", servo_position_names[(servo_position + 2) % 3]); /* Aktuelle Position */
            printf("Uptime: %lld ms\n", k_uptime_get());
            printf("==============\n");
            
            LOG_INF("Akku: %.2fV (%d%%)", battery_voltage, battery_percentage);
        }

        /* 1 Sekunde warten */
        k_msleep(1000);
    }

    return 0;
}
