// экспоненциальное бегущее среднее

#ifndef _GFilterRA_h
#define _GFilterRA_h

class GFilterRA {
public:
    GFilterRA(){}
    
    GFilterRA(float coef, int interval) {
        _coef = coef;
        _prd = interval;
    }

    GFilterRA(float coef) {
        _coef = coef;
    }

    void setCoef(float coef) {
        _coef = coef;
    }
    
    void setStep(int interval) {
        _prd = interval;
    }

    float filteredTime(int value) {
        if (millis() - _tmr >= _prd) {
            _tmr = millis();
            filtered(value);
        }
        return _fil;
    }

    float filteredTime(float value) {
        if (millis() - _tmr >= _prd) {
            _tmr = millis();
            filtered(value);
        }
        return _fil;
    }

    float filtered(int value) {
        return _fil += (float)(value - _fil) * _coef;
    }

    float filtered(float value) {
        return _fil += (float)(value - _fil) * _coef;
    }
    
private:
    float _coef = 0.0, _fil = 0.0;
    uint32_t _tmr = 0;
    int _prd = 0;
};
#endif