#include "Ellipsoid.h"

namespace tsgl {

 /*!
  * \brief Explicitly constructs a new Ellipsoid.
  * \details Explicit constructor for a Ellipsoid object.
  *   \param x The x coordinate of the center of the Ellipsoid.
  *   \param y The y coordinate of the center of the Ellipsoid.
  *   \param z The z coordinate of the center of the Ellipsoid.
  *   \param xRadius The Ellipsoid's radius on the x-axis.
  *   \param yRadius The Ellipsoid's radius on the y-axis.
  *   \param zRadius The Ellipsoid's radius on the z-axis.
  *   \param yaw The Ellipsoid's yaw.
  *   \param pitch The Ellipsoid's pitch.
  *   \param roll The Ellipsoid's roll.
  *   \param c A ColorGLfloat for the Ellipsoid's vertex colors.
  * \warning An invariant is held where if any radius isn't positive then an error message is given.
  * \return A new Ellipsoid with a buffer for storing the specified numbered of vertices.
  */
Ellipsoid::Ellipsoid(float x, float y, float z, GLfloat xRadius, GLfloat yRadius, GLfloat zRadius, float yaw, float pitch, float roll, ColorGLfloat c) : Object3D(x, y, z, yaw, pitch, roll)  {
    if (xRadius <= 0 || yRadius <= 0 || zRadius <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
    }
    attribMutex.lock();
    geometryType = GL_TRIANGLE_STRIP;
    verticalSections = 36;
    horizontalSections = 20;
    numberOfVertices = verticalSections*horizontalSections*2;
    vertices = new GLfloat[numberOfVertices * 3];
    colors = new GLfloat[numberOfVertices * 4];
    myXRadius = xRadius;
    myYRadius = yRadius;
    myZRadius = zRadius;
    attribMutex.unlock();
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addVertex(myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin((b*PI)/horizontalSections)), myYRadius*(cos((a*PI)/(verticalSections/2))), myZRadius*(cos((b*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c);
			addVertex(myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin(((b+1)*PI)/horizontalSections)), myYRadius*(cos((a*PI)/(verticalSections/2))), myZRadius*(cos(((b+1)*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c);
		}
	}
}

 /*!
  * \brief Explicitly constructs a new Ellipsoid.
  * \details Explicit constructor for a Ellipsoid object.
  *   \param x The x coordinate of the center of the Ellipsoid.
  *   \param y The y coordinate of the center of the Ellipsoid.
  *   \param z The z coordinate of the center of the Ellipsoid.
  *   \param xRadius The Ellipsoid's radius on the x-axis.
  *   \param yRadius The Ellipsoid's radius on the y-axis.
  *   \param zRadius The Ellipsoid's radius on the z-axis.
  *   \param yaw The Ellipsoid's yaw.
  *   \param pitch The Ellipsoid's pitch.
  *   \param roll The Ellipsoid's roll.
  *   \param c An array of ColorGLfloats for the Ellipsoid's vertex colors.
  * \warning An invariant is held where if any radius isn't positive then an error message is given.
  * \return A new Ellipsoid with a buffer for storing the specified numbered of vertices.
  */
Ellipsoid::Ellipsoid(float x, float y, float z, GLfloat xRadius, GLfloat yRadius, GLfloat zRadius, float yaw, float pitch, float roll, ColorGLfloat c[]) : Object3D(x, y, z, yaw, pitch, roll)  {
    if (xRadius <= 0 || yRadius <= 0 || zRadius <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
    }
    attribMutex.lock();
    geometryType = GL_TRIANGLE_STRIP;
    verticalSections = 36;
    horizontalSections = 20;
    numberOfVertices = verticalSections*horizontalSections*2;
    vertices = new GLfloat[numberOfVertices * 3];
    colors = new GLfloat[numberOfVertices * 4];
    myXRadius = xRadius;
    myYRadius = yRadius;
    myZRadius = zRadius;
    attribMutex.unlock();
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addVertex(myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin((b*PI)/horizontalSections)), myYRadius*(cos((a*PI)/(verticalSections/2))), myZRadius*(cos((b*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c[b]);
			addVertex(myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin(((b+1)*PI)/horizontalSections)), myYRadius*(cos((a*PI)/(verticalSections/2))), myZRadius*(cos(((b+1)*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c[b]);
		}
	}
}

/**
 * \brief Sets the Ellipsoid to a new color.
 * \param c The new ColorGLfloat.
 */
void Ellipsoid::setColor(ColorGLfloat c) {
    // attribMutex.lock();
    // for(int i = 0; i < numberOfVertices; i++) {
    //     colors[i*6 + 2] = c.R;
    //     colors[i*6 + 3] = c.G;
    //     colors[i*6 + 4] = c.B;
    //     colors[i*6 + 5] = c.A;
    // }
    // attribMutex.unlock();
}

/**
 * \brief Sets the Ellipsoid to an array of new colors.
 * \param c An array of new ColorGLfloats.
 */
void Ellipsoid::setColor(ColorGLfloat c[]) {
    // attribMutex.lock();
    // for(int i = 0; i < numberOfVertices; i++) {
    //     colors[i*4] = c[i].R;
    //     colors[i*4 + 1] = c[i].G;
    //     colors[i*4 + 2] = c[i].B;
    //     colors[i*4 + 3] = c[i].A;
    // }
    // attribMutex.unlock();
}

/**
 * \brief Gets an array of the Ellipsoid's fill vertex colors.
 * \return c An array of ColorGLfloats.
 * \warning This method allocates memory. The caller is responsible for deallocating it.
 */
// ColorGLfloat* Ellipsoid::getColor() {
//   ColorGLfloat * c = new ColorGLfloat[numberOfVertices * 4];
//     for(int i = 0; i < numberOfVertices; i++) {
//         c[i] = ColorGLfloat(colors[i*6 + 2], colors[i*6 + 3], colors[i*6 + 4], colors[i*6 + 5]);
//     }
//     return c;
// }

/**
 * \brief Mutates the Ellipsoid's x-axis radius.
 * \param radius The new x-axis radius of the Ellipsoid.
 */
void Ellipsoid::setXRadius(GLfloat radiusX) {
    if (radiusX <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    GLfloat ratio = radiusX / myXRadius;
    myXRadius = radiusX;
    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i*3] *= ratio;
    }
    attribMutex.unlock();
}

/**
 * \brief Mutates the Ellipsoid's x-axis radius by the parameter amount.
 * \param delta The amount by which to change the x-axis radius of the Ellipsoid.
 */
void Ellipsoid::changeXRadiusBy(GLfloat delta) {
    if (myXRadius + delta <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    myXRadius += delta;
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
            vertices[(b*verticalSections + a) * 2 * 3] = myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin((b*PI)/horizontalSections));
            vertices[(b*verticalSections + a) * 2 * 3 + 3] = myXRadius*(sin((a*PI)/(verticalSections/2)))*(sin(((b+1)*PI)/horizontalSections));
		}
	}
    attribMutex.unlock();
}

/**
 * \brief Mutates the Ellipsoid's y-axis radius.
 * \param radius The new y-axis radius of the Ellipsoid.
 */
void Ellipsoid::setYRadius(GLfloat radiusY) {
    if (radiusY <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    GLfloat ratio = radiusY / myYRadius;
    myYRadius = radiusY;
    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i*3 + 1] *= ratio;
    }
    attribMutex.unlock();
}

/**
 * \brief Mutates the Ellipsoid's y-axis radius by the parameter amount.
 * \param delta The amount by which to change the y-axis radius of the Ellipsoid.
 */
void Ellipsoid::changeYRadiusBy(GLfloat delta) {
    if (myYRadius + delta <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    myYRadius += delta;
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
            vertices[(b*verticalSections + a) * 2 * 3 + 1] = myYRadius*(cos((a*PI)/(verticalSections/2)));
            vertices[(b*verticalSections + a) * 2 * 3 + 4] = myYRadius*(cos((a*PI)/(verticalSections/2)));
		}
	}
    attribMutex.unlock();
}

