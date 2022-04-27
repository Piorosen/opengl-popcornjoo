#include <display/display.h>
#include <GL/glut.h>

display::rect display::info::primaryMonitor() { 
    display::rect result;

    result.point.x = 0;
    result.point.y = 0;
    result.size.width = glutGet(GLUT_SCREEN_WIDTH);
    result.size.height = glutGet(GLUT_SCREEN_HEIGHT);

    return result;
}

void display::convert::init(display::rect rect) { 
    
}