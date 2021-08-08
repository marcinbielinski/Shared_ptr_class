#include <iostream>
#include <vector>

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T* ptr)
    {
        _ptr = ptr;
        _count = new int(1);
    }
    SharedPtr(const SharedPtr& object)
    {
    }
    SharedPtr& operator=(const SharedPtr<T>& object)
    {
        if (_count != nullptr)
        {
            subtractCount();
            if (*_count == 0)
            {
                delete _ptr;
            }
        }
        _ptr = object.ptr;
        _count = object.count;
        addCount();
        return *this;
    }
    SharedPtr(SharedPtr&& dying_object) noexcept
    {
        this->_ptr = dying_object._ptr;
        dying_object._ptr = nullptr;
    }

    int getCount()
    {
        if (_count != nullptr)
        {
            return *_count;
        }
        else
        {
            return 0;
        }
    }
    void subtractCount()
    {
        (*_count)--;
    }
    void addCount()
    {
        (*_count)++;
    }
    void reset()
    {
        if (_count != nullptr)
        {
            subtractCount();
            if (*_count == 0)
            {
                delete _ptr;
                delete _count;
            }
            _ptr = nullptr;
            _count = nullptr;
        }
    }

    T* operator->()
    {
        return this->_ptr;
    }
    T& operator*()
    {
        return *(this->_ptr);
    }

    ~SharedPtr()
    {
        if (_count != nullptr)
        {
            subtractCount();
            if (*_count == 0)
            {
                delete _ptr;
                delete _count;
            }
        }
    }
private:
    T* _ptr = nullptr;
    int *_count{nullptr};
};

class Box
{
public:
    int _val;

    explicit Box(int val) : _val(val)
    {
        std::cout << "Constructing the box" << std::endl;
    }

    ~Box()
    {
        std::cout << "Destructing the box" << std::endl;
    }
};
SharedPtr<Box> makeMe()
{
    SharedPtr<Box> box(new Box(5));
    return box;
}

int main() {

    std::vector<SharedPtr<Box>> my_vec;

    SharedPtr<Box> box1 = makeMe();
    SharedPtr<Box> box2 = box1;
    SharedPtr<Box> box3 = box1;

//    my_vec.emplace_back(box1);
//    my_vec.emplace_back(box2);
//    my_vec.emplace_back(box3);
//

    std::cout << box1.getCount() << " " << box2.getCount() << " " << box3.getCount();
    std::cout << std::endl;

    box3.reset();

    std::cout << box1.getCount() << " " << box2.getCount() << " " << box3.getCount();
    std::cout << std::endl;

    std::cout << box1->_val;


    return 0;
}