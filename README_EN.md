This is an automatic translation and may be incorrect in some places. See the source README and examples for authoritative information.

[![latest](https://img.shields.io/github/v/release/GyverLibs/GyverFilters.svg?color=brightgreen)](https://github.com/GyverLibs/GyverFilters/releases/latest/download/GyverFilters.zip)
[![PIO](https://badges.registry.platformio.org/packages/gyverlibs/library/GyverFilters.svg)](https://registry.platformio.org/libraries/gyverlibs/GyverFilters)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD%24%E2%82%AC%20%D0%9F%D0%BE%D0%B4%D0%B4%D0%B5%D1%80%D0%B6%D0%B0%D1%82%D1%8C-%D0%B0%D0%B2%D1%82%D0%BE%D1%80%D0%B0-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverFilters?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverFilters
GyverFilters - a library with some convenient filters for Arduino
- GFilterRA - a compact alternative to the exponential running average filter (Running Average)
- GMedian3 - fast median filter 3rd order (cuts emissions)
- GMedian is an N-order median filter. Order set up in GyverFilters.h - MEDIAN FILTER SIZE
- GABfilter - alpha-beta filter (Kalman variety for one-dimensional case)
- GKalman is a simplified Kalman for one-dimensional case (in my opinion, the best filter)
- GLinear - linear least square approximation for two arrays
- FastFilter - Fast Integer Exponential Filter
- RingAverage is a running average with a ring buffer (does not work for float!)

Based on[digital filter lesson](https://alexgyver.ru/lessons/filters/)

### Compatibility
Compatible with all Arduino platforms (Arduino features are used)

### Documentation.
There's a library[extended documentation](https://alexgyver.ru/GyverFilters/)

## Contents
- [Installation](#install)
- [Use of use](#usage)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **GyverFilters** and installed through the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download the library](https://github.com/GyverLibs/GyverFilters/archive/refs/heads/main.zip).zip archive for manual installation:
    - Unpack and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unpack and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/ *
    - (Arduino IDE) Automatic installation from .zip: *Sketch/Connect library/Add .ZIP library...* and specify downloaded archive
- Read more detailed instructions for installing libraries[here](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: new versions fix errors and bugs, as well as optimize and add new features.
- Through the library manager IDE: find the library as when installing and click "Update"
- Manually: **Delete the folder with the old version** and then put the new one in its place. “Replacement” can not be done: sometimes new versions delete files that will remain when replaced and can lead to errors!

<a id="usage"></a>
## Use of use
```cpp
// =========== ALPHA-BETTA alfaBeta.h ===========
// Period of sampling (measurement), process variation, noise variation
GABfilter(float delta, float sigma_process, float sigma_noise);

// Period of sampling (measurement), process variation, noise variation
void setParameters(float delta, float sigma_process, float sigma_noise);

// returns the filter value
float filtered(float value);
    
// ========== FAST FILTER FastFilter.h ==========
FastFilter; 
FastFilter(uint8_t k = 20);                     // factor 0-31, dt 0
FastFilter(uint8_t k = 20, uint16_t dt = 0);    // factor 0-31, dt in milliseconds

void setK(uint8_t k);       // 0-31
void setDt(uint16_t dt);    // fix the filtration period in ms
void setPass(uint8_t pass); // set the pass mode (FF PASS MAX / FF PASS MIN)
void setRaw(long raw);      // set the reference value for filtering
void setFil(long fil);      // filter
bool checkPass(long val);   // overflow
void compute();             // timer
void computeNow();          // calculate now
int getFil();               // filter
int getRaw();               // finalize

// =========== SIMPLE KALMAN kalman.h ===========
// measurement spread, estimation spread, rate of change of values
GKalman(float mea_e, float est_e, float q);
// scatter of measurement, rate of change of values (dispersion of measurement is taken equal to spread of estimate)
GKalman(float mea_e, float q);

// measurement spread, estimation spread, rate of change of values
void setParameters(float mea_e, float est_e, float q);

// scatter of measurement, rate of change of values (dispersion of measurement is taken equal to spread of estimate)
void setParameters(float mea_e, float q);

// returns the filter value
float filtered(float value);

// ======== LINEAR APPROXIMATION linear.h =======
GLinear<тип_данных> filter;

void compute(*x_array, *y_array, arrSize);    // approximate
float getA();       // get a coefficient
float getB();       // get
float getDelta();   // approximate

// ============= MEDIAN N median.h ==============
GMedian<порядок, тип_данных> median;

тип_данных filtered(тип_данных value);      // result

// ============= MEDIAN 3 median3.h ==============
GMedian3<тип_данных> median;

тип_данных filtered(тип_данных value);      // result

// ========= RING AVERAGE RingAverage.h =========
RingAverage<тип_данных, порядок> filter;
// It doesn't work for float!

тип_данных filtered(тип_данных val);        // result
float filteredFloat(тип_данных val);        // float

// ====== RUNNING AVERAGE runningAverage.h ======
GFilterRA filter;
GFilterRA(float coef);                      // factor
GFilterRA(float coef, uint16_t interval);   // period

void setCoef(float coef);                   // factor
void setPeriod(uint16_t interval);          // period
float filteredTime(float value);            // timer
float filtered(float value);                // get results now
```

<a id="versions"></a>
## Versions
- v1.6 of 12.11. 2019
- v1.7: corrected by GLinear
- v1.8: slight improvements
- v2.0:
    - Improved and corrected median and median3
    - Improved linear
    - Look at the examples! The use of these filters has slightly changed.
- v2.1: Calculation of delta in linear filter corrected
- v2.2: Compilation error corrected
- v3.0: FastFilter and RingAverage added
- v3.1: Optimizing code for many filters
- v3.1.1: Error corrected
- v3.2: small fixes, updated documentation

<a id="feedback"></a>
## Bugs and feedback
If you find bugs, create **Issue**, or better write to the mail immediately.[alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
The library is open for revision and your **Pull Requests*!

When reporting bugs or incorrect work of the library, it is necessary to specify:
- Library version
- What is used by the IC
- SDK version (for ESP)
- Arduino IDE version
- Are embedded examples that use features and designs that cause bugs in your code working correctly?
- What code was downloaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed. Not a canvas of a thousand lines, but a minimum code.
