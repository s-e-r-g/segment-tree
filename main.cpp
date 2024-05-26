#include <iostream>
#include <vector>

class SegmentTree
{
public:
    SegmentTree(const std::vector<int> &data);
    void update(int index, int value);
    int query(int left, int right) const;

private:
    int _size;
    std::vector<int> _tree;
};

SegmentTree::SegmentTree(const std::vector<int> &data) 
    : _size(data.size())
    , _tree(2 * data.size())

{
    for (int i = 0; i < _size; ++i)
    {
        _tree[_size + i] = data[i];
    }

    for (int i = _size - 1; i > 0; --i)
    {
        _tree[i] = _tree[2 * i] + _tree[2 * i + 1];
    }
}

int SegmentTree::query(int left, int right) const
{
    left += _size;
    right += _size;
    int sum = 0;
    while (left <= right)
    {
        if ((left & 1) == 1)
        {
            sum += _tree[left++];
        }
        if ((right & 1) == 0)
        {
            sum += _tree[right--];
        }
        left /= 2;
        right /= 2;
    }
    return sum;
}

void SegmentTree::update(int index, int value)
{
    index += _size;
    _tree[index] = value;
    while (index > 1)
    {
        index /= 2;
        _tree[index] = _tree[2 * index] + _tree[2 * index + 1];
    }
}

int main()
{
    std::vector<int> numbers = {1, 3, 5};
    SegmentTree segTree(numbers);

    std::cout << "Sum(0,2): " << segTree.query(0, 2) << std::endl;
    std::cout << "Update(1,2)" << std::endl;
    segTree.update(1, 2);
    std::cout << "Sum(0,2): " << segTree.query(0, 2) << std::endl;
}
