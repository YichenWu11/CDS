#include <type_traits>
#include <iostream>

#include <CDS/Utility/TypeList.h>

void test_type_list()
{
    using TestList = TypeList<char, int, float>;

    using TargetType = At<TestList, 1>::Result;

    TargetType f1;

    if (typeid(f1) == typeid(int))  printf("index 1 of TestList is int\n");

    int indexOfFloat = IndexOf<TestList, float>::Result;

    printf("index of float in TestList is %d\n", indexOfFloat);

    using TestListAddDouble = Append<TestList, double>::Result;


    int beforeAddDoubleSize = Size<TestList>::Result;
    int afterAddDoubleSize =  Size<TestListAddDouble>::Result;

    printf("before add double, size of TestList is %d\n", beforeAddDoubleSize);
    printf("after add double, size of TestList is %d\n", afterAddDoubleSize);

    using TestListAddDoubleAddDouble = Append<TestListAddDouble, double>::Result;
    using TestListDoubleDoubleDupRemoval = NoDuplicate<TestListAddDoubleAddDouble>::Result;

    int beforeDupRemovalSize = Size<TestListAddDoubleAddDouble>::Result;
    int afterDupRemovalSize = Size<TestListDoubleDoubleDupRemoval>::Result;

    printf("before duplicate removal, size of TestListAddDouble is %d\n", beforeDupRemovalSize);
    printf("before duplicate removal, size of TestListAddDouble is %d\n", afterDupRemovalSize);

    using TestListReplaceCharWithDouble = Replace<TestList, char, double>::Result;

    using afterReplaceTargetType = At<TestListReplaceCharWithDouble, 0>::Result;

    afterReplaceTargetType d1;

    if (typeid(d1) == typeid(double))  printf("now index 0 of TestList is double\n");
}
