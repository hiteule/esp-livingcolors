#include "livingcolors.h"
#include "esphome/core/log.h"

#include <cinttypes>
#include <Wire.h>

namespace esphome {
namespace livingcolors {

  static const char *const TAG = "LivingColorsComponent";
  static const char COMMAND_OFF = '0';
  static const char COMMAND_COLOR = '1';
  static const char COMMAND_EFFECT_COLOR_CYCLE = '2';

  LivingColorsComponent::LivingColorsComponent() {
  }

  void LivingColorsComponent::setup() {
    Wire.begin();
  }

  void LivingColorsComponent::setup_state(light::LightState *state) {
    state_ = state;
    state_->set_gamma_correct(0);
    state_->set_default_transition_length(0);
    state_->add_effects({new LivingColorsCycleLightEffect()});
  }

  void LivingColorsComponent::write_state(light::LightState *state) {
    float brightness;
    state->current_values_as_brightness(&brightness);

    uint8_t hue, saturation, value;
    char command;
    if (brightness > 0.0) {
      float red, green, blue;
      state->current_values_as_rgb(&red, &green, &blue, false);

      int _hue;
      float _saturation, _value;
      rgb_to_hsv(red, green, blue, _hue, _saturation, _value);

      hue = (uint8_t) lroundf(_hue * (255.0 / 360.0));
      saturation = (uint8_t) lroundf(_saturation * 255.0);
      value = (uint8_t) lroundf(_value * 255.0);
      command = COMMAND_COLOR;
    } else {
      hue = 0;
      saturation = 0;
      value = 0;
      command = COMMAND_OFF;
    }

    ESP_LOGV(TAG, "Setting light to 0x%02X 0x%02X 0x%02X", hue, saturation, value);

    char buf[14];
    sprintf(buf, "%c|%03d-%03d-%03d", command, hue, saturation, value);

    Wire.beginTransmission(0x21);
    Wire.write(buf);
    Wire.endTransmission();
  }

  void LivingColorsCycleLightEffect::apply() {
    if(!this->applied_) {
      ESP_LOGV(TAG, "LivingColorsCycleLightEffect::apply");

      char buf[14];
      sprintf(buf, "%c|xxx-xxx-xxx", COMMAND_EFFECT_COLOR_CYCLE);

      Wire.beginTransmission(0x21);
      Wire.write(buf);
      Wire.endTransmission();

      this->applied_ = true;
    }
  }

  void LivingColorsCycleLightEffect::stop() {
    ESP_LOGV(TAG, "LivingColorsCycleLightEffect::stop");

    char buf[14];
    sprintf(buf, "%c|xxx-xxx-xxx", COMMAND_OFF);

    Wire.beginTransmission(0x21);
    Wire.write(buf);
    Wire.endTransmission();

    this->applied_ = false;
  }

} // namespace livingcolors
} // namespace esphome
