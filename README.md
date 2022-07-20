[![arduino-library-badge](https://www.ardu-badge.com/badge/GyverFilters.svg?)](https://www.ardu-badge.com/GyverFilters)
[![Foo](https://img.shields.io/badge/Website-AlexGyver.ru-blue.svg?style=flat-square)](https://alexgyver.ru/)
[![Foo](https://img.shields.io/badge/%E2%82%BD$%E2%82%AC%20%D0%9D%D0%B0%20%D0%BF%D0%B8%D0%B2%D0%BE-%D1%81%20%D1%80%D1%8B%D0%B1%D0%BA%D0%BE%D0%B9-orange.svg?style=flat-square)](https://alexgyver.ru/support_alex/)
[![Foo](https://img.shields.io/badge/README-ENGLISH-blueviolet.svg?style=flat-square)](https://github-com.translate.goog/GyverLibs/GyverFilters?_x_tr_sl=ru&_x_tr_tl=en)  

[![Foo](https://img.shields.io/badge/ПОДПИСАТЬСЯ-НА%20ОБНОВЛЕНИЯ-brightgreen.svg?style=social&logo=telegram&color=blue)](https://t.me/GyverLibs)

# GyverFilters
GyverFilters - библиотека с некоторыми удобными фильтрами для Arduino
- GFilterRA - компактная альтернатива фильтра экспоненциальное бегущее среднее (Running Average)			
- GMedian3 - быстрый медианный фильтр 3-го порядка (отсекает выбросы)
- GMedian - медианный фильтр N-го порядка. Порядок настраивается в GyverFilters.h - MEDIAN_FILTER_SIZE
- GABfilter - альфа-бета фильтр (разновидность Калмана для одномерного случая)
- GKalman - упрощённый Калман для одномерного случая (на мой взгляд лучший из фильтров)
- GLinear - линейная аппроксимация методом наименьших квадратов для двух массивов
- FastFilter - быстрый целочисленный экспоненциальный фильтр
- RingAverage - бегущее среднее с кольцевым буфером

Основано на [уроке по цифровым фильтрам](https://alexgyver.ru/lessons/filters/)

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

### Документация
К библиотеке есть [расширенная документация](https://alexgyver.ru/GyverFilters/)

## Содержание
- [Установка](#install)
- [Использование](#usage)
- [Версии](#versions)
- [Баги и обратная связь](#feedback)

<a id="install"></a>
## Установка
- Библиотеку можно найти по названию **GyverFilters** и установить через менеджер библиотек в:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Скачать библиотеку](https://github.com/GyverLibs/GyverFilters/archive/refs/heads/main.zip) .zip архивом для ручной установки:
    - Распаковать и положить в *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Распаковать и положить в *C:\Program Files\Arduino\libraries* (Windows x32)
    - Распаковать и положить в *Документы/Arduino/libraries/*
    - (Arduino IDE) автоматическая установка из .zip: *Скетч/Подключить библиотеку/Добавить .ZIP библиотеку…* и указать скачанный архив
- Читай более подробную инструкцию по установке библиотек [здесь](https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Обновление
- Рекомендую всегда обновлять библиотеку: в новых версиях исправляются ошибки и баги, а также проводится оптимизация и добавляются новые фичи
- Через менеджер библиотек IDE: найти библиотеку как при установке и нажать "Обновить"
- Вручную: **удалить папку со старой версией**, а затем положить на её место новую. "Замену" делать нельзя: иногда в новых версиях удаляются файлы, которые останутся при замене и могут привести к ошибкам!


<a id="usage"></a>
## Использование
```cpp
// =========== ALPHA-BETTA alfaBeta.h ===========
// период дискретизации (измерений), process variation, noise variation
GABfilter(float delta, float sigma_process, float sigma_noise);

// период дискретизации (измерений), process variation, noise variation
void setParameters(float delta, float sigma_process, float sigma_noise);

// возвращает фильтрованное значение
float filtered(float value);
    
// ========== FAST FILTER FastFilter.h ==========
FastFilter; 
FastFilter(uint8_t k = 20);                     // коэффициент 0-31, dt 0
FastFilter(uint8_t k = 20, uint16_t dt = 0);    // коэффициент 0-31, dt в миллисекундах

void setK(uint8_t k);       // коэффициент 0-31
void setDt(uint16_t dt);    // установить период фильтрации в мс
void setPass(uint8_t pass); // установить режим пропуска (FF_PASS_MAX / FF_PASS_MIN)
void setRaw(long raw);      // установить исходное значение для фильтрации
void setFil(long fil);      // установить фильтрованное значение
bool checkPass(long val);   // проверка на переполнение
void compute();             // расчёт по таймеру
void computeNow();          // произвести расчёт сейчас
int getFil();               // получить фильтрованное значение
int getRaw();               // получить последнее сырое значение

// =========== SIMPLE KALMAN kalman.h ===========
// разброс измерения, разброс оценки, скорость изменения значений
GKalman(float mea_e, float est_e, float q);
// разброс измерения, скорость изменения значений (разброс измерения принимается равным разбросу оценки)
GKalman(float mea_e, float q);

// разброс измерения, разброс оценки, скорость изменения значений
void setParameters(float mea_e, float est_e, float q);

// разброс измерения, скорость изменения значений (разброс измерения принимается равным разбросу оценки)
void setParameters(float mea_e, float q);

// возвращает фильтрованное значение
float filtered(float value);

// ======== LINEAR APPROXIMATION linear.h =======
GLinear<тип_данных> filter;

void compute(*x_array, *y_array, arrSize);    // аппроксимировать
float getA();       // получить коэффициент А
float getB();       // получить коэффициент В
float getDelta();   // получить аппроксимированное изменение

// ============= MEDIAN N median.h ==============
GMedian<порядок, тип_данных> median;

тип_данных filtered(тип_данных value);      // получить результат

// ============= MEDIAN 3 median3.h ==============
GMedian3<тип_данных> median;

тип_данных filtered(тип_данных value);      // получить результат

// ========= RING AVERAGE RingAverage.h =========
RingAverage<тип_данных, порядок> filter;

тип_данных filtered(тип_данных val);        // получить результат
float filteredFloat(тип_данных val);        // получить результат float

// ====== RUNNING AVERAGE runningAverage.h ======
GFilterRA filter;
GFilterRA(float coef);                      // установить коэффициент
GFilterRA(float coef, uint16_t interval);   // установить коэффициент и период

void setCoef(float coef);                   // установить коэффициент
void setPeriod(uint16_t interval);          // установить период
float filteredTime(float value);            // получить результат по таймеру
float filtered(float value);                // получить результат сейчас
```

<a id="versions"></a>
## Версии
- v1.6 от 12.11.2019
- v1.7: исправлен GLinear
- v1.8: небольшие улучшения
- v2.0:
    - Улучшен и исправлен median и median3
    - Улучшен linear
    - Смотрите примеры! Использование этих фильтров чуть изменилось
- v2.1: Исправлен расчёт дельты в линейном фильтре
- v2.2: Исправлена ошибка компиляции
- v3.0: Добавлен FastFilter и RingAverage
- v3.1: Оптимизация кода у многих фильтров
- v3.1.1: Исправлена ошибочка
- v3.2: мелкие фиксы, обновлена документация

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!


При сообщении о багах или некорректной работе библиотеки нужно обязательно указывать:
- Версия библиотеки
- Какой используется МК
- Версия SDK (для ESP)
- Версия Arduino IDE
- Корректно ли работают ли встроенные примеры, в которых используются функции и конструкции, приводящие к багу в вашем коде
- Какой код загружался, какая работа от него ожидалась и как он работает в реальности
- В идеале приложить минимальный код, в котором наблюдается баг. Не полотно из тысячи строк, а минимальный код
