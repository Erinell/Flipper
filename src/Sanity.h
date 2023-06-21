#include "Arduino.h"
#include "Settings.h"
#include "Pins.h"
#include "macro.h"

constexpr uint8_t _points_pin[] = SCORE;
constexpr uint16_t _points_value[] = SCORE_VALUE;
constexpr uint8_t _bonus_pin[] = BONUS;
constexpr uint16_t _bonus_value[] = BONUS_VALUE;
constexpr uint16_t _bonus_led[] = LEDS_BONUS;
constexpr uint8_t _solenoids_pin[] = SOLENOIDS;
constexpr uint16_t _trigger_solenoids_pin[] = TRIGGER_SOLENOID;

static_assert(COUNT(_points_pin)<=COUNT(_points_value), "SCORE_VALUE doit être supérieur ou égal aux broches SCORE définies");
static_assert(COUNT(_bonus_pin)<=COUNT(_bonus_value), "BONUS_VALUE doit être supérieur ou égal aux broches BONUS définies");
static_assert(COUNT(_bonus_led)<=COUNT(_bonus_value), "BONUS_VALUE doit être supérieur ou égal aux broches LEDS_BONUS définies");
static_assert(EQUAL(COUNT(_solenoids_pin),COUNT(_trigger_solenoids_pin)), "Les broches SOLENOIDS voient être égal aucx broches TRIGGER_SOLENOID");