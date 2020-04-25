#include "dealer_comm.h"

//main function for the dealer's side of the game
int main(int argc, char* argv[])
{
	try
	{
		if (argc < 2)
		{
			std::cerr << "Usage: chat_server <port> [<port> ...]\n";
		  return 1;
    }

    asio::io_context io_context;

		std::list<Dealer_comm> dealers;
		for (int i = 1; i < argc; ++i)
		{
			tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[i]));
			dealers.emplace_back(io_context, endpoint);
		}
		io_context.run();
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}
	return 0;
}