#include <iostream>
#include <vector>

template <typename Operation, typename ElementType>
class SegmentTree
{
public:
    SegmentTree(std::vector<ElementType>& data)
        : _size(data.size())
        , _tree(data.empty() ? 0 : data.size() - 1)
        , _data(data)
    {
        for (int index = _size - 1; index > 0; --index)
        {
            set(index, Operation()(get(index * 2), get(index * 2 + 1)));
        }
    }

    void update(int index, ElementType value)
    {
        index += _size;
        set(index, value);
        while (index > 1)
        {
            index /= 2;
            set(index, Operation()(get(index * 2), get(index * 2 + 1)));
        }
    }

    ElementType query(int left, int right) const
    {
        left += _size;
        right += _size;
    
        std::optional<ElementType> result;

        while (left <= right)
        {
            if ((left & 1) == 1)
            {
                result = result ? Operation()(*result, get(left)) : get(left);
                ++left;
            }
            if ((right & 1) == 0)
            {
                result = result ? Operation()(*result, get(right)) : get(right);
                --right;
            }
            left /= 2;
            right /= 2;
        }
        return *result;
    }

private:
    int _size;
    std::vector<ElementType> _tree;
    std::vector<ElementType>& _data;

private:
    ElementType get(int index) const
    {
        return (index < _size) ? _tree[index - 1] : _data[index - _size];
    }

    void set(int index, ElementType value)
    {
        if (index < _size)
        {
            _tree[index - 1] = value;
        }
        else
        {
            _data[index - _size] = value;
        }
    }
};

int main()
{
    std::vector<int> numbers = {1, 3, 5};
    SegmentTree<std::plus<>, int> segTree(numbers);

    std::cout << "Sum(0,2): " << segTree.query(0, 2) << std::endl;
    std::cout << "Update(1,2)" << std::endl;
    segTree.update(1, 2);
    std::cout << "Sum(0,2): " << segTree.query(0, 2) << std::endl;
}
