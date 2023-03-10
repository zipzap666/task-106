#ifndef EVENT_QUEUE_H
#define EVENT_QUEUE_H
#include <memory>
#include <chrono>
#include <mutex>
#include <queue>
#include <condition_variable>
#include <thread>
#include "EventInterface.h"

class EventQueue
{
public:
    // Положить сообщение в очередь
    void push(const std::shared_ptr<const Event> &event)
    {
        std::unique_lock<std::mutex> u_mtx(mtx);
        queue.push(std::move(event));
        cv.notify_one();
    }

    // Удалить сообщение из очереди и вернуть его. По истечении duration, если очередь пуста, вернуть пустой указатель
    std::shared_ptr<const Event> pop(const std::chrono::seconds &duration)
    {
        std::unique_lock<std::mutex> u_mtx(mtx);
        if (cv.wait_for(u_mtx, duration, [this]
                        { return !queue.empty(); }))
        {
            auto event = queue.front();
            queue.pop();
            return event;
        }
        return nullptr;
    }

    bool isEmpty(){ return queue.empty();};

private:
    std::queue<std::shared_ptr<const Event>> queue;
    std::mutex mtx;
    std::condition_variable cv;
};

#endif // EVENT_QUEUE_H