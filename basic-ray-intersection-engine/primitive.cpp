#include "primitive.h"

Primitive::Primitive()
{

}

Primitive::Primitive(QString qname, std::unique_ptr<Shape> shapePtr, std::unique_ptr<Light> lightPtr, std::unique_ptr<Material> materialPtr)
    : name(qname)
{
    shape = std::move(shapePtr);
}

bool Primitive::getIntersection(const Ray& ray, Intersection *intersect) const {
    if (nullptr == intersect) {
        std::cout << "Primitive getIntersection, intersect == nullptr" << std::endl;
        return false;
    }

    if (shape->getIntersection(ray, intersect)) {
//        intersect->objectHit = this;
        return true;
    }

    return false;
}
