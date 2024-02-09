#ifndef WAYPOINTMACHINE_H_
#define WAYPOINTMACHINE_H_

enum {WP_LOOP, WP_SINGLE};
// Class to handle all Waypoint stuff
class WaypointMachine
{
    private:
        std::vector<const sf::Vector2f*> Waypoints;
        bool validateAccess(const unsigned int pos);
        unsigned int currentWaypoint;
        unsigned int wpMode;
    public:
        WaypointMachine(const unsigned int reserve = 0);
        const sf::Vector2f getCurrentWaypoint();
        const sf::Vector2f getWaypoint(const unsigned int pos);
        void addWaypoint(const float x, const float y);
        void moveToNextWaypoint();
        void removeWaypoint(const unsigned int pos);
        void removeCurrentWaypoint();
        void setMode(unsigned int wpM) {wpMode = wpM;}
        unsigned int getCurrentWaypointIndex() {return currentWaypoint;}
        bool empty();
};

#endif // WAYPOINTMACHINE_H_
