#include "graphics/geometry.h"
#include "graphics/screen.h"

#include <unistd.h>


int main() {
    Graphics::screenInitialize();
    sleep(1);
    Graphics::screenFinalize();
    return 0;
}