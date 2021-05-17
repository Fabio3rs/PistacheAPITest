/**
 *@file CController.cpp
 * @author Fabio Rossini Sluzala ()
 * @brief
 * @version 0.1
 * @date 2021-05-16
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "CController.hpp"
#include <exception>

void CController::register_routes(const std::string&, Pistache::Rest::Router&)
{
    throw std::runtime_error("CController::register_routes should not be called");
}
