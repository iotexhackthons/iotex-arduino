#ifdef OS

#include "random/random.h"
#include "helpers/client_helpers.h"

#include <fcntl.h>
#include <unistd.h>

using namespace Iotex;

// Define global object
Random randomGenerator;

void Random::fillRandom(uint8_t *buf, size_t size)
{
    int fd = open("/dev/random", O_RDONLY);
    read(fd, buf, size);
}

#endif