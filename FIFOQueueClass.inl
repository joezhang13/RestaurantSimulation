#include <iostream>
using namespace std;

template < class T >
FIFOQueueClass< T >::FIFOQueueClass(
  )
{
  head = NULL;
  tail = NULL;
}

template < class T >
FIFOQueueClass< T >::~FIFOQueueClass(
  )
{
  this->clear();
}

template < class T >
void FIFOQueueClass< T >::enqueue(
  const T &newItem
  )
{
  LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >(NULL, newItem, head);
  head = newNode;
  newNode->setBeforeAndAfterPointers();
  if (tail == NULL)
  {
    tail = newNode;
  }
}

template < class T >
bool FIFOQueueClass< T >::dequeue(
  T &outItem
  )
{
  if (tail == NULL)
  {
    return false;
  }
  else
  {
    outItem = tail->getValue();
    LinkedNodeClass< T > *temp = tail;
    if (tail->getPrev() != NULL)
    {
      tail = tail->getPrev();
      tail->setNextPointerToNull();
    }
    else
    {
      head = NULL;
      tail = NULL;
    }
    
    delete temp;
    return true;
  }
}

template < class T >
void FIFOQueueClass< T >::print(
  ) const
{
  if (head == NULL)
  {
    cout << "This queue is empty!" << endl;
  }
  
  LinkedNodeClass< T > *temp = head;
  while (temp != NULL)
  {
    if (temp->getNext() != NULL)
    {
      cout << temp->getValue() << " ";
    }
    else
    {
      cout << temp->getValue() << endl;
    }
    temp = temp->getNext();
  }
}

template < class T >
int FIFOQueueClass< T >::getNumElems(
  ) const
{
  int num = 0;
  LinkedNodeClass< T > *temp = head;
  while (temp != NULL)
  {
    num++;
    temp = temp->getNext();
  }
  return num;
}

template < class T >
void FIFOQueueClass< T >::clear(
  )
{
  LinkedNodeClass< T > *temp = head;
  while (head != NULL)
  {
    head = head->getNext();
    delete temp;
    temp = head;
  }
  head = NULL;
  tail = NULL;
}