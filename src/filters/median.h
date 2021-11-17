// медианный фильтр N-го порядка

#ifndef _GMedian_h
#define _GMedian_h

template < uint8_t SIZE, typename TYPE >
class GMedian {
public:
    TYPE filtered(TYPE newVal) {
        buffer[_count] = newVal;
        if ((_count < SIZE - 1) && (buffer[_count] > buffer[_count + 1])) {
            for (int i = _count; i < SIZE - 1; i++) {
                if (buffer[i] > buffer[i + 1]) {
                    TYPE buff = buffer[i];
                    buffer[i] = buffer[i + 1];
                    buffer[i + 1] = buff;
                }
            }
        } else {
            if ((_count > 0) && (buffer[_count - 1] > buffer[_count])) {
                for (int i = _count; i > 0; i--) {
                    if (buffer[i] < buffer[i - 1]) {
                        TYPE buff = buffer[i];
                        buffer[i] = buffer[i - 1];
                        buffer[i - 1] = buff;
                    }
                }
            }
        }
        if (++_count >= SIZE) _count = 0;
        return buffer[SIZE / 2];
    }
private:
    TYPE buffer[SIZE];
    uint8_t _count = 0;
};
#endif