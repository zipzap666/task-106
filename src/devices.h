#ifndef DEVICES_H
#define DEVICES_H
#include <string>
#include <thread>
#include <chrono>

class Device
{
public:
    virtual ~Device(){};
    virtual std::string getName() = 0;
    virtual std::string getDataAsString() = 0;
};

class DeviceA : public Device 
{
public:
    DeviceA(){}

    std::string getDataAsString() override
    {
        size_t length = rand() % 5; // 501
        _data = "";
        for(size_t i = 0; i < length; ++i)
        {
            _data += static_cast<char>(rand() % 256);
        }
        return _data;
    }

    std::string getName() override
    {
        return "A";
    }

private:
    std::string _data;
};

class DeviceB : public Device
{
public:
    DeviceB(){}

    std::string getDataAsString() override
    {   
        _data = "";
        for(size_t i = 0; i < 3; ++i)
        {
            _data += std::to_string(rand() % 199) + " ";
        }
        return _data;
    }

    std::string getName() override
    {
        return "B";
    }

private:
    std::string _data;
};

#endif // DEVICES_H