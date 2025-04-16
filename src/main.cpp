#include "argparse/argparse.hpp"

#include <iostream>

int main(int argc, char* argv[])
{
  argparse::ArgumentParser program("RTSP Radio");

  program.add_argument("-s", "--source").help("File path to the source files").required();

  try
  {
    program.parse_args(argc, argv);
  }
  catch(const std::exception& err)
  {
    std::cerr << err.what() << std::endl;
    std::cerr << program;
    return 1;
  }

  auto source = program.get<std::string>("--source");
  std::cout << "Source: " << source << std::endl;
  return 0;
}
