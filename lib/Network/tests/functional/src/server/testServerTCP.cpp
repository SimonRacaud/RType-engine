/*
** EPITECH PROJECT, 2021
** mainTestNetwork.cpp
** File description:
** TODO: add description
*/

#include <cstring>
#include "AsioServerTCP.hpp"
#include <unordered_map>

using namespace Network;

class intWrapper {
  public:
    intWrapper() = default;
    intWrapper(int val) : _val(val){};
    ~intWrapper() = default;

    std::size_t size() const
    {
        return sizeof(intWrapper);
    }

    int getVal() const
    {
        return _val;
    }

    intWrapper *data() const
    {
        intWrapper *my_new = new intWrapper;

        *my_new = _val;
        *(my_new + sizeof(int)) = _otherVal;
        return my_new;
    }
    intWrapper &operator=(const intWrapper &rhs)
    {
        this->_val = rhs.getVal();
        return *this;
    }

  private:
    int _val{222};
    int _otherVal{444};
};

/**
 * @brief Test
 *  AsioServerTCP::startAccept()
 *  AsioServerTCP::receiveAny()
 * @return 0 if test succeeded
 */
int testServerAcceptReceive()
{
    const std::size_t portServer(8080);
    std::tuple<intWrapper, std::size_t, std::string, std::size_t> recvData; // TODO DATA replace by type
    AsioServerTCP<intWrapper> server(portServer);                           // TODO DATA replace by type
    intWrapper my_var;

    while (true) {
        recvData = server.receiveAny();
        if (std::get<1>(recvData)) {
            //            std::cout.write(std::get<0>(recvData).getVal(), std::get<1>(recvData));
            my_var = std::get<0>(recvData);
            std::cout << "my_var.getVal() : " << my_var.getVal() << std::endl;
            std::cout << std::endl;
            return 0;
        }
        // todo set clock to avoid infinite loop
        //  in shell script ?
        //  with Clock class ?
    }
    return 84;
}