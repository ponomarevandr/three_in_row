#include "graphics/geometry.h"
#include "graphics/screen.h"
#include "graphics/primitives.h"
#include "debug/output.h"

#include <unistd.h>


int main() {
    Graphics::screenInitialize();
    Graphics::fillRectangle(Graphics::Rectangle(Graphics::Point(0, 0), Graphics::getScreenWidth()-1,
        Graphics::getScreenHeight()-1),
        Graphics::Color::RED);
    Graphics::drawString(L"xo▽", Graphics::Point(2, 3), Graphics::Color::BLACK,
        Graphics::Color::RED);
    Graphics::screenRefresh();
    sleep(10);
    Debug::output.getStream() << Graphics::getScreenWidth() << " " << Graphics::getScreenHeight() << "\n";
    Graphics::screenFinalize();
    return 0;
}