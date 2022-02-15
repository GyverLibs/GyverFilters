// экспоненциальное бегущее среднее

#ifndef _GFilterRA_h
#define _GFilterRA_h

class GFilterRA {
public:
    GFilterRA(){}
    
    GFilterRA(float coef, uint16_t interval) {
        _coef = coef;
        _prd = interval;
    }

    GFilterRA(float coef) {
        _coef = coef;
    }

    void setCoef(float coef) {
        _coef = coef;
    }
    
    void setPeriod(uint16_t interval) {
        _prd = interval;
    }

    float filteredTime(float value) {
        if (millis() - _tmr >= _prd) {
            _tmr += _prd;
            filtered(value);
        }
        return _fil;
    }

    float filtered(float value) {
        return _fil += (value - _fil) * _coef;
    }
    
    //
    void setStep(uint16_t interval) {
        _prd = interval;
    }
    
private:
    float _coef = 0.0, _fil = 0.0;
    uint32_t _tmr = 0;
    uint16_t _prd = 0;
};
#endif