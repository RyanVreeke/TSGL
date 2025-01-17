#include "Sphere.h"

namespace tsgl {

 /*!
  * \brief Explicitly constructs a new Sphere.
  * \details Explicit constructor for a Sphere object.
  *   \param x The x coordinate of the center of the Sphere.
  *   \param y The y coordinate of the center of the Sphere.
  *   \param z The z coordinate of the center of the Sphere.
  *   \param radius The Sphere's radius
  *   \param yaw The Sphere's yaw.
  *   \param pitch The Sphere's pitch.
  *   \param roll The Sphere's roll.
  *   \param c A ColorFloat for the Sphere's vertex colors.
  * \warning An invariant is held where if radius isn't positive then an error message is given.
  * \return A new Sphere with a buffer for storing the specified numbered of vertices.
  */
Sphere::Sphere(float x, float y, float z, GLfloat radius, float yaw, float pitch, float roll, ColorFloat c)  : Shape(x, y, z, yaw, pitch, roll)  {
    // FIXME alpha param works kinda weirdly
    if (radius <= 0) {
        TsglDebug("Cannot have a Sphere with radius less than or equal to 0.");
    }
    attribMutex.lock();
    myRadius = radius;
    myXScale = radius;
    myYScale = radius;
    myZScale = radius;
    verticalSections = 36;
    horizontalSections = 20;
    geometryType = GL_TRIANGLE_STRIP;
    numberOfVertices = verticalSections*horizontalSections*2 + 1;
    vertices = new GLfloat[numberOfVertices * 7];
    outlineGeometryType = GL_LINES;
    numberOfOutlineVertices = verticalSections*horizontalSections*4 + 1;
    outlineVertices = new GLfloat[numberOfOutlineVertices * 7];
    isOutlined = false;
    attribMutex.unlock();  
	for(float b=0;b<horizontalSections;b++)
	{
		for(float a=0;a<verticalSections;a++)
		{
			addVertex(sin((a*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), ColorFloat(c.R * (1 - 1 * sin(a/verticalSections * PI) / 2), c.G * (1 - 1 * sin(a/verticalSections * PI) / 2), c.B * (1 - 1 * sin(a/verticalSections * PI) / 2), 1));
			addVertex(sin((a*PI)/(verticalSections/2))*sin(((b+1)*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos(((b+1)*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), ColorFloat(c.R * (1 - 1 * sin(a/verticalSections * PI) / 2), c.G * (1 - 1 * sin(a/verticalSections * PI) / 2), c.B * (1 - 1 * sin(a/verticalSections * PI) / 2), 1));
		}
	}
    addVertex(0, 1, 0, c);

    // horizontal outline
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin(((b+1)*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos(((b+1)*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
		}
	}

    // vertical outline
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
			addOutlineVertex(sin(((a+1)*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos(((a+1)*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin(((a+1)*PI)/(verticalSections/2)), GRAY);
		}
	}
    addOutlineVertex(0, 1, 0, GRAY);
}

 /*!
  * \brief Explicitly constructs a new Sphere.
  * \details Explicit constructor for a Sphere object.
  *   \param x The x coordinate of the center of the Sphere.
  *   \param y The y coordinate of the center of the Sphere.
  *   \param z The z coordinate of the center of the Sphere.
  *   \param radius The distance from the center of the Sphere's base to each vertex of the base.
  *   \param yaw The Sphere's yaw.
  *   \param pitch The Sphere's pitch.
  *   \param roll The Sphere's roll.
  *   \param c An array of ColorFloats for the Sphere's vertex colors.
  * \warning An invariant is held where if radius isn't positive then an error message is given.
  * \return A new Sphere with a buffer for storing the specified numbered of vertices.
  */
Sphere::Sphere(float x, float y, float z, GLfloat radius, float yaw, float pitch, float roll, ColorFloat c[])  : Shape(x, y, z, yaw, pitch, roll)  {
    if (radius <= 0) {
        TsglDebug("Cannot have a Sphere with radius less than or equal to 0.");
    }
    attribMutex.lock();
    myRadius = radius;
    myXScale = radius;
    myYScale = radius;
    myZScale = radius;
    verticalSections = 36;
    horizontalSections = 20;
    geometryType = GL_TRIANGLE_STRIP;
    numberOfVertices = verticalSections*horizontalSections*2 + 1;
    vertices = new GLfloat[numberOfVertices * 7];
    outlineGeometryType = GL_LINES;
    numberOfOutlineVertices = verticalSections*horizontalSections*4 + 1;
    outlineVertices = new GLfloat[numberOfOutlineVertices * 7];
    isOutlined = false;
    attribMutex.unlock();
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addVertex((sin((a*PI)/(verticalSections/2)))*(sin((b*PI)/horizontalSections)), (cos((a*PI)/(verticalSections/2))), (cos((b*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c[b]);
			addVertex((sin((a*PI)/(verticalSections/2)))*(sin(((b+1)*PI)/horizontalSections)), (cos((a*PI)/(verticalSections/2))), (cos(((b+1)*PI)/horizontalSections))*(sin((a*PI)/(verticalSections/2))), c[b]);
		}
	}
    addVertex(0, 1, 0, c[horizontalSections]);

    // horizontal outline
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin(((b+1)*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos(((b+1)*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
		}
	}

    // vertical outline
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			addOutlineVertex(sin((a*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos((a*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin((a*PI)/(verticalSections/2)), GRAY);
			addOutlineVertex(sin(((a+1)*PI)/(verticalSections/2))*sin((b*PI)/horizontalSections), cos(((a+1)*PI)/(verticalSections/2)), cos((b*PI)/horizontalSections)*sin(((a+1)*PI)/(verticalSections/2)), GRAY);
		}
	}
    addOutlineVertex(0, 1, 0, GRAY);
}

/**
 * \brief Mutates the Sphere's radius.
 * \param radius The new radius of the Sphere.
 */
void Sphere::setRadius(float radius) {
    if (radius <= 0) {
        TsglDebug("Cannot have a Sphere with radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    myRadius = radius;
    myXScale = radius;
    myYScale = radius;
    myZScale = radius;
    attribMutex.unlock();
}

/**
 * \brief Mutates the Sphere's radius by the parameter amount.
 * \param delta The amount by which to change the radius of the Sphere.
 */
void Sphere::changeRadiusBy(float delta) {
    if (myRadius + delta <= 0) {
        TsglDebug("Cannot have a Sphere with radius less than or equal to 0.");
        return;
    }
    attribMutex.lock();
    myRadius += delta;
    myXScale += delta;
    myYScale += delta;
    myZScale += delta;
    attribMutex.unlock();
}

/**
 * \brief Sets the Sphere to a new color.
 * \param c The new ColorFloat.
 */
void Sphere::setColor(ColorFloat c) {
    attribMutex.lock();
    myAlpha = c.A;
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			vertices[(b*verticalSections + a)*2*7 + 3] = c.R * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 4] = c.G * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 5] = c.B * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 6] = c.A;
			vertices[(b*verticalSections + a)*2*7 + 10] = c.R * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 11] = c.G * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 12] = c.B * (1 - 1 * sin(((float)a)/verticalSections * PI) / 2);
            vertices[(b*verticalSections + a)*2*7 + 13] = c.A;
		}
	}
    vertices[horizontalSections*verticalSections*2*7+3] = c.R;
    vertices[horizontalSections*verticalSections*2*7+4] = c.G;
    vertices[horizontalSections*verticalSections*2*7+5] = c.B;
    vertices[horizontalSections*verticalSections*2*7+6] = c.A;
    attribMutex.unlock();
}

/**
 * \brief Sets the Sphere to an array of new colors.
 * \param c An array of new ColorFloats.
 * \details The array should have 20 ColorFloat minimum, one for each horizontal section. 
 */
void Sphere::setColor(ColorFloat c[]) {
    attribMutex.lock();
    myAlpha = 0.0;
	for(int b=0;b<horizontalSections;b++)
	{
		for(int a=0;a<verticalSections;a++)
		{
			vertices[(b*verticalSections + a)*2*7 + 3] = c[b].R;
            vertices[(b*verticalSections + a)*2*7 + 4] = c[b].G;
            vertices[(b*verticalSections + a)*2*7 + 5] = c[b].B;
            vertices[(b*verticalSections + a)*2*7 + 6] = c[b].A;
			vertices[(b*verticalSections + a)*2*7 + 10] = c[b].R;
            vertices[(b*verticalSections + a)*2*7 + 11] = c[b].G;
            vertices[(b*verticalSections + a)*2*7 + 12] = c[b].B;
            vertices[(b*verticalSections + a)*2*7 + 13] = c[b].A;
            myAlpha += c[b].A * 2;
		}
	}
    vertices[horizontalSections*verticalSections*2*7+3] = c[horizontalSections].R;
    vertices[horizontalSections*verticalSections*2*7+4] = c[horizontalSections].G;
    vertices[horizontalSections*verticalSections*2*7+5] = c[horizontalSections].B;
    vertices[horizontalSections*verticalSections*2*7+6] = c[horizontalSections].A;
    myAlpha += c[horizontalSections].A;
    myAlpha /= numberOfVertices;
    attribMutex.unlock();
}

/**
 * \brief Accessor for Sphere's colors.
 * \details Populates the reference parameter vector with a ColorFloat for each vertical section of Sphere.
 * \param colorVec A vector of ColorFloats to which the ColorFloats associated with Sphere will be pushed.
 * \note Overrides Shape::getColors().
 */
void Sphere::getColors(std::vector<ColorFloat> &colorVec) {
    attribMutex.lock();
    for(int b=0;b<horizontalSections;b++) {
        colorVec.push_back(ColorFloat(
            vertices[(b*verticalSections)*2*7 + 3],
            vertices[(b*verticalSections)*2*7 + 4],
            vertices[(b*verticalSections)*2*7 + 5],
            vertices[(b*verticalSections)*2*7 + 6])
            );
    }
    attribMutex.unlock();
}

}