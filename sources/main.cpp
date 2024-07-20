#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "graphics/primitives.h"

#include <unistd.h>


int main() {
    Graphics::screenInitialize();
    Graphics::drawBox(Graphics::Rectangle(Graphics::Point(1, 1), 5, 5),
        Graphics::Color::BLACK, Graphics::Color::RED);
    Graphics::screenRefresh();
    sleep(10);
    Graphics::screenFinalize();
    return 0;
}