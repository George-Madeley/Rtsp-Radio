#include "app/app.hpp"
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

  app::App app;
  if(!app.init())
  {
    std::cerr << "Failed to initialize the application." << std::endl;
    return 1;
  }
  app.start(source);

  return 0;
}
