This is an automatic translation, may be incorrect in some places. See sources and examples!

# GyverFilters
GyverFilters - library with some handy filters for Arduino
- GFilterRA - a compact alternative to the filter exponential running average (Running Average)
- GMedian3 - fast 3rd order median filter (cuts out outliers)
- GMedian - N-th order median filter. The order is configured in GyverFilters.h - MEDIAN_FILTER_SIZE
- GABfilter - alpha-beta filter (Kalman version for one-dimensional case)
- GKalman - a simplified Kalman for the one-dimensional case (in my opinion the best of the filters)
- GLinear - linear least squares approximation for two arrays
- FastFilter - fast integer exponential filter
- RingAverage - running average with ring buffer

Based on [Digital Filters Tutorial](https://alexgyver.ru/lessons/filters/)

### Compatibility
Compatible with all Arduino platforms (using Arduino functions)

### Documentation
The library has [extended documentation](https://alexgyver.ru/GyverFilters/)

## Content
- [Install](#install)
- [Usage](#usage)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found by the name **GyverFilters** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/GyverFilters/archive/refs/heads/main.zip) .zip archive forfor manual setting:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="usage"></a>
## Usage
```cpp
// =========== ALPHA-BETTA alfaBeta.h ===========
// sampling period (measurements), process variation, noise variation
GABfilter(float delta, float sigma_process, float sigma_noise);

// sampling period (measurements), process variation, noise variation
void setParameters(float delta, float sigma_process, float sigma_noise);

// returns the filtered value
float filtered(float value);
    
// ========== FAST FILTER FastFilter.h ==========
fastfilter;
FastFilter(uint8_t k = 20); // coefficient 0-31, dt 0
FastFilter(uint8_t k = 20, uint16_t dt = 0); // coefficient 0-31, dt in milliseconds

void setK(uint8_tk); // coefficient 0-31
void setDt(uint16_t dt); // set filtering period in ms
void setPass(uint8_t pass); // set pass mode (FF_PASS_MAX / FF_PASS_MIN)
void setRaw(long raw); // set initial value for filtering
void setFil(long fil); // set filtered value
bool checkPass(long val); // check for overflow
void compute(); // timer calculation
void computeNow(); // calculate now
int getfil(); // get filtered value
int getRaw(); // get last raw value

// =========== SIMPLE KALMAN kalman.h ===========
// measurement spread, estimate spread, speedvalue changes
GKalman(float mea_e, float est_e, float q);
// measurement scatter, rate of change of values ​​(measurement scatter is taken equal to the estimate scatter)
GKalman(float mea_e, float q);

// measurement spread, estimate spread, rate of change of values
void setParameters(float mea_e, float est_e, float q);

// measurement scatter, rate of change of values ​​(measurement scatter is taken equal to the estimate scatter)
void setParameters(float mea_e, float q);

// returns the filtered value
float filtered(float value);

// ======== LINEAR APPROXIMATION linear.h =======
GLinear<datatype> filter;

void compute(*x_array, *y_array, arrSize); // approximate
float getA(); // get factor A
float getB(); // get factor B
float getDelta(); // get approximate change

// ============= MEDIAN N median.h ==============
GMedian<order, datatype> median;

data_type filtered(data_type value); // get result

// ============= MEDIAN 3 median3.h ==============
GMedian3<datatype> median;

data_type filtered(data_type value); // get result

// ========= RING AVERAGE RingAverage.h =========
RingAverage<data_type, order> filter;

datatype filtered(datatype val); // get result
float filteredFloat(datatype val); // get float result

// ====== RUNNING AVERAGE runningAverage.h ======
GFilterRA filter;
GFilterRA(floatcoef); // set coefficient
GFilterRA(float coef, uint16_t interval); // set coefficient and period

void setCoef(floatcoef); // set coefficient
void setPeriod(uint16_t interval); // set period
float filteredTime(float value); // get result by timer
float filtered(float value); // get result now
```

<a id="versions"></a>
## Versions
- v1.6 from 11/12/2019
- v1.7: fixed GLinear
- v1.8: minor improvements
- v2.0:
    -Improved and fixed median and median3
    - Improved linear
    - See examples! The use of these filters has changed slightly
- v2.1: Fixed delta calculation in linear filter
- v2.2: Compilation error fixed
- v3.0: Added FastFilter and RingAverage
- v3.1: Code optimization for many filters
- v3.1.1: Bug fixed
- v3.2: minor fixes, updated documentation

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!