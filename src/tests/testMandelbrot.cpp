/*
 * testMandelbrot.cpp
 *
 *  Created on: May 27, 2015
 *      Author: cpd5
 */

#include "Mandelbrot/Mandelbrot.h"

using namespace tsgl;

/*!
 * \brief Draws the Mandelbrot set on a CartesianCanvas with custom controls, a specified target update rate,
 *  and a dynamic number of threads and uses command-line arguments to specify the number of threads to use.
 *  There is also a ProgressBar that shows the progress made by each thread as the Mandelbrot set is drawn onto the CartesianCanvas.
 * \details
 * - A class containing all of the data and methods to draw a Mandelbrot set has been made.
 * - When you create a Mandelbrot object:
 *    - The number of threads to use is predetermined (passed as the \b threads parameter) and stored in: \b myThreads.
 *    - The number of iterations to check is predetermined (passed as the \b depth parameter) and stored in: \b myDepth.
 *    - The internal timer of the Canvas is set up to go off every ( \b FRAME / 2 ) seconds.
 *    - A flag telling us to redraw is set to true.
 *    .
 * - When you bind the buttons:
 *    - The spacebar on-press event is set to tell the Canvas to clear and re-render.
 *    - The left mouse on-press event is set to grab the mouse's current coordinates.
 *    - The left mouse on-release event is set to grab the mouse's current coordinates, and tell the Canvas to zoom into the
 *      bounding rectangle between the current coordinates and those from the left mouse's on press event.
 *    - The right mouse on-press event is set to grab the mouse's current coordinates, and tell the Canvas to zoom out
 *      from that area.
 *    - The mouse's scroll wheel is set to tell the Canvas to zoom in / out by a predetermined amount at the mouse's
 *      current coordinates.
 *    .
 * - When you actually draw the Mandelbrot object onto the CartesianCanvas:
 *   - Create the Canvas that will draw the ProgressBar and the ProgressBar object.
 *   - While the myRedraw flag is set:
 *      - Set the myRedraw flag to false.
 *      - Reset the internal timer to 0.
 *      - Fork off the predetermined number of parallel threads using OMP.
 *      - Store the actual number of threads spawned in: \b nthreads.
 *      - Assign a color to each thread.
 *      - Figure the cartesian size of the area each thread is to calculate and store it in: \b blocksize.
 *      - Figure out the actual number of rows each thread is to calculate and store it in: \b blockheight.
 *      - Clear the Canvas that holds the ProgressBar.
 *      - Update the ProgressBar.
 *      - Draw the ProgressBar onto the Canvas.
 *      - For 0 to \b blockheight and as long as we aren't trying to render off of the screen:
 *        - Update the ProgressBar.
 *        - Redraw the ProgressBar with labels for the ID of each thread above each segment of the ProgressBar.
 *        - Make an inner loop which determines whether to color the pixels black or a different color based off of whether they escaped or not.
 *          - (Basic Mandelbrot calculations; see http://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings ).
 *          - Break if the Canvas is to redraw.
 *        .
 *        - Handle any IO events (OS X version only).
 *        - Break if the Canvas is to redraw.
 *      .
 *      - Output the time it took to compute the screen.
 *      - While the Canvas has not been closed and it isn't time to redraw yet:
 *        - Sleep the thread for one frame until the Canvas is closed by the user or told to redraw.
 *      .
 *   .
 * - If the ProgressBar Canvas is still open, close it up.
 * .
 * \param can Reference to the CartesianCanvas being drawn to.
 * \param threads Reference to the number of threads passed via command-line arguments.
 * \param depth The number of iterations to go to in order to draw the Mandelbrot set.
 */
void mandelbrotFunction(CartesianCanvas& can, unsigned &threads, unsigned depth) {
    Mandelbrot m1(threads,depth);  //Make the object
    m1.bindings(can); //Bind the buttons
    m1.draw(can);  //Draw the Mandelbrot object onto the Canvas
}

//Takes command line arguments for the width and height of the screen
//as well as the number of threads to use and the number of iterations to draw the Mandelbrot set
int main(int argc, char* argv[]) {
    int w = (argc > 1) ? atoi(argv[1]) : 1.2*Canvas::getDisplayHeight();
    int h = (argc > 2) ? atoi(argv[2]) : 0.75*w;
    if (w <= 0 || h <= 0) {     //Checked the passed width and height if they are valid
      w = 1200;
      h = 900;                  //If not, set the width and height to a default value
    }
    Cart c5(-1, -1, w, h, -2, -1.125, 1, 1.125, "Mandelbrot", FRAME / 2);
    unsigned t = (argc > 3) ? atoi(argv[3]) : omp_get_num_procs();    //Get the number of threads to use
    if (t == 0)
      t = omp_get_num_procs();
    unsigned d = (argc > 4) ? atoi(argv[4]) : MAX_COLOR;
    c5.setBackgroundColor(GRAY);
    c5.start();

    mandelbrotFunction(c5, t, d);   //And pass it as an argument

    c5.wait();
}
