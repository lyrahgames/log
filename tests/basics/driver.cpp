#include <lyrahgames/log/log.hpp>

using namespace std;
using namespace lyrahgames;

int main() {
  log::log log{};
  // log.quiet = true;
  log.info("This is an information for the user.");
  log.warning("This is a warning.");
  log.error("This is an error.");
}
