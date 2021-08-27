#include <cstdlib>
#include <utility>

namespace pp {

template <typename ValueType, typename ReferenceCountType = int>
class SharedPointer {
public:
    template <typename ... Args>
    explicit SharedPointer(Args ... args) {
        this->_pointer = (ValueType *)((unsigned long)::malloc(sizeof(ValueType) + sizeof(ReferenceCountType)) + sizeof(ReferenceCountType));
        ::new (this->_pointer) ValueType(std::forward<Args>(args)...);

        *(this->getReferenceCountPoint()) = 1;
    }

    SharedPointer(const SharedPointer &other) : _pointer(other._pointer) {
        this->increaseReferenceCount();
    }

    SharedPointer &operator=(const SharedPointer &other) {
        if (this != &other) {
            SharedPointer temp = other;
            this->swap(temp);
        }
        return *this;
    }

    ReferenceCountType getReferenceCount() {
        return *(this->getReferenceCountPoint());
    }

    ValueType *operator->() {
        return this->_pointer;
    }

    ValueType &operator*() {
        return *this->_pointer;
    }

    ~SharedPointer() {
        this->release();
    }

private:
    inline ReferenceCountType *getReferenceCountPoint() {
        return (ReferenceCountType *)(this->_pointer) - 1;
    }

    inline void decreaseReferenceCount() {
        --(*this->getReferenceCountPoint());
    }

    inline void increaseReferenceCount() {
        ++(*this->getReferenceCountPoint());
    }

    inline void release() {
        this->decreaseReferenceCount();

        if (this->getReferenceCount() == 0) {
            this->_pointer->~ValueType();
            ::free(this->getReferenceCountPoint());
        }
    }

    inline void swap(SharedPointer &other) noexcept {
        std::swap(this->_pointer, other._pointer);
    }

private:
    ValueType *_pointer;
};

}  // namespace pp
