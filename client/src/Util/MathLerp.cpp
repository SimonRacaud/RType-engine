/*
** EPITECH PROJECT, 2021
** RType
** File description:
** MathLerp
*/

#include "EngineCore.hpp"

float lerp(float minValue, float maxValue, float norm)
{
	return (maxValue - minValue) * norm + minValue;
}