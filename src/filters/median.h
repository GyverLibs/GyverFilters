// медианный фильтр N-го порядка

#ifndef _GMedian_h
#define _GMedian_h

#include <stddef.h>
#include <utility>
#include <array>

template <typename T, size_t size>
struct GMedian
{
    GMedian (T value = T()) :
        index(0)
    {
        for (size_t i = 0; i != size; ++i)
        {
            ordered_values[i] = {value, i};
            position[i] = i;
        }
    }
    
    T filtered (T value)
    {
        size_t cur = position[index];
        if (++index == size)
            index = 0;
        ordered_values[cur].first = std::move(value);
        
        auto disordered = [this] (size_t index) -> bool 
        {
            return ordered_values[index + 1].first < ordered_values[index].first;
        };
        
        if ((cur != size - 1) && disordered(cur))
        {
            for (size_t i = cur; (i != size - 1) && disordered(i); ++i)
            {
                std::swap(position[ordered_values[i].second], position[ordered_values[i + 1].second]);
                std::swap(ordered_values[i], ordered_values[i + 1]);
            }
        }
        else if ((cur != 0) && disordered(cur - 1))
        {
            for (size_t i = cur; (i != 0) && disordered(i - 1); --i)
            {
                std::swap(position[ordered_values[i - 1].second], position[ordered_values[i].second]);
                std::swap(ordered_values[i - 1], ordered_values[i]);
            }
        }
        
        if constexpr (size % 2 == 1)
            return ordered_values[size / 2].first;
        else
            return (ordered_values[(size - 1) / 2].first + ordered_values[size / 2].first) / 2;
    }
    
private:
    std::array <std::pair <T, size_t>, size> ordered_values;
    std::array <size_t, size> position; 
    size_t index;
};

template <typename T>
struct GMedian <T, 0> 
{
    ~GMedian () = delete;
};

template <typename T>
struct GMedian <T, 1>
{
    GMedian (T = T())
        {}

    T filtered (T value)
    {
        return value;
    }
};

template <typename T>
struct GMedian <T, 2>
{
    GMedian (T value = T()) :
        a(value),
        b(value)
    {}

    T filtered (T value)
    {
        a = std::move(b);
        b = std::move(value);
        return (a + b) / 2;
    }

private:
    T a;
    T b;
};

template <typename T>
struct GMedian <T, 3>
{
    GMedian (T value = T()) :
        values{value, value, value},
        index(0)
    {}

    T filtered (T value)
    {
        values[index] = std::move(value);
        if (++index == 3)
            index = 0;
        
        if (values[0] < values[1])
        {
            if (values[1] < values[2])
                return values[1];
            else
                return std::max(values[0], values[2]);
        }
        else
        {
            if (values[1] < values[2])
                return std::min(values[0], values[2]);
            else
                return values[1];
        }
    }

private:
    std::array <T, 3> values;
    size_t index;
};


template <typename T>
struct GMedian <T, 4>
{
    GMedian (T value = T()) :
        values{value, value, value, value},
        index(0)
    {}

    T filtered (T value)
    {
        values[index] = std::move(value);
        if (++index == 4)
            index = 0;
        
        return (std::max(std::min(values[0], values[1]), std::min(values[2], values[3])) + 
                std::min(std::max(values[0], values[1]), std::max(values[2], values[3]))) / 2;
    }

private:
    std::array <T, 4> values;
    size_t index;
};

#endif
