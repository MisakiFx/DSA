#include <iostream>
#include "List.h" 
using namespace std;
template <class T>
class Queue : public List<T>
{
	public:
		void enqueue(T const& e)
		{
			insertAsLast(e);//入队：尾部插入 
		}
		T dequeue()
		{
			return List<T>::remove(List<T>::first());//出队：首部删除 
		}
		T& front()
		{
			return List<T>::first()->data;//对首 
		}
};
int main()
{
	
}
