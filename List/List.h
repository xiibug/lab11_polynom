#ifndef _TLIST_ 
#define _TLIST_ 

#include <iostream>
#include<fstream>

using namespace std;

template <class T>
class TListElem
{
protected:
    T data;
    TListElem* next=0;
    TListElem* prev=0;
public:
    TListElem();
    TListElem(T _data);
    ~TListElem();

    T GetData();

    TListElem<T>* GetNext();
    TListElem<T>* GetPrev();

    void SetData(T _data);
    void SetNext(TListElem* _next);
    void SetPrev(TListElem* _prev);

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TListElem<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TListElem<T1>& A);

    virtual TListElem<T>* Clone();
};


template <class T1>
inline ostream& operator<< (ostream& ostr, const TListElem<T1>& A)
{
    return ostr << A.data;
}

template <class T1>
inline istream& operator >> (istream& istr, TListElem<T1>& A)
{
    return istr >> A.data;
}

template <class T>
class TList
{
protected:
    TListElem<T>* root=0;
    TListElem<T>* end=0;
    int count;
public:
    TList();
    TList(TList<T>& _v);
    ~TList();

    TList<T>& operator =(TList<T>& _v);

    bool IsEmpty(void) const;
    bool IsFull(void) const;

    void InsFirst(T d);
    void InsLast(T d);
    void Ins(TListElem<T>* e, T d);

    TListElem<T>* GetFirst();
    TListElem<T>* GetLast();

    void DelFirst();
    void DelLast();
    void Del(TListElem<T>* e);

    void LoadToFile();

    template <class T1>
    friend ostream& operator<< (ostream& ostr, const TList<T1>& A);
    template <class T1>
    friend istream& operator >> (istream& istr, TList<T1>& A);

    int GetCount();
};

template <class T1>
ostream& operator<< (ostream& ostr, const TList<T1>& A) {
    TListElem<T1>* i = A.root;
    while (i != 0)
    {
        ostr << *i << " ";
        i = i->GetNext();
    }
    return ostr;
}

template <class T1>
istream& operator >> (istream& istr, TList<T1>& A) {
    int count;
    istr >> count;
    for (int i = 0; i < count; i++)
    {
        T1 d;
        istr >> d;
        A.InsLast(d);
    }
    return istr;
}

template<class T>
inline TList<T>::TList()
{
    root = 0;
    end = 0;
    count = 0;
}

template <class T>
TList<T>::TList(TList<T>& _v)
{
    count = _v.count;
    TListElem<T>* i = _v.root;
    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;

    while (i != 0)
    {
        j = i->Clone();
        j->SetNext(0);
        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }
        p = j;
        if (root == 0)
            root = j;
        end = j;
        i = i->GetNext();
    }
}

template <class T>
TList<T>::~TList()
{
    if (this->root != 0)
    {
        TListElem<T>* i = this->root;
        TListElem<T>* p = 0;
        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }
        this->root = 0;
        this->end = 0;
        this->count = 0;
    }
}

template <class T>
TList<T>& TList<T>::operator =(TList<T>& _v)
{
    if (this == &_v)
        return *this;

    if (this->root != 0)
    {
        TListElem<T>* i = this->root;
        TListElem<T>* p = 0;

        while (i != 0)
        {
            p = i;
            i = i->GetNext();
            delete p;
        }
        this->root = 0;
        this->end = 0;
        this->count = 0;
    }

    count = _v.count;
    TListElem<T>* i = _v.root;
    TListElem<T>* j = this->root;
    TListElem<T>* p = 0;

    while (i != 0)
    {
        j = i->Clone();
        j->SetNext(0);

        if (p != 0)
        {
            p->SetNext(j);
            j->SetPrev(p);
        }

        p = j;

        if (root == 0)
            root = j;

        end = j;
        i = i->GetNext();

        return *this;
    }
}

template<class T>
inline bool TList<T>::IsEmpty(void) const
{
    return count == 0;
}

template<class T>
inline bool TList<T>::IsFull(void) const
{
    try
    {
        TListElem<T>* tmp = new TListElem<T>();
        delete tmp;
        return false;
    }
    catch (...)
    {
        return true;
    }
}

template<class T>
inline void TList<T>::InsFirst(T d)
{
    if (this->IsFull())
        throw new exception;

    TListElem<T>* temp = new TListElem<T>(d);
    temp->SetNext(root);
    root = temp;
    if (end == 0)
        end = temp;
    
    count++;
}

template<class T>
inline void TList<T>::InsLast(T d)
{
    if (this->IsFull())
        throw new exception;


    if (end == 0)
        end = new TListElem<T>(d);
    else
    {
        TListElem<T>* temp = new TListElem<T>(d);
        end->SetNext(temp);
        end = temp;
    }
    if (root == 0)
        root = end;
    count++;
}

template<class T>
inline void TList<T>::Ins(TListElem<T>* e, T d)
{
    TListElem<T>* tmp = d.Clone();
    tmp->SetNext(e->GetNext());
    tmp->SetPrev(e);
    e->GetNext()->SetPrev(tmp);
    e->SetNext(tmp);
    count++;
}

template<class T>
inline TListElem<T>* TList<T>::GetFirst()
{
    return root;
}

template<class T>
inline TListElem<T>* TList<T>::GetLast()
{
    return end;
}

template<class T>
inline void TList<T>::DelFirst()
{
    TListElem<T>* i = this->root;
    root = root->GetNext();
    count--;
    delete i;
}

template<class T>
inline void TList<T>::DelLast()
{
    TListElem<T>* i = this->end;
    end = root->GetPrev();
    count--;
    delete i;
}

template<class T>
inline void TList<T>::Del(TListElem<T>* e)
{
    e->GetPrev()->SetNext(e->GetNext());
    e->GetNext()->SetPrev(e->GetPrev());
    count--;
    delete e;
}

template<class T>
inline void TList<T>::LoadToFile()
{
    ofstream fout("List.txt");
    if (fout.is_open())
        fout << *this;
    else
        throw new exception;
}

template <class T>
int TList<T>::GetCount()
{
    return count;
}

template<class T>
inline TListElem<T>::TListElem()
{
    data = 0;
    next = 0;
    prev = 0;
}

template<class T>
inline TListElem<T>::TListElem(T _data)
{
    data = _data;
    next = 0;
    prev = 0;
}

template<class T>
inline TListElem<T>::~TListElem()
{
    next = 0;
    prev = 0;
}

template<class T>
inline T TListElem<T>::GetData()
{
    return data;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetNext()
{
    return next;
}

template<class T>
inline TListElem<T>* TListElem<T>::GetPrev()
{
    return prev;
}

template<class T>
inline void TListElem<T>::SetData(T _data)
{
    data = _data;
}

template<class T>
inline void TListElem<T>::SetNext(TListElem<T>* _next)
{
    next = _next;
}

template<class T>
inline void TListElem<T>::SetPrev(TListElem<T>* _prev)
{
    prev = _prev;
}

template<class T>
inline TListElem<T>* TListElem<T>::Clone()
{
    TListElem<T>* res = new TListElem<T>(*this);
    return res;
}

#endif 