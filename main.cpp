#include "app.h"

int main( int argc, char* args[] )
{
    int windowWidth = 1280;
    int windowHeight = 640;
    int gridSize = 10;
    double speed = 0.8;
    int growth = 5;
    int apples = 100;
    int fpsCap = 1;
    double speedMul = 1.05;

    std::ifstream settings;
    settings.open("settings.txt");
    settings >> windowWidth >> windowHeight >> gridSize >> speed >> growth >> apples >> fpsCap >> speedMul;
    settings.close();

    // RESTRICTIONS

    windowWidth = std::max(100,windowWidth);
    windowHeight = std::max(100,windowHeight);
    gridSize = std::max(1,gridSize);

    speed = std::max(0.33,speed);
    growth = std::max(1,growth);
    apples = std::max(1,apples);
    apples = std::min(2000,apples);

    speedMul = std::max(1.d,speedMul);
    speedMul = std::min(1.5,speedMul);

    //(for better experience)
    if(speedMul >= 1.1)
        fpsCap=0;

    App app(windowWidth,windowHeight,apples,gridSize,growth,speed,fpsCap!=0,speedMul);
    app.run();
    return 0;
}
