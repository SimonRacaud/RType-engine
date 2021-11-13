/*
** EPITECH PROJECT , 2021
** SetProgressBarValue
** File description:
** \file SetProgressBarValue.hpp
** \author simon
** \brief
** \date 13/11/2021
*/

#ifndef SETPROGRESSBARVALUE_HPP
#define SETPROGRESSBARVALUE_HPP

#include "Event/IEvent.hpp"
#include "CustomEntityName.hpp"

class SetProgressBarValue : public Engine::Event::IEvent
{
  public:
    SetProgressBarValue(Engine::EntityName name, size_t value)
    : _value(value), _name(name)
    {}
    virtual ~SetProgressBarValue() = default;

    std::type_index getType() const override {
        return std::type_index(typeid(this));
    }

    Engine::EntityName getName() const
    {
        return _name;
    }

    size_t getValue() const
    {
        return _value;
    }

  private:
    size_t _value;
    Engine::EntityName _name;
};

#endif // SETPROGRESSBARVALUE_HPP
