#include <iostream>
using namespace std;
class SeqList//类
{
  public:
  int array[100];
  int size;
  void PushBack(int v);
};
SeqList seqList;//对象
SeqList* pSeqList;//经过申请空间
int main()
{
  seqList.PushBack(100);
  pSeqList->PushBack(100);
}
