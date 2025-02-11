#include "Test.hpp"

void
__cdecl
TestFunc(
    _In_ std::uint64_t Num
)
{
    if (Num < 50)
    {
        throw(EXCEPTION_INVALID_ARG);
    }

    printf("Valid number: %llu\n", Num);
}

int
__cdecl
main(
    [[maybe_unused]] _In_ int ArgC,
    [[maybe_unused]] _In_ char* ArgV[]
)
{
    try // Will throw an exception
    {
        TestFunc(25);
    }
    catch (MyException)
    {
        printf("Exception caught: %llu = %s\n", MyException.code(), MyException.what());
    }

    try // Won't throw an exception
    {
        TestFunc(100);
    }
    catch (MyException)
    {
        printf("Exception caught: %llu = %s\n", MyException.code(), MyException.what());
    }

    return 0;
}