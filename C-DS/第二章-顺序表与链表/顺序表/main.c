#include <stdio.h>
#include "SeqList.h"
int main()
{
#if 1
  SeqList seqlist;
  SeqListInit(&seqlist, 10);
  SeqListPushBack(&seqlist, 5);
#else
  SeqList seqlist = SeqListInit(seqlist, 10);
#endif
}
