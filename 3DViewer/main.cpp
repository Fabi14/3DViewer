#include "Viewer3D.h"


int main(void)
{
    Viewer3D app;
    if (app.init())
    {
        app.run();
    }

    return 0;
}