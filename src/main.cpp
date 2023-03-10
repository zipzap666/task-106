#include <iostream>

#include "events.h"
#include "devices.h"
#include "EventQueue.h"
#include <thread>
#include <mutex>

void blockCout(std::mutex &mtx, std::string str)
{
    std::unique_lock<std::mutex> u_mtx(mtx);
    std::cout << str << std::endl;
}


int main(){
    
    std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
    std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();    

    EventQueue queue;
    std::chrono::seconds time_out(5);
    std::mutex cout_mtx;

    std::condition_variable cv;
    

    std::thread threadA([&queue, &cout_mtx](std::shared_ptr<Device> device)
    {
        int n = 2;
        while (n--)
        {
            queue.push(std::make_shared<StartedEvent>(device));
            queue.push(std::make_shared<WorkDoneEvent>(device));
            queue.push(std::make_shared<DataEvent>(device));
        }
    }, deviceA);

    std::thread threadB([&queue, &cout_mtx](std::shared_ptr<Device> device)
    {
        int n = 2;
        while (n--)
        {
            queue.push(std::make_shared<StartedEvent>(device));
            queue.push(std::make_shared<WorkDoneEvent>(device));
            queue.push(std::make_shared<DataEvent>(device));
        }
    }, deviceB);

    while(true)
    {
        auto event = queue.pop(time_out);
        if(event != nullptr)
        {
            blockCout(cout_mtx, event->toString());
        }else{
            break;
        }
    }

    threadA.join();
    threadB.join();
    return 0;
}