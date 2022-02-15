// быстрый целочисленный экспоненциальный фильтр

#ifndef _FastFilter_h
#define _FastFilter_h

#define FF_PASS_MAX 1
#define FF_PASS_MIN 2

class FastFilter {
public:
    // коэффициент 0-31
    FastFilter(uint8_t k = 20, uint16_t dt = 0) {
        setK(k);
        setDt(dt);
    }
    
    // коэффициент 0-31
    void setK(uint8_t k) {
        _k1 = k;
        _k2 = 32 - k;
    }
    
    // установить период фильтрации
    void setDt(uint16_t dt) {
        _dt = dt;
    }
    
    // установить режим пропуска (FF_PASS_MAX / FF_PASS_MIN)
    void setPass(uint8_t pass) {
        _pass = pass;
    }
    
    // установить исходное значение для фильтрации
    void setRaw(long raw) {
        _raw = raw;
    }
    
    // установить фильтрованное значение
    void setFil(long fil) {
        _raw_f = fil;
    }
    
    // проверка на переполнение
    bool checkPass(long val) {
        if (_pass == FF_PASS_MAX && val > _raw_f) {
            _raw_f = val;
            return 1;
        } else if (_pass == FF_PASS_MIN && val < _raw_f) {
            _raw_f = val;
            return 1;
        }
        return 0;
    }
    
    // расчёт по таймеру
    void compute() {
        if (_dt == 0 || millis() - _tmr >= _dt) {
            _tmr = millis();
            computeNow();
        }
    }
    
    // произвести расчёт сейчас
    void computeNow() {
        _raw_f = ((long)_k1 * _raw_f + _k2 * _raw) >> 5;
    }
    
    // получить фильтрованное значение
    long getFil() {
        return _raw_f;
    }
    
    // получить последнее сырое значение
    long getRaw() {
        return _raw;
    }
    
private:
    uint32_t _tmr = 0;
    uint16_t _dt = 0;
    uint8_t _k1 = 20, _k2 = 12;
    uint8_t _pass = 0;
    long _raw_f = 0, _raw = 0;
};
#endif