/**
 * \brief Mutates the Ellipsoid's z-axis radius.
 * \param radius The new z-axis radius of the Ellipsoid.
 */
void Ellipsoid::setZRadius(GLfloat radiusZ) {
    if (radiusZ <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    GLfloat ratio = radiusZ / myZRadius;
    myZRadius = radiusZ;
    for (int i = 0; i < numberOfVertices; i++) {
        vertices[i*3 + 2] *= ratio;
    }
    attribMutex.unlock();
}

/**
 * \brief Mutates the Ellipsoid's z-axis radius by the parameter amount.
 * \param delta The amount by which to change the z-axis radius of the Ellipsoid.
 */
void Ellipsoid::changeZRadiusBy(GLfloat delta) {
    if (myZRadius + delta <= 0) {
        TsglDebug("Cannot have an Ellipsoid with any radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    myZRadius += delta;
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
            vertices[(b*verticalSections + a) * 2 * 3 + 2] = myZRadius*(cos((b*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2)));
            vertices[(b*verticalSections + a) * 2 * 3 + 5] = myZRadius*(cos(((b+1)*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2)));
		}
	}
    attribMutex.unlock();
}

/*!
 * \brief Destructor for the Ellipsoid.
 */
Ellipsoid::~Ellipsoid() { }

}