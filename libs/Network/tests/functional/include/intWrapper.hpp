/*
** EPITECH PROJECT, 2021
** intWrapper.hpp
** File description:
** fake data wrapper
*/

#ifndef R_TYPE_INTWRAPPER_HPP
#define R_TYPE_INTWRAPPER_HPP

class intWrapper {
  public:
    intWrapper() = default;
    explicit intWrapper(int val) : _val(val){};
    ~intWrapper() = default;

    [[nodiscard]] std::size_t length() const
    {
        return sizeof(intWrapper);
    }

    [[nodiscard]] int getVal() const
    {
        return _val;
    }

    [[nodiscard]] int getOtherVal() const
    {
        return _otherVal;
    }

    [[nodiscard]] uint8_t *serialize() const
    {
        auto data(new uint8_t[sizeof(intWrapper)]);

        memcpy(data, &_val, sizeof(int));
        memcpy(data + sizeof(int), &_otherVal, sizeof(int));
        return data;
    }

    intWrapper(uint8_t *data, const std::size_t len)
    {
        if (len != sizeof(intWrapper)) {
            return;
        }
        memcpy(&_val, data, sizeof(int));
        memcpy(&_otherVal, data + sizeof(int), sizeof(int));
    }

  private:
    int _val{111};
    int _otherVal{333};
};
#endif // R_TYPE_INTWRAPPER_HPP