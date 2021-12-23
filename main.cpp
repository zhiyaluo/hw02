// for memory leak detection
#ifdef WIN32
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif
#endif

#include "List.h"

#include <list>

template<class E>
void print(parallel101::List<E> const& lst) {  // 有什么值得改进的？
    // print并不修改lst，也不需要复制lst，所以需要添加const& 修饰符
    printf("[");
    //for (auto curr = lst.front(); curr; curr = curr->next.get()) {
    //    printf(" %d", curr->value);
    //}
    // 在实现了迭代器之后，可以使用for_each来遍历
    std::for_each(lst.begin(), lst.end(), [](auto& n) { printf(" %d", n); });
    printf(" ]\n");
}

void runcase()
{
    using namespace parallel101;
    using List = List<int>;

    List a;
    List z;
    a.swap(z);

    a.push_front(7);
    a.push_front(5);
    a.push_front(8);
    a.push_front(2);
    a.push_front(9);
    a.push_front(4);
    a.push_front(1);

    print(a);   // [ 1 4 9 2 8 5 7 ]


    //a.at(2)->erase();
    a.erase(a.begin() + 2);

    print(a);   // [ 1 4 2 8 5 7 ]

    List b = a;

    //a.at(3)->erase();
    a.erase(a.begin() + 3);

    print(a);   // [ 1 4 2 5 7 ]
    print(b);   // [ 1 4 2 8 5 7 ]

    b = {};
    a = {};

    /// more tests
    auto s = { 3, 1, 4, 1, 5 };
    a.assign(s.begin(), s.end());
    print(a);   // [ 3 1 4 1 5 ]

    std::list<int> li;
    a.assign(li.begin(), li.end());
    li.insert(li.begin(), 1);

    b.swap(a);
    b.pop_front();
    print(b);   // [ 1 4 1 5 ]

    a = { 1 };
    print(a);   // [ 1 ]

    a.insert_before(a.begin(), b.begin(), b.end());
    a.insert_before(a.begin(), 10);
    print(a);   // [ 10 1 4 1 5 1 ]

    a.insert_after(a.begin(), b.begin(), b.end());
    a.insert_after(a.begin(), 11);
    print(a);   // [ 10 11 1 4 1 5 1 4 1 5 1 ]

    a.erase(a.begin());
    print(a);   // [ 11 1 4 1 5 1 4 1 5 1 ]

    a.erase(a.begin() + 2, a.end() - 2);
    print(a);   // [ 11 1 5 1 ]

    a.emplace_back(12);
    print(a);   // [ 11 1 5 1 12 ]

    a.emplace_front(13);
    print(a);   // [ 13 11 1 5 1 12 ]

    a.emplace_before(a.begin(), 0);
    print(a);   // [ 0 13 11 1 5 1 12 ]

    a.emplace_after(a.begin(), 8);
    print(a);   // [ 0 8 13 11 1 5 1 12 ]

    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    a.pop_back();
    print(a);   // [ ]

    a.insert_before(a.begin(), 1);
    a.insert_before(a.begin(), 2);
    a.insert_before(a.begin(), 3);
    print(a);   // [ 3 2 1 ]

    a.clear();
    print(a);   // [ ]

    a.insert_before(a.end(), 1);
    a.insert_before(a.end(), 2);
    a.insert_before(a.end(), 3);
    print(a);   // [ 1 2 3 ]

    std::initializer_list<int> il = {};
    List c(il);
    print(c);   // [ ]

    a.swap(c);
    print(c);   // [ 1 2 3 ]

    a.insert_after(a.begin(), 1);
    a.insert_after(a.begin(), 2);
    a.insert_after(a.begin(), 3);
    print(a);   // [ 1 3 2 ]

    a.clear();
    a.insert_after(a.end(), 1);
    a.insert_after(a.end(), 2);
    a.insert_after(a.end(), 3);
    print(a);   // [ 1 2 3 ]

    b.clear();
    b.insert_after(b.begin(), a.begin(), a.end());
    print(b);   // [ 1 2 3 ]

    a.clear();
    b.clear();

    auto ss = { 5, 6, 7, 8 };
    auto sf = a.insert_before(a.begin(), ss.begin(), ss.end());
    print(a);   // [ 5 6 7 8 ]

    printf("%d\n", *sf); // 5
    printf("%d\n", *(sf + 1)); // 6
    printf("%d\n", *(sf + 2)); // 7
    printf("%d\n", *(sf + 3)); // 8

    a.clear();
    sf = a.insert_after(a.begin(), ss.begin(), ss.end());
    print(a); // [ 5 6 7 8 ]

    printf("%d\n", *sf); // 5
    printf("%d\n", *(sf + 1)); // 6
    printf("%d\n", *(sf + 2)); // 7
    printf("%d\n", *(sf + 3)); // 8

    sf = a.erase(a.begin());

    printf("%d\n", *sf); // 6

    sf = a.erase(a.end() - 1);

    printf("%d\n", *sf); // ?? end = random value
    print(a);   // [ 6 7 ]

    List d({ 1, 2, 3 });
    print(d);   // [ 1 2 3 ]
    a.assign({ 1,2,3 });
    print(a);   // [ 1 2 3 ]
    b = {};
    b.insert_after(b.begin(), { 1, 2,3 });
    print(b);   // [ 1 2 3 ]
    b.clear();
    b.insert_before(b.begin(), { 3, 2, 1 });
    print(b);   // [ 3 2 1 ]

    b.insert_before(b.begin(), std::move(9));
    print(b);   // [ 9 3 2 1 ]

    b.insert_after(b.begin(), std::move(10));
    print(b);   // [ 9 10 3 2 1 ]

    b.push_back(std::move(12));
    b.push_front(std::move(13));
    print(b);   // [ 13 9 10 3 2 1 12 ]
}

int main() {
#ifdef WIN32
#ifdef _DEBUG
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
#endif
#endif

    runcase();

#ifdef WIN32
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
#endif
    return 0;
}
