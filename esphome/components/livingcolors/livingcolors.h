#pragma once

#include "esphome/core/color.h"
#include "esphome/core/component.h"
#include "esphome/core/helpers.h"
#include "esphome/components/light/light_output.h"
#include "esphome/components/light/base_light_effects.h"
#include "esphome/components/light/esp_hsv_color.h"

namespace esphome {
namespace livingcolors {

class LivingColorsComponent: public light::LightOutput, public Component {
  public:
    LivingColorsComponent();

    void setup() override;

    void setup_state(light::LightState *state) override;
    void write_state(light::LightState *state) override;
    light::LightTraits get_traits() override {
      auto traits = light::LightTraits();
      traits.set_supported_color_modes( { light::ColorMode::RGB });
      return traits;
    }

  protected:
    light::LightState *state_ { nullptr };
};

class LivingColorsCycleLightEffect : public light::LightEffect {
  public:
    LivingColorsCycleLightEffect() : light::LightEffect("Color cycle") {}

    void stop() override;
    void apply() override;
    void init() {}

  protected:
    bool applied_ = false;
};

} // namespace livingcolors
} // namespace esphome
