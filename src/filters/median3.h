// быстрый медианный фильтр 3-го порядка

#ifndef _GMedian3_h
#define _GMedian3_h

template < typename TYPE >
class GMedian3 {
public:
    TYPE filtered(TYPE value) {	// возвращает фильтрованное значение
        buf[_counter] = value;
        if (++_counter > 2) _counter = 0;
        return (max(buf[0], buf[1]) == max(buf[1], buf[2])) ? max(buf[0], buf[2]) : max(buf[1], min(buf[0], buf[2]));
    }
    
private:
    TYPE buf[3];
    uint8_t _counter = 0;
};
#endif