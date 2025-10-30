#pragma once
#include <glm/glm.hpp>
#include <variant>

class CallbackContext
{
public:
    using ValueType = std::variant<std::monostate, bool, float, glm::vec2>;

    CallbackContext() = default;

    template<typename T>
    explicit CallbackContext(const T& value)
        : value_(value) {}

    template<typename T>
    T ReadValue() const
    {
        if (auto val = std::get_if<T>(&value_))
            return *val;
        else
            return T{}; // �^���Ⴆ�΃f�t�H���g�l��Ԃ�
    }

private:
    ValueType value_;
};

