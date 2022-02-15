/*
    GyverFilters - библиотека с некоторыми удобными фильтрами для Arduino
    Документация: https://alexgyver.ru/gyverfilters/
    GitHub: https://github.com/GyverLibs/GyverFilters
    - GFilterRA - компактная альтернатива фильтра экспоненциальное бегущее среднее (Running Average)			
    - GMedian3 - быстрый медианный фильтр 3-го порядка (отсекает выбросы)
    - GMedian - медианный фильтр N-го порядка. Порядок настраивается в GyverFilters.h - MEDIAN_FILTER_SIZE
    - GABfilter - альфа-бета фильтр (разновидность Калмана для одномерного случая)
    - GKalman - упрощённый Калман для одномерного случая (на мой взгляд лучший из фильтров)
    - GLinear - линейная аппроксимация методом наименьших квадратов для двух массивов
    - FastFilter - быстрый целочисленный экспоненциальный фильтр
    - RingAverage - бегущее среднее с кольцевым буфером
    
    AlexGyver, alex@alexgyver.ru
    https://alexgyver.ru/
    MIT License
    
    Версии:
    v1.6 от 12.11.2019
    v1.7: исправлен GLinear
    v1.8: небольшие улучшения
    v2.0:
        - Улучшен и исправлен median и median3
        - Улучшен linear
        - Смотрите примеры! Использование этих фильтров чуть изменилось
    v2.1: Исправлен расчёт дельты в линейном фильтре
    v2.2: Исправлена ошибка компиляции
    v3.0: Добавлен FastFilter и RingAverage
    v3.1: Оптимизация кода у многих фильтров
    v3.1.1: Исправлена ошибочка
    v3.2: мелкие фиксы, обновлена документация
*/

#ifndef _GyverFilters_h
#define _GyverFilters_h
#include <Arduino.h>
#include <filters/alfaBeta.h>
#include <filters/kalman.h>
#include <filters/linear.h>
#include <filters/median.h>
#include <filters/median3.h>
#include <filters/runningAverage.h>
#include <filters/FastFilter.h>
#include <filters/RingAverage.h>
#endif