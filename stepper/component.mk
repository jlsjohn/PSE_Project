# Component makefile for extras/stepper
DIRECTORY = /home/john/FreeRtos/esp-open-sdk/esp-open-rtos/

INC_DIRS += $(DIRECTORY)extras/stepper

# args for passing into compile rule generation
extras/stepper_INC_DIR =  $(DIRECTORY)extras/stepper
extras/stepper_SRC_DIR =  $(DIRECTORY)extras/stepper

$(eval $(call component_compile_rules,extras/stepper))
