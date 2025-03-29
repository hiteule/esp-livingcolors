import esphome.config_validation as cv
import esphome.codegen as cg
from esphome.components import light
from esphome.const import (
    CONF_ID,
    CONF_LIGHT_ID,
)

CODEOWNERS = ["@hiteule"]
DEPENDENCIES = [ ]
AUTO_LOAD = [ ]
MULTI_CONF = False

ns = cg.esphome_ns.namespace("livingcolors")
LivingColorsComponent = ns.class_("LivingColorsComponent", light.LightOutput, cg.Component)

CONFIG_SCHEMA = cv.COMPONENT_SCHEMA.extend(
  {
    cv.GenerateID(): cv.declare_id(LivingColorsComponent),
  }
)

CONFIG_SCHEMA = cv.All(
  light.LIGHT_SCHEMA.extend(
    {
      cv.GenerateID(CONF_LIGHT_ID): cv.declare_id(LivingColorsComponent),
    }
  )
  .extend(cv.COMPONENT_SCHEMA)
)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_LIGHT_ID])
    await cg.register_component(var, config)
    await light.register_light(var, config)
