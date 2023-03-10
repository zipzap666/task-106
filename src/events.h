#ifndef EVENTS_H
#define EVENTS_H

#include <memory>
#include <string>

#include "EventInterface.h"
#include "devices.h"

class DeviceEvent : public Event
{
public:
    DeviceEvent(std::shared_ptr<Device> device) : _device(device){};
    virtual ~DeviceEvent() {};

    virtual std::string toString() const override = 0;

protected:
    std::shared_ptr<Device> _device;
};

class DataEvent : public DeviceEvent
{
public:
    DataEvent(std::shared_ptr<Device> device) : DeviceEvent(device){};

    std::string toString() const override
    {
        return _device->getName() + ": " + _device->getDataAsString();
    };
};

class WorkDoneEvent : public DeviceEvent
{
public:
    WorkDoneEvent(std::shared_ptr<Device> device) : DeviceEvent(device)
    {
        if(_device->getName() == "A")
            std::this_thread::sleep_for(std::chrono::seconds(1));
        else if (_device->getName() == "B")
            std::this_thread::sleep_for(std::chrono::seconds(5));
    };

    std::string toString() const override
    {   
        return _device->getName() + " : Work done!";
    };
};

class StartedEvent : public DeviceEvent
{
public:
    StartedEvent(std::shared_ptr<Device> device) : DeviceEvent(device){};

    std::string toString() const override 
    {
        return _device->getName() + " : Work start!";
    };
};


#endif // EVENTS_H