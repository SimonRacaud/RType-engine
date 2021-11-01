/*
** PERSONAL PROJECT, 2021
** Singly GenericObject
** File description:
** GenericObject.hpp
*/

#ifndef GENERICOBJECT_HPP
#define GENERICOBJECT_HPP

#include <any>
#include <stdexcept>
#include <functional>
#include <unordered_map>

template<typename tokenType>
class GenericObject
{
    public:
        GenericObject(const tokenType &token, std::function<void (GenericObject<tokenType> &)> call = nullptr): _call(call), _token(token)
        {
        }
        GenericObject(const GenericObject<tokenType> &src): _call(src._call), _token(src._token), _list(src._list)
        {
        }
        GenericObject(): _call(nullptr), _token()
        {
        }

        ~GenericObject()
        {
            this->_list.clear();
        }

        /*
        **  SETTER
        */
        template <typename dataType, typename... constructorParams> void addData(const tokenType &key, constructorParams &&... params)
        {
            this->_list[typeid(dataType).hash_code()][key] = std::any(std::in_place_type<dataType>, dataType(std::forward<constructorParams>(params)...));
        }

        /*
        **  GETTER
        */

        template <typename dataType> [[nodiscard]] unsigned int getDataOccurence() const
        {
            try {
                return this->_list.at(typeid(dataType).hash_code()).size();
            } catch ([[maybe_unused]] const std::out_of_range &e) {
                return 0;
            }
        }

        template <typename dataType> [[nodiscard]] dataType getData(const tokenType &key) const
        {
            try {
                return std::any_cast<dataType>(this->_list.at(typeid(dataType).hash_code()).at(key));
            } catch (const std::out_of_range &e) {
                throw std::invalid_argument("Data does not exist: " + std::string(e.what()) + " type: " + typeid(dataType).name());
            } catch (const std::bad_any_cast &e) {
                throw std::invalid_argument("Bad Data: " + std::string(e.what()));
            }
        }

        template <typename dataType> [[nodiscard]] dataType getData() const
        {
            try {
                if (this->_list.at(typeid(dataType).hash_code()).size() != 1)
                    throw std::invalid_argument("Number of dataType is different than 0");
                return std::any_cast<dataType>(this->_list.at(typeid(dataType).hash_code()).begin()->second);
            } catch (const std::out_of_range &e) {
                throw std::invalid_argument("Data does not exist: " + std::string(e.what()) + " type: " + typeid(dataType).name());
            } catch (const std::bad_any_cast &e) {
                throw std::invalid_argument("Bad Data: " + std::string(e.what()));
            }
        }

        template <typename dataType> [[nodiscard]] bool isSetData(const tokenType &key) const
        {
            try {
                std::any_cast<dataType>(this->_list.at(typeid(dataType).hash_code()).at(key));
                return true;
            } catch ([[maybe_unused]] const std::out_of_range &e) {
                return false;
            } catch ([[maybe_unused]] const std::bad_any_cast &e) {
                return false;
            }
        }

        template <typename dataType> void removeData(const tokenType &key)
        {
            this->_list.at(typeid(dataType).hash_code()).erase(key);
        }

        template <typename dataType> void removeData()
        {
            this->_list.erase(typeid(dataType).hash_code());
        }

        void run()
        {
            if (this->_call != nullptr)
                this->_call(this);
        }

        void setRunning(std::function<void (GenericObject<tokenType> &)> call)
        {
            this->_call = call;
        }

        bool operator==(const tokenType &token)
        {
            return this->_token == token;
        }

        GenericObject &operator=(const GenericObject &src)
        {
            this->_list = src._list;
            this->_token = src._token;
            this->_call = src._call;
            return *this;
        }
    private:
        std::unordered_map<size_t, std::unordered_map<tokenType, std::any>> _list;
        std::function<void (GenericObject<tokenType> &)> _call;
        tokenType _token;
};

#endif