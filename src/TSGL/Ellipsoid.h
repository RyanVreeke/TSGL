/*
 * Ellipsoid.h extends Object3D and provides a class for drawing a ellipsoid.
 */

#ifndef ELLIPSOID_H_
#define ELLIPSOID_H_

#include "Object3D.h"       // For extending our Object3D object
#include "TsglAssert.h"  // For unit testing purposes

namespace tsgl {

/*! \class Ellipsoid
 *  \brief Draw an arbitrary Ellipsoid with colored vertices.
 *  \details Ellipsoid is a class for holding vertex data for an Ellipsoid.
 */
class Ellipsoid : public Object3D {
protected:
    GLfloat myXRadius, myYRadius, myZRadius;
    int horizontalSections, verticalSections;
public:
    Ellipsoid(float x, float y, float z, GLfloat xRadius, GLfloat yRadius, GLfloat zRadius, float yaw, float pitch, float roll, ColorGLfloat c);

    Ellipsoid(float x, float y, float z, GLfloat xRadius, GLfloat yRadius, GLfloat zRadius, float yaw, float pitch, float roll, ColorGLfloat c[]);

    virtual ~Ellipsoid();

    virtual void setColor(ColorGLfloat c);

    virtual void setColor(ColorGLfloat c[]);

    virtual void setXRadius(GLfloat radiusX);

    virtual void changeXRadiusBy(GLfloat delta);

    virtual void setYRadius(GLfloat radiusY);

    virtual void changeYRadiusBy(GLfloat delta);

    virtual void setZRadius(GLfloat radiusZ);

    virtual void changeZRadiusBy(GLfloat delta);

    virtual GLfloat getXRadius() { return myXRadius; }

    virtual GLfloat getYRadius() { return myYRadius; }

    virtual GLfloat getZRadius() { return myZRadius; }

    // virtual ColorGLfloat* getColor();
};

}

#endif /* ELLIPSOID_H_ */