#include "esphome.h"
#include <Wire.h>

class LightI2COutput : public Component, public LightOutput {
 public:
  void setup() override {
    Wire.begin();
  }

  // return the traits this light supports
  LightTraits get_traits() override {
    auto traits = LightTraits();
    traits.set_supported_color_modes({ColorMode::RGB, ColorMode::BRIGHTNESS});

    return traits;
  }

  // This will be called by the light to get a new state to be written.
  void write_state(LightState *state) override {
    float red, green, blue;
    state->current_values_as_rgb(&red, &green, &blue);

    int red_i = red*255;
    int green_i = green*255;
    int blue_i = blue*255;
    
    char buf[70];
    sprintf(buf, "%03d-%03d-%03d", red_i, green_i, blue_i);

    Wire.beginTransmission(0x21);
    Wire.write(buf);
    Wire.endTransmission();
  }
};
