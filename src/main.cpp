#include "app/app.hpp"
#include "argparse/argparse.hpp"
#include "loguru.hpp"

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

  loguru::g_preamble_date = false;
  loguru::g_preamble_time = false;
  loguru::g_preamble_file = false;
  loguru::g_preamble_thread = false;

  loguru::init(argc, argv);

  auto source = program.get<std::string>("--source");

  app::App app;
  if(!app.init())
  {
    LOG_S(FATAL) << "Failed to initialize the application.";
    return 1;
  }
  app.start(source);

  return 0;
}
