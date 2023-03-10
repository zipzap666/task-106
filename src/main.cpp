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

    size_t count_read_A = 10;
    size_t count_read_B = 1;
    
    std::shared_ptr<Device> deviceA = std::make_shared<DeviceA>();
    std::shared_ptr<Device> deviceB = std::make_shared<DeviceB>();    

    EventQueue queue;
    std::chrono::seconds time_out(5);
    std::mutex cout_mtx;

    std::condition_variable cv;
    

    std::thread threadA([&queue, &count_read_A](std::shared_ptr<Device> device)
    {
        queue.push(std::make_shared<StartedEvent>(device));
        while (count_read_A--)
        {
            queue.push(std::make_shared<DataEvent>(device));
        }
        queue.push(std::make_shared<WorkDoneEvent>(device));
    }, deviceA);

    std::thread threadB([&queue, &count_read_B](std::shared_ptr<Device> device)
    {
        queue.push(std::make_shared<StartedEvent>(device));
        while (count_read_B--)
        {
            queue.push(std::make_shared<DataEvent>(device));
        }
        queue.push(std::make_shared<WorkDoneEvent>(device));
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