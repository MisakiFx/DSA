#include <iostream>
#include "List.h" 
using namespace std;
template <class T>
class Queue : public List<T>
{
	public:
		void enqueue(T const& e)
		{
			insertAsLast(e);//��ӣ�β������ 
		}
		T dequeue()
		{
			return List<T>::remove(List<T>::first());//���ӣ��ײ�ɾ�� 
		}
		T& front()
		{
			return List<T>::first()->data;//���� 
		}
};
int main()
{
	
}
