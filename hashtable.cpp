/*
Copyright (C) 2013 Matej Zavrsnik <matejzavrsnik@gmail.com> (matejzavrsnik.com)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <QLinkedList>

template <class T> // data type for storing
class CHashtable {
    
private:
    QLinkedList<T>* m_items;
    uint m_size; // size of array
    uint m_count; // how many elements it contains
    uint (*m_hashFunction) (const T&,uint);
    bool m_storeDuplicates;
    
    int getIndex( T item, uint (*hf) (const T&,uint) ) 
    {
        int index = -1;
        if(hf != NULL)
            index = hf(item,m_size);
        else if(m_hashFunction != NULL)
            index = m_hashFunction(item,m_size);
        return index;
    }
    
public:
    CHashtable(uint size, bool storeDuplicates = false) 
    {
        m_items = new QLinkedList<T>[size];
        m_size = size;
        m_storeDuplicates = storeDuplicates;
        m_hashFunction = NULL;
        m_count = 0;
    }
    
    virtual ~CHashtable() 
    {
        for(uint i=0; i<m_size; i++ )
        {
            while(!m_items[i].isEmpty())
            {
                m_items[i].removeFirst();
            }
        }
        delete [] m_items;
    }
    
    virtual void setHashFunction(uint (*hf) (const T&,uint)) 
    {
        m_hashFunction = hf;
    }
    
    virtual void insert(T item, uint (*hf) (const T&,uint) = NULL) 
    {
        int index = getIndex(item,hf);
        if(index >= 0 ) 
        {
            if(m_storeDuplicates || !m_items[index].contains(item)) 
            {
                m_items[index].append(item);
                ++m_count;
            }
        }
    }
    
    virtual bool search(T item, uint (*hf) (const T&,uint) = NULL) 
    {
        int index = getIndex(item,hf);
        if(index >= 0) 
        {
            return m_items[index].contains(item);
        }
        return false;
    }
    
    virtual void remove(T item, uint (*hf) (const T&,uint) = NULL) 
    {
        int index = getIndex(item,hf);
        if(index >= 0) 
        {
            m_items[index].removeOne(item);
        }
    }
    
    // how many items are stored in table
    virtual uint count()
    {
        return m_count;
    }
    
    // how many items are stored in indexed element
    virtual uint count( int index )
    {
        return (uint)m_items[index].count();
    }
    
};
