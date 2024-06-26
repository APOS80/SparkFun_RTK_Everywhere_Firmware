######################################################################
# makefile
#
# Builds the EVK firmware
######################################################################

##########
# Source files
##########

# Uncomment all five lines for a complete update
#EXECUTABLES = arduino-config lib-update
EXECUTABLES += RTK

PARTITION_CSV_FILE=RTKEverywhere

# Windows NT
ifeq ($(OS),Windows_NT)
BLE_PATCH_DST_PATH=C:\Users\$(USERNAME)\Documents\Arduino\libraries\ESP32_BleSerial\src\BleSerial.cpp
BLE_PATCH_SRC_PATH=Patch\BleSerial.cpp
COPY=copy
PARTITION_DST_PATH=C:\Users\$(USERNAME)\AppData\Local\Arduino15\packages\esp32\hardware\esp32\$(ESP_CORE_VERSION)\tools\partitions\$(PARTITION_CSV_FILE).csv
PARTITION_SRC_PATH=..\$(PARTITION_CSV_FILE).csv

# Linux
else
BLE_PATCH_DST_PATH=~/Arduino/libraries/ESP32_BleSerial/src/BleSerial.cpp
BLE_PATCH_SRC_PATH=Patch/BleSerial.cpp
COPY=cp
PARTITION_DST_PATH=~/.arduino15/packages/esp32/hardware/esp32/$(ESP_CORE_VERSION)/tools/partitions/$(PARTITION_CSV_FILE).csv
PARTITION_SRC_PATH=../$(PARTITION_CSV_FILE).csv

endif

##########
# Buid tools and rules
##########

##########
# Buid all the sources - must be first
##########

.PHONY: all

all: $(EXECUTABLES)

##########
# Buid RTK firmware
##########

.PHONY: arduino-config

arduino-config:
	arduino-cli config init --overwrite --additional-urls "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json,https://espressif.github.io/arduino-esp32/package_esp32_dev_index.json"

.PHONY: lib-update

ESP_CORE_VERSION=3.0.1

lib-update:
	arduino-cli core update-index
	arduino-cli core install esp32:esp32@$(ESP_CORE_VERSION)
	arduino-cli lib install \
		ArduinoJson@6.19.4 \
		"ArduinoMqttClient"@0.1.8 \
		ESP32Time@2.0.0 \
		ESP32_BleSerial@1.0.4 \
		"ESP32-OTA-Pull"@1.0.0 \
		JC_Button@2.1.2 \
		PubSubClient@2.8.0 \
		"SdFat"@2.1.1 \
		"SparkFun BQ40Z50 Battery Manager Arduino Library"@1.0.0 \
		"SparkFun Extensible Message Parser"@1.0.1 \
		"SparkFun IM19 IMU Arduino Library"@1.0.1 \
		"SparkFun LIS2DH12 Arduino Library"@1.0.3 \
		"SparkFun MAX1704x Fuel Gauge Arduino Library"@1.0.4 \
		"SparkFun Qwiic OLED Arduino Library"@1.0.13 \
		"SparkFun u-blox GNSS v3"@3.1.5 \
		"SparkFun u-blox PointPerfect Library"@1.11.4 \
		"SparkFun UM980 Triband RTK GNSS Arduino Library"@1.0.4 \
		SSLClientESP32@2.0.0


$(PARTITION_DST_PATH):	$(PARTITION_SRC_PATH)
	$(COPY)  $(PARTITION_SRC_PATH)  $(PARTITION_DST_PATH)

$(BLE_PATCH_DST_PATH): 	$(BLE_PATCH_SRC_PATH)
	$(COPY)  $(BLE_PATCH_SRC_PATH)  $(BLE_PATCH_DST_PATH)

DEBUG_LEVEL=debug
ENABLE_DEVELOPER=false
FIRMWARE_VERSION_MAJOR=99
FIRMWARE_VERSION_MINOR=99
POINTPERFECT_TOKEN=

form.h:	AP-Config/* AP-Config/src/* AP-Config/src/fonts/*
	python ../Tools/index_html_zipper.py AP-Config/index.html form.h
	python ../Tools/main_js_zipper.py AP-Config/src/main.js form.h

RTK:	RTK_Everywhere.ino *.ino *.h $(PARTITION_DST_PATH) $(BLE_PATCH_DST_PATH)
	arduino-cli compile --fqbn "esp32:esp32:esp32":DebugLevel=$(DEBUG_LEVEL),PSRAM=enabled RTK_Everywhere.ino \
		--warnings default \
		--build-property build.partitions=$(PARTITION_CSV_FILE) \
		--build-property upload.maximum_size=6291456 \
		--build-property "compiler.cpp.extra_flags=-MMD -c \"-DPOINTPERFECT_TOKEN=$(POINTPERFECT_TOKEN)\" \"-DFIRMWARE_VERSION_MAJOR=$(FIRMWARE_VERSION_MAJOR)\" \"-DFIRMWARE_VERSION_MINOR=$(FIRMWARE_VERSION_MINOR)\" \"-DENABLE_DEVELOPER=$(ENABLE_DEVELOPER)\"" \
		--export-binaries

##########
# Upload the firmware
##########

.PHONY: upload

SKETCH=RTK_Everywhere.ino
ESPTOOL_PATH=~/Arduino/hardware/espressif/esp32/tools/esptool
TERMINAL_PORT="/dev/ttyUSB0"
BOOT_LOADER_PATH=~/SparkFun/SparkFun_RTK_Firmware_Uploader/RTK_Firmware_Uploader/resource

upload:	build/esp32.esp32.esp32/$(SKETCH).bin
	python3 $(ESPTOOL_PATH)/esptool.py \
        --chip   esp32 \
        --port   $(TERMINAL_PORT) \
        --baud   921600 \
        --before   default_reset \
        --after   hard_reset \
        write_flash \
        --flash_mode dio \
        --flash_freq 80m \
        --flash_size detect \
        --compress \
         0x1000   $(BOOT_LOADER_PATH)/RTK_Surveyor.ino.bootloader.bin \
         0x8000   $(BOOT_LOADER_PATH)/RTK_Surveyor_Partitions_16MB.bin \
         0xe000   $(BOOT_LOADER_PATH)/boot_app0.bin \
        0x10000   $<
	~/SparkFun/serial-115200.sh   ttyUSB0

########
# Clean the build directory
##########

