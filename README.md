# Vector

Utility library that includes 2D, 3D and 4D vectors as well as 3D and 4D matrices. This library has been created with 3D graphics in mind, therefore, standard transformation, rotation and projection matrices can be easily created.

## ESP32-S3 optimization
The library is currently being used in projects with the ESP32-S3 microcontroller and has been optimized to take advantage of some special instructions included in its processor.
This allows for a performance increase of up to **four** times compared to standard C++ code. If compared against Espressif's dedicated library ([esp-dsp](https://github.com/espressif/esp-dsp)) it can be up to twice as fast.
