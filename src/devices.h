#include <string>


class Device
{
public:
    Device() : _data(nullptr){}

    virtual ~Device()
    {
        if(_data != nullptr)
        {
            delete[] _data;
        }
    }

    virtual std::string getName() = 0;
    std::string getDataAsString()
    {
        return std::string(_data, _data_size);
    }
private:
    char* _data;
    size_t _data_size;
};

class DeviceA : Device
{
public:

    std::string getName() override
    {
        return "A";
    }
};

class DeviceB : Device
{
public:

    std::string getName() override
    {
        return "A";
    }
};