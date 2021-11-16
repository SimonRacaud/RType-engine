/*
** EPITECH PROJECT, 2021
** RType
** File description:
** EnemyLoader
*/

#ifndef ENEMYLOADER_HPP_
#define ENEMYLOADER_HPP_

#include "IEnemyApi.hpp"
#include "Exception/RuntimeException.hpp"
#include "DLLoader/DLLoader.hpp"

IEnemyApi *loadEnemyApi(const std::string &path);
void closeEnemyApi(IEnemyApi *ptr);

#endif /* !ENEMYLOADER_HPP_ */
