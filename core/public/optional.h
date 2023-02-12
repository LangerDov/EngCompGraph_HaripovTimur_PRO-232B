#pragma once
template<typename T>
class Optional
{
public:
    Optional() { value = { 0 }; bHasVal = false; }
    ~Optional() {}

    void operator=(T val) { value = val; bHasVal = true; }
    void Erase() { memset(&value, 0, sizeof(T)); bHasVal = false; }

    T GetValue() { return value; }
    bool HasValue() { return bHasVal; }

private:
    bool bHasVal;
    T value;
};