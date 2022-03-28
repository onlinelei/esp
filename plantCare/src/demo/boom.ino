#include <TFT_eSPI.h> // Hardware-specific library
#include <SPI.h>

TFT_eSPI tft = TFT_eSPI();       // Invoke custom library

// Maximum number of generations until the screen is refreshed
#define MAX_GEN_COUNT 500

// The ESP8266 has plenty of memory so we can create a large array
// 2 x 2 pixel cells, array size = 5120 bytes per array, runs fast
#define GRIDX 80
#define GRIDY 64
#define CELLXY 2

// 1 x 1 pixel cells, array size = 20480 bytes per array
//#define GRIDX 160
//#define GRIDY 128
//#define CELLXY 1

#define GEN_DELAY 10 // Set a delay between each generation to slow things down

//Current grid and newgrid arrays are needed
uint8_t grid[GRIDX][GRIDY];

//The new grid for the next generation
uint8_t newgrid[GRIDX][GRIDY];

//Number of generations
uint16_t genCount = 0;

//Draws the grid on the display
void drawGrid() {

    uint16_t color = TFT_WHITE;
    for (int16_t x = 1; x < GRIDX - 1; x++) {
        for (int16_t y = 1; y < GRIDY - 1; y++) {
            if ((grid[x][y]) != (newgrid[x][y])) {
                if (newgrid[x][y] == 1) color = 0xFFFF; //random(0xFFFF);
                else color = 0;
                tft.fillRect(CELLXY * x, CELLXY * y, CELLXY, CELLXY, color);
            }
        }
    }
}

//Initialise Grid
void initGrid() {
    for (int16_t x = 0; x < GRIDX; x++) {
        for (int16_t y = 0; y < GRIDY; y++) {
            newgrid[x][y] = 0;

            if (x == 0 || x == GRIDX - 1 || y == 0 || y == GRIDY - 1) {
                grid[x][y] = 0;
            }
            else {
                if (random(3) == 1)
                    grid[x][y] = 1;
                else
                    grid[x][y] = 0;
            }

        }
    }
}


int getNumberOfNeighbors(int x, int y) {
    return grid[x - 1][y] + grid[x - 1][y - 1] + grid[x][y - 1] + grid[x + 1][y - 1] + grid[x + 1][y] + grid[x + 1][y + 1] + grid[x][y + 1] + grid[x - 1][y + 1];
}


//Compute the CA. Basically everything related to CA starts here
void computeCA() {
    for (int16_t x = 1; x < GRIDX; x++) {
        for (int16_t y = 1; y < GRIDY; y++) {
            int neighbors = getNumberOfNeighbors(x, y);
            if (grid[x][y] == 1 && (neighbors == 2 || neighbors == 3 ))
            {
                newgrid[x][y] = 1;
            }
            else if (grid[x][y] == 1)  newgrid[x][y] = 0;
            if (grid[x][y] == 0 && (neighbors == 3))
            {
                newgrid[x][y] = 1;
            }
            else if (grid[x][y] == 0) newgrid[x][y] = 0;
        }
    }
}



void setup()   {

    //Set up the display
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(0, 0);

}

void loop() {

    //Display a simple splash screen
    tft.fillScreen(TFT_BLACK);
    tft.setTextSize(2);
    tft.setTextColor(TFT_WHITE);
    tft.setCursor(40, 5);
    tft.println(F("Arduino"));
    tft.setCursor(35, 25);
    tft.println(F("Cellular"));
    tft.setCursor(35, 45);
    tft.println(F("Automata"));

    delay(1000);

    tft.fillScreen(TFT_BLACK);

    initGrid();

    genCount = MAX_GEN_COUNT;

    drawGrid();

    //Compute generations
    for (int gen = 0; gen < genCount; gen++){
        computeCA();
        drawGrid();
        delay(GEN_DELAY);
        for (int16_t x = 1; x < GRIDX-1; x++) {
            for (int16_t y = 1; y < GRIDY-1; y++) {
                grid[x][y] = newgrid[x][y];
            }
        }

    }
}