#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

void client_func() {
	boost::asio::io_context io;
	tcp::resolver resolver(io);
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));
	tcp::socket socket(io);
	boost::asio::connect(socket, resolver.resolve("127.0.0.1", "8080"));

	std::string input_name;
	char reply[1024];
	int reply_length;
	while (true) {
		do {
			std::cout << "What is your name?: ";
			std::getline(std::cin, input_name);
		} while (input_name.length() == 0);
		boost::asio::write(socket, boost::asio::buffer(input_name.c_str(), input_name.size()));
		for (;;) {
			reply_length = socket.read_some(boost::asio::buffer(reply));
			if (reply_length != 0) {
				break;
			}
		}
		for (int i = 0; i < reply_length; ++i) {
			std::cout << reply[i];
		}
		std::cout << std::endl;
	}
}

void server() {
	boost::asio::io_context io;
	tcp::acceptor acceptor(io, tcp::endpoint(tcp::v4(), 8080));

	std::string reply("Hello ");
	char req[1024];
	int req_length;
	acceptor.async_accept([&req, &req_length, &reply](const boost::system::error_code& error, tcp::socket socket) {
		while (true) {
			if (!error) {
				for (;;) {
					try {
						req_length = socket.read_some(boost::asio::buffer(req));
					}
					catch (const std::exception& e) {
						std::cout << e.what();
					}
					if (req_length != 0) {
						break;
					}
				}
				reply.append(req, req_length);
				boost::asio::write(socket, boost::asio::buffer(reply.c_str(), reply.size()));
				reply.erase(6, req_length);
			}
		}
		});
	io.run();
}

int main() {
	std::thread client(&client_func);
	server();
	if (client.joinable()) {
		client.join();
	}
	return 0;
}