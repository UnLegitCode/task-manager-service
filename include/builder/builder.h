#ifndef BUILDER_H
#define BUILDER_H

#include <string>

template<typename T>
class Builder {
protected:
    Builder() = default;
public:
    virtual ~Builder() = default;

    virtual std::unique_ptr<T> build() = 0;
};

#endif //BUILDER_H