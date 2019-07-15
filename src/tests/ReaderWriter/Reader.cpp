#include "Reader.h"

/**
 * \brief Default-constructor for the Reader class.
 * \return: The constructed Reader object.
 */
Reader::Reader() : RWThread() { }

/**
 * \brief Explicit-constructor for the Reader class.
 * \param: sharedData, a reference to the RWDatabase object that is shared between the Reader and Writer.
 * \param: id, an unsigned long that will be passed to the Thread() constructor that will act as the id for the Thread object.
 * \param: can, a handle to the Canvas that will be drawn on.
 * \return: The constructed Reader object.
 */
Reader::Reader(RWDatabase<Rectangle*> & sharedDatabase, Lock& lock, unsigned long id, Canvas & can) : RWThread(sharedDatabase, lock, id, can) {
	myX = can.getWindowWidth()-50;
	myCircle->setCenter(myX, myY);
	myCountLabel->setBottomLeftCorner(myX + countLabelOffset, myY + 8);
}

/**
 * \brief Draws and removes Arrow from Canvas
 * \details Helps the read() method
 * \details Includes a half second pause
 */
void Reader::drawArrow(int x, int y) {
	Arrow arrow(myCircle->getX()-20, myY, x, y, BLACK, false);
	arrow.setLayer(5);
	myCan->add(&arrow);
	myCan->sleepFor(0.5);
	while( paused ) {}
	myCan->remove(&arrow);
}

//TODO: comment
void Reader::lock() {
	myCircle->setCenter(myX-75, myY); //Move towards data
	myCountLabel->setBottomLeftCorner(myX-75+countLabelOffset, myY + 8);
	monitor->readLock();  //Lock data for reading
	myCan->sleepFor(RWThread::access_wait);
	while( paused ) {}
	myCircle->setCenter(myX-127, myY); //Move inside data
	myCountLabel->setBottomLeftCorner(myX-127+countLabelOffset, myY + 8);
}

//TODO: comment
void Reader::act() {
	//Read
	Rectangle * rec = data->read(rand()%data->getItemCount()); //Get the color
	ColorFloat* fillColor = rec->getFillColor();
	myCircle->setColor( fillColor[0] );
	myCountLabel->setColor( fillColor[0].getContrast() );
	delete[] fillColor;

	//Draw and erase the arrow
	drawArrow(rec->getX(), rec->getY());
}

//TODO: comment
void Reader::unlock() {
	//Release lock
	count++; myCountLabel->setText( to_wstring(count) ); //Finished another read
	if( count == 10  ) {
		countLabelOffset = -12;
	} else if( count == 100 ) {
		myCountLabel->setFontSize(22);
		countLabelOffset = -18;
	}
	while( paused ) {}
	myCircle->setCenter(myX, myY); 	//Return to home location
	myCountLabel->setBottomLeftCorner(myX + countLabelOffset, myY + 8);
	monitor->readUnlock(); 	//Unlock the data
}
