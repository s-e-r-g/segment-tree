#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <cxxabi.h>

// Implementation

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



// **** TESTS ******

std::string demangle(const char* name)
{
    char buffer[1024];
    size_t size=1024;
    int status;
    return abi::__cxa_demangle(name, buffer, &size, &status);
}

template <typename Operation, typename ElementType>
class TestSegmentTree
{
public:
    TestSegmentTree(const std::vector<ElementType>& arr) : data(arr), tree(data){} 

public:
    std::vector<ElementType> data;
    SegmentTree<Operation, ElementType> tree;

public:
    void check_query(int from, int to)
    {
        auto result = tree.query(from, to);
        auto expected = std::accumulate(data.begin() + from + 1, data.begin() + to + 1, data[from], Operation());
        if (result != expected)
            std::cout << "FAILURE: [" << demangle(typeid(*this).name()) << "] Query(" << from << "," << to << "): " << result << " (" << expected << " is expected)" << std::endl;
    }

};

int main()
{
    TestSegmentTree<std::multiplies<>, int> test1({1,3,5});
    test1.check_query(0, 2);
    test1.check_query(0, 0);
    test1.check_query(1, 1);
    test1.check_query(2, 2);
    test1.check_query(1, 2);
    test1.check_query(0, 1);

    TestSegmentTree<std::plus<>, int> test2({1,3,5});
    test2.check_query(0, 2);
    test2.check_query(0, 0);
    test2.check_query(1, 1);
    test2.check_query(2, 2);
    test2.check_query(1, 2);
    test2.check_query(0, 1);

    // Test plus carefully, with different sizes from 1 to 100
    for (int i = 1; i < 100; ++i)
    {
        std::vector<int> data;
        for (int x = 1; x <= i; ++x)
        {
            data.push_back(x);
        }
        TestSegmentTree<std::plus<>, int> test(data);
        for (int l = 0; l < data.size(); ++l)
            for (int r = l; r < data.size(); ++r)
                test.check_query(l, r);

        for (int change = 0; change < data.size(); ++change)
        {
            test.tree.update(change, change + 100);
            for (int l = 0; l < data.size(); ++l)
                for (int r = l; r < data.size(); ++r)
                    test.check_query(l, r);
        }
    }
}
