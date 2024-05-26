#include <iostream>
#include <vector>

class SegmentTree
{
public:
    SegmentTree(std::vector<int>& data);
    void update(int index, int value);
    int query(int left, int right) const;

private:
    int _size;
    std::vector<int> _tree;
    std::vector<int>& _data;

    
private:
    int get(int index) const;
    void set(int index, int value);
};


SegmentTree::SegmentTree(std::vector<int>& data) 
    : _size(data.size())
    , _tree(data.empty() ? 0 : data.size() - 1)
    , _data(data)
{
    for (int i = _size - 1; i > 0; --i)
    {
        set(i, get(i * 2) + get(i * 2 + 1));
    }
}


int SegmentTree::get(int index) const
{
    return  (index < _size) ? _tree[index - 1] : _data[index - _size];
}

void SegmentTree::set(int index, int value)
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


int SegmentTree::query(int left, int right) const
{
    left += _size;
    right += _size;
    int sum = 0;
    while (left <= right)
    {
        if ((left & 1) == 1)
        {
            sum += get(left++);
        }
        if ((right & 1) == 0)
        {
            sum += get(right--);
        }
        left /= 2;
        right /= 2;
    }
    return sum;
}

void SegmentTree::update(int index, int value)
{
    index += _size;
    set(index, value);
    while (index > 1)
    {
        index /= 2;
        set(index, get(2 * index) + get(2 * index + 1));
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
