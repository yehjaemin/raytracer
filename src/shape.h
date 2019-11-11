class Shape {
public:
    Shape(const Transform *ObjectToWorld, const Transform *WorldToObject);
    virtual ~Shape();
    virtual Bounds3f ObjectBound() const = 0;
    virtual Bounds3f WorldBound() const;

    const Transform *ObjectToWorld, *WorldToObject;
};
