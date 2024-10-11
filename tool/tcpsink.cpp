////////////////////////////////////////////////////////////////////////////////
//
//  YOUR QUILL
//
////////////////////////////////////////////////////////////////////////////////

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>
#include <memory>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>

using asio::ip::tcp;

static constexpr const size_t       kBufferSize     = 1024;

class session : public std::enable_shared_from_this<session> {
public:
    session(tcp::socket&& s) : m_socket(std::move(s))
    {
    }
    
    void start()
    {
        auto self(shared_from_this());
        m_socket.async_read_some(asio::buffer(m_buffer, kBufferSize), [this, self](std::error_code ec, std::size_t length){
            if(!ec){
                std::ignore =  write(1, m_buffer, length);
                start();
            }
        });
    }

private:
    tcp::socket     m_socket;
    char            m_buffer[kBufferSize];
};


class server {
public:
    server(asio::io_context& ctx, uint16_t port) : 
        m_acceptor(ctx, tcp::endpoint(tcp::v4(), port)),
        m_socket(ctx)
    {
    }

    void    start()
    {
        m_acceptor.async_accept(m_socket, [this](std::error_code ec){
            if(!ec)
                std::make_shared<session>(std::move(m_socket))->start();
            start();
        });
    }
    
private:
    tcp::acceptor   m_acceptor;
    tcp::socket     m_socket;
};

int main(int argc, char* argv[])
{
    if(argc <= 1){
        std::cout << "Usage: " << argv[0] << " <port>\n";
        return 0;
    }
    
    asio::error_code        ec;
    asio::io_context        ctx;
    server                  s(ctx, atoi(argv[1]));
    s.start();
    ctx.run();
    return 0;
}
