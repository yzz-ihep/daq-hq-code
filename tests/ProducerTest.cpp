#include <memory>
#include <thread>
#include <unistd.h>

#include "producer/ProducerServer.h"
#include "message/IMultiDataMessage.h"

using namespace message_pass;

class TestMessage2 : virtual public IMultiDataMessage
{
public:
    size_t get_buf_num()
    {
        return 0;
    }
    size_t get_key()
    {
        return 100;
    }
    void set_key(std::size_t key) {}
    void add_buf(size_t size) {}
    std::pair<void*, std::size_t> operator[](std::size_t) {
        return std::pair<void*, std::size_t>(nullptr, 0);
    }
};

int main(void)
{

    std::shared_ptr<ProducerServer<TestMessage2>>
        cs(new ProducerServer<TestMessage2>("192.168.37.201:9092", {"test"}, 1));
    std::thread start_thread([&]() {
        cs->start();
    });
    start_thread.join();

    sleep(500);
    cs->stop();
    return 0;
}
