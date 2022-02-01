#include <iostream>
using namespace std;

template < class T >
SortedListClass< T >::SortedListClass(
  )
{
  head = NULL;
  tail = NULL;
}

template < class T >
SortedListClass< T >::SortedListClass(
  const SortedListClass< T > &rhs
  )
{
  if (rhs.head != NULL)
  {
    LinkedNodeClass< T > *rhsNode = rhs.head;
    head = new LinkedNodeClass< T >(NULL, rhsNode->getValue(), NULL);
    LinkedNodeClass< T > *thisNode = head;
    LinkedNodeClass< T > *nextNode = NULL;
    while (rhsNode->getNext() != NULL)
    {
      rhsNode = rhsNode->getNext();
      nextNode = new LinkedNodeClass< T >(thisNode, rhsNode->getValue(), NULL);
      nextNode->setBeforeAndAfterPointers();
      thisNode = nextNode;
    }
    tail = thisNode;
  }
  else
  {
    head = NULL;
    tail = NULL;
  }
}

template < class T >
SortedListClass< T >::~SortedListClass(
  )
{
  this->clear();
}

template < class T >
void SortedListClass< T >::clear(
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

template < class T >
void SortedListClass< T >::insertValue(
  const T &valToInsert  
  )
{
  LinkedNodeClass< T > *newNode = NULL;
  if (head != NULL)
  {
    LinkedNodeClass< T > *thisNode = head;
    LinkedNodeClass< T > *nextNode = NULL;
    bool insert = false;
    //If the inserted value is smaller than the first node value,
    //put it in the first place
    if (valToInsert < thisNode->getValue())
    {
      newNode = new LinkedNodeClass< T >(NULL, valToInsert, thisNode);
      head = newNode;
      newNode->setBeforeAndAfterPointers();
      insert = true;
    }
    //If the inserted value is between the first node value and 
    //the last node value, check each node until find the appropriate place
    while (thisNode->getNext() != NULL && !insert)
    {
      nextNode = thisNode->getNext();
      insert = valToInsert >= thisNode->getValue() && 
               valToInsert < nextNode->getValue();
      if (insert)
      {
        newNode = new LinkedNodeClass< T >(thisNode, valToInsert, nextNode);
        newNode->setBeforeAndAfterPointers();
      }
      thisNode = nextNode;
    }
    //If the inserted value has not been assigned to a place after 
    //the previous steps, put it in the last place
    if (!insert)
    {
      newNode = new LinkedNodeClass< T >(tail, valToInsert, NULL);
      tail = newNode;
      newNode->setBeforeAndAfterPointers();
    } 
  }
  else
  {
    newNode = new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    head = newNode;
    tail = newNode;
  }
}

template < class T >
void SortedListClass< T >::printForward(
  ) const
{
  LinkedNodeClass< T > *thisNode = head;
  cout << "Forward List Contents Follow:" << endl;
  while (thisNode != NULL)
  {
    cout << "  " << thisNode->getValue() << endl;
    thisNode = thisNode->getNext();
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
void SortedListClass< T >::printBackward(
  ) const
{
  LinkedNodeClass< T > *thisNode = tail;
  cout << "Backward List Contents Follow:" << endl;
  while (thisNode != NULL)
  {
    cout << "  " << thisNode->getValue() << endl;
    thisNode = thisNode->getPrev();
  }
  cout << "End Of List Contents" << endl;
}

template < class T >
bool SortedListClass< T >::removeFront(
  T &theVal
  )
{
  bool success = (head != NULL);
  if (success)
  {
    LinkedNodeClass< T > *temp = head;
    theVal = head->getValue();
    if (head->getNext() != NULL)
    {
      head = head->getNext();
      head->setPreviousPointerToNull();
    }
    else
    {
      head = NULL;
      tail = NULL;
    }
    
    delete temp;
  }
  return success;
}

template < class T >
bool SortedListClass< T >::removeLast(
  T &theVal
  )
{
  bool success = (tail != NULL);
  if (success)
  {
    LinkedNodeClass< T > *temp = tail;
    theVal = tail->getValue();
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
  }
  return success;
}

template < class T >
int SortedListClass< T >::getNumElems(
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
bool SortedListClass< T >::getElemAtIndex(
  const int index,
  T &outVal
  ) const
{
  bool success = false;
  LinkedNodeClass< T > *temp = head;
  success = index >= 0 && index < this->getNumElems();
  if (success)
  {
    for (int i = 0; i < index; i++)
    {
      temp = temp->getNext();
    }
    outVal = temp->getValue();
  }
  else
  {
    cout << "The index is out of range! The maximum index is " << 
            this->getNumElems() - 1 << endl;
  }
  return success;
}