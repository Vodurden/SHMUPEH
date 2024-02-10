#include "WaypointMachine.h"

#include "Logger.h"

bool WaypointMachine::empty()
{
    return Waypoints.empty();
}

bool WaypointMachine::validateAccess(const unsigned int pos)
{
    if(pos < Waypoints.size())
    {
        return true;
    }
    else
    {
        Logger::log("accessed an invalid waypoint", LOGTYPE_ERROR);
        return false;
    }

    return false;
}

WaypointMachine::WaypointMachine(const unsigned int reserve)
{
    if(reserve > 0)
        Waypoints.reserve(reserve);

    currentWaypoint = 0;
    wpMode = WP_LOOP;
}

const sf::Vector2f WaypointMachine::getCurrentWaypoint()
{
    return *(Waypoints[currentWaypoint]);
}

const sf::Vector2f WaypointMachine::getWaypoint(const unsigned int pos)
{
    if(validateAccess(pos))
    {
        return *(Waypoints.at(pos));
    }
    else
    {
        sf::Vector2f a;
        Logger::log("attempt to access invalid waypoint", LOGTYPE_ERROR);
        return a;
    }
}

void WaypointMachine::addWaypoint(const float x, const float y)
{
    Waypoints.push_back(new sf::Vector2f(x, y));
}

void WaypointMachine::removeWaypoint(const unsigned int pos)
{
    if(validateAccess(pos))
    {
        std::vector<const sf::Vector2f*>::iterator tempIter = Waypoints.begin();
        tempIter += pos;
        Waypoints.erase(tempIter);
    }
}

void WaypointMachine::moveToNextWaypoint()
{
    switch(wpMode)
    {
        case WP_LOOP:
        {
            currentWaypoint++;
            if(currentWaypoint >= Waypoints.size())
                currentWaypoint = 0;
            break;
        }
        case WP_SINGLE:
        {
            removeCurrentWaypoint();
        }
    }
}

void WaypointMachine::removeCurrentWaypoint()
{
    std::vector<const sf::Vector2f*>::iterator tempIter = Waypoints.begin();
    tempIter += currentWaypoint;
    Waypoints.erase(tempIter);
}
