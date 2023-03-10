#ifndef EVENT_INTERFACE_H
#define EVENT_INTERFACE_H
#include <string>

class Event
{
public:
    virtual ~Event(){};
    virtual std::string toString() const = 0;
};

#endif // EVENT_INTERFACE_H