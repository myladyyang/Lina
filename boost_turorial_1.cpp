#include <iostream>
#include <boost/asio.hpp>
#include <functional>
#include <array>
#include <boost/date_time/posix_time/posix_time.hpp>

using boost::asio::ip::tcp;

int main(int argc,char* argv[]){
  if(argc !=2){
    std::cerr << "Using Client <host>" << std::endl;
    return 1;
  }
  try{
    boost::asio::io_service io_service;
    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1],"daytime");
    tcp::resolver::iterator endpoint_iterator =resolver.resolve(query);
    tcp::socket socket(io_service);

    boost::asio::connect(socket,endpoint_iterator);

    for(;;){
      boost::array<char,128> buf;
      boost::system::error_code error;
    
      size_t len = socket.read_some(boost::asio::buffer(buf),error);

      if(error == boost::asio::error::eof){
	break;
      }
      else if(error){
	throw boost::system::system_error(error);
      }
      std::cout.write(buf.data(),len);
    }
  }catch (std::exception &e){
    std::cerr << e.what() << std::endl;
  }
}

