//栈的压入弹出序列
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
class Solution {
public:
    bool IsPopOrder(vector<int> pushV,vector<int> popV) {
        if(pushV.size() != popV.size())
        {
            return false;
        }
        int pushi = 0, popi = 0;
        stack<int> sta;
        while(popi < popV.size())
        {
            if(sta.empty() || (sta.top() != popV[popi]))
            {
                if(pushi < pushV.size())
                {
                    sta.push(pushV[pushi]);
                    pushi++;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                std::cout << "sta:" << sta.top() << std::endl;
                sta.pop();
                popi++;
            }
        }
        return true;
    }
};
int main()
{
    Solution sol;
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b = {4, 5, 3, 2, 1};
    bool is = sol.IsPopOrder(a, b);
    std::cout << is << std::endl;
}