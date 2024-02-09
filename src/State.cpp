#include "State.h"

void State::handleEvents() {Logger::log(" base 'State' handleEvents() called", LOGTYPE_ERROR);}
void State::think() {Logger::log(" base 'State' think() called", LOGTYPE_ERROR);}
void State::draw() {Logger::log(" base 'State' draw() called", LOGTYPE_ERROR);}
bool State::isActive() {Logger::log(" base 'State' isActive() called", LOGTYPE_ERROR); return false;}
