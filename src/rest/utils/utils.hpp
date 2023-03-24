#pragma once

#include <vector>
#include <string>

/// @brief Просчитать MD5 Хэш
/// @param input Данные
/// @return Строка с хэшем
std::string HashMD5(const std::vector<uint8_t> &input);

/// @brief Просчитать MD5 Хэш
/// @param input Строка
/// @return Строка с хэшем
std::string HashMD5(const std::string &input);
