// Radix Sort to sort Ints
// assuming int size to be 32
// and binary base for sorting
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>

using namespace std;

inline int getDigit(int number, int pos)
{
       if(pos == 31)
        return -1*((number^(1<<pos))>>pos);
       else
        return (number&(1<<pos))>>pos;
}
void countSort(vector<int> &input, int digitPos)
{
    vector<int> output;
    vector<int> pos(4,0);
    int digit, first, idx;
    output.resize(input.size());
    for(int i = 0;i<input.size();i++)
    {
        digit = getDigit(input[i],digitPos);
        pos[digit]++;
    }
    
    for(int i = 0;i<pos.size();i++)
    {
        if(pos[i]!=0)
        {
            first = pos[i];
            pos[i] = 0;
            idx = i;
            break;
        }
    }

int temp;
    for(int i = idx+1; i<pos.size();i++)
    {
        temp = pos[i];
        pos[i] = first + pos[i-1];
        first = temp;
    }

    for(int i = 0;i<output.size(); i++)
    {
        digit = getDigit(input[i],digitPos);
        output[pos[digit]] = input[i];
        pos[digit]++;
    }
    input = output;
}

int main()
{
    vector<int>nums{0,19,-255,5,-2};
    cout<<"Hello"<<endl;
    for(int i = 0;i<32;i++)
        countSort(nums,i);
    for(int i = 0; i<nums.size();i++)
        cout<<nums[i]<<" ";
    cout<<endl;
}
