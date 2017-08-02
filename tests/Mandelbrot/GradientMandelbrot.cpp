/*
 * GradientMandelbrot.cpp
 */

#include "GradientMandelbrot.h"

GradientMandelbrot::GradientMandelbrot(unsigned threads, unsigned depth) : Mandelbrot(threads, depth) {}

void GradientMandelbrot::draw(CartesianRasterCanvas& can) {
  const int CH = can.getWindowHeight();   //Height of our FastMandelbrot canvas
  while(myRedraw) {
    myRedraw = false;
    can.reset();
    int next = 0;
    Decimal maxX = can.getMaxX(); Decimal minX = can.getMinX();
    #pragma omp parallel num_threads(myThreads)
    {
      while(true) {
        int myNext;
        #pragma omp critical
        {
          myNext = next++;
        }
        if (myNext >= can.getWindowHeight())
          break;
        Decimal row = can.getMaxY() - myNext*can.getPixelHeight();
        for(Decimal col = minX; col <= maxX; col += can.getPixelWidth()) {
          complex c(col, row);
          complex z(col, row);
          int iterations = 0;
          while (std::abs(z) < 2.0l && iterations < myDepth) {
            iterations++;
            z = z * z + c;
          }
          if( iterations >= myDepth-1 ) { //If iterations reached myDepth
            can.drawPoint(col, row, BLACK);
          } else {
            float mu = iterations + 1 - log( log( std::abs(z) )) / log(2);
            if( mu < 0 ) can.drawPoint(col, row, ColorHSV(0, 1.0f, 0.6f, 1.0f)); //If we have a negative adjusted iterations
            else can.drawPoint(col, row, ColorHSV((mu/(float)myDepth)*6.0f, 1.0f, 0.6f, 1.0f));
          }
          if (myRedraw) break;
        }
        can.handleIO();
        if (myRedraw) break;
      }
    }
    printf("%f seconds to draw\n", can.getTime());
    printf("%Lfx scale\n", 1/(can.getCartHeight()/2));
    while (can.isOpen() && !myRedraw) {
      can.sleep(); //Removed the timer and replaced it with an internal timer in the Canvas class
    }
  }
}
