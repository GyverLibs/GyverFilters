![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)
![author](https://img.shields.io/badge/author-AlexGyver-informational.svg)
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

### Совместимость
Совместима со всеми Arduino платформами (используются Arduino-функции)

### Документация
К библиотеке есть [расширенная документация](https://alexgyver.ru/GyverFilters/)

## Содержание
- [Установка](#install)
- [Инициализация](#init)
- [Использование](#usage)
- [Пример](#example)
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

<a id="init"></a>
## Инициализация
См. примеры

<a id="usage"></a>
## Использование
```cpp
// ============== Бегущее среднее ==============
GFilterRA();                                // инициализация фильтра
GFilterRA(float coef, uint16_t interval);   // расширенная инициализация фильтра (коэффициент, шаг фильтрации)
void setCoef(float coef);                   // настройка коэффициента фильтрации (0.00 - 1.00). Чем меньше, тем плавнее
void setStep(uint16_t interval);            // установка шага фильтрации (мс). Чем меньше, тем резче фильтр
  
float filteredTime(int16_t value);          // возвращает фильтрованное значение с опорой на встроенный таймер  
float filtered(int16_t value);              // возвращает фильтрованное значение
  
float filteredTime(float value);            // возвращает фильтрованное значение с опорой на встроенный таймер  
float filtered(float value);                // возвращает фильтрованное значение
// ============== Медиана из трёх ==============
GMedian3();                     // инициализация фильтра
uint16_t filtered(uint16_t);    // возвращает фильтрованное значение
// ============== Медиана из MEDIAN_FILTER_SIZE (настраивается в GyverFilters.h) ==============
GMedian();                      // инициализация фильтра
uint16_t filtered(uint16_t);    // возвращает фильтрованное значение
// ============== Альфа-Бета фильтр ==============
GABfilter(float delta, float sigma_process, float sigma_noise);
// период дискретизации (измерений), process variation, noise variation
    
void setParameters(float delta, float sigma_process, float sigma_noise);
// период дискретизации (измерений), process variation, noise variation
    
float filtered(float value);      // возвращает фильтрованное значение
// ============== Упрощённый Калман ==============
GKalman(float mea_e, float est_e, float q);
// разброс измерения, разброс оценки, скорость изменения значений
    
GKalman(float mea_e, float q);
// разброс измерения, скорость изменения значений (разброс измерения принимается равным разбросу оценки)
    
void setParameters(float mea_e, float est_e, float q);
// разброс измерения, разброс оценки, скорость изменения значений
    
void setParameters(float mea_e, float q);
// разброс измерения, скорость изменения значений (разброс измерения принимается равным разбросу оценки)
    
float filtered(float value);     // возвращает фильтрованное значение
// ============== Линейная аппроксимация ==============
void compute(int *x_array, int *y_array, int arrSize);    // аппроксимировать
float getA();    // получить коэффициент А
float getB();    // получить коэффициент В
float getDelta();  // получить аппроксимированное изменение
```

<a id="example"></a>
## Пример
Остальные примеры смотри в **examples**!
```cpp
/*
	Пример использования медианного фильтра.
*/

#include "GyverFilters.h"

// указываем размер окна и тип данных в <>
GMedian<10, int> testFilter;    

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(80);
  int value = analogRead(0);
  // добавляем шум "выбросы"
  value += random(2) * random(2) * random(-1, 2) * random(50, 250);
  Serial.print(value);
  Serial.print(',');  
  value = testFilter.filtered(value);
  Serial.println(value);
}
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

<a id="feedback"></a>
## Баги и обратная связь
При нахождении багов создавайте **Issue**, а лучше сразу пишите на почту [alex@alexgyver.ru](mailto:alex@alexgyver.ru)  
Библиотека открыта для доработки и ваших **Pull Request**'ов!