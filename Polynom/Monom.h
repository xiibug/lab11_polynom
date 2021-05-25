#pragma once

#include "List.h"

class TMonomData
{
public:
	double* data;
	double K;
	int dim; // var number

	TMonomData(int t);
	TMonomData(double* _data = 0, int _dim = 0, double _K = 0);
	TMonomData(TMonomData& _v);
	~TMonomData();

};

class TMonom : public TListElem<TMonomData>
{ // K * x_0 ^ data[0] * x_1 ^ data[1] ... x_(dim-1) ^ data[dim-1]
protected:

public:

	TMonom(TMonomData _data);
	TMonom(double* _data = 0, int _dim = 0, double _K=0);
	TMonom(TMonom& _v);
	~TMonom();

	bool operator ==(const TMonom& _v);
	bool operator !=(const TMonom& _v);
	
	TMonomData& operator * (int);
	TMonomData& operator * ();

	double GetK();
	void SetK(double _k);

	int GetDim();
	void SetDim(int _dim);

	TMonom& operator=(const TMonom& _v);
	double& operator [] (int i);
	
	TMonom operator *(const TMonom& _v);
	TMonom operator /(const TMonom& _v);

	TMonom* operator -(const TMonom& _v);
	TMonom* operator +(const TMonom& _v);

	bool operator >(const TMonom& _v);
	bool operator <(const TMonom& _v);

	friend ostream& operator<<(ostream& ostr, const TMonom& A);
	friend istream& operator>>(istream& istr, TMonom A);

	virtual TMonom* Clone();
	
};

ostream& operator<<(ostream& ostr, const TMonom& A)
{
    ostr << A.data.K;
    for (int i = 0; i < A.data.dim; i++)
        ostr << " * x[" << i << "]^" << A.data.data[i];
    ostr << " ";
    return ostr;
}

istream& operator>>(istream& istr, TMonom A)
{
    int dim = 0;
    if (A.data.dim != 0)
        dim = A.data.dim;
    else
    {
        istr >> dim;
        A.SetDim(dim);
    }
    istr >> A.data.K;
    for (int i = 0; i < dim; i++)
    {
        istr >> A[i];
    }
    return istr;
}

TMonom::TMonom(TMonomData _data) : TListElem<TMonomData>(_data)
{
}

TMonom::TMonom(double* _data, int _dim, double _K) : TListElem<TMonomData>()
{
    if (_dim < 0)
        throw new exception;
    data.dim = _dim;
    data.K = _K;
    if (data.dim > 0)
    {
        data.data = new double[data.dim];
        for (int i = 0; i < data.dim; i++)
            data.data[i] = _data[i];
    }
}

TMonom::TMonom(TMonom& _v) : TListElem<TMonomData>(_v)
{
    prev = 0;
    next = 0;
}

TMonom::~TMonom()
{
}

bool TMonom::operator==(const TMonom& _v)
{
    bool f = true;

    if (data.dim != _v.data.dim)
        f = false;

    if (data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
        {
            if (data.data[i] != _v.data.data[i])
            {
                f = false;
                break;
            }
        }
        return f;
    }
    else
    {
        return data.K == _v.data.K;
    }
}

bool TMonom::operator!=(const TMonom& _v)
{
    return !this->operator==(_v);
}

TMonomData& TMonom::operator*(int)
{
    return data;
}

TMonomData& TMonom::operator*()
{
    return data;
}

double TMonom::GetK()
{
    return data.K;
}

void TMonom::SetK(double _k)
{
    data.K = _k;
}

int TMonom::GetDim()
{
    return data.dim;
}

void TMonom::SetDim(int _dim)
{
    if (data.dim == _dim)
        return;
    if (_dim < 0)
        throw new exception;
    else if (_dim == 0)
    {
        if (data.dim > 0)
            delete[] data.data;
        data.dim = 0;
        data.data = 0;
    }
    else
    {
        if (data.dim > 0)
            delete[] data.data;
        data.dim = _dim;
        data.data = new double[data.dim];
        for (int i = 0; i < data.dim; i++)
            data.data[i] = 0;
    }

}

TMonom& TMonom::operator=(const TMonom& _v)
{
    if (this == &_v)
        return *this;

    next = 0;
    prev = 0;
    data.K = _v.data.K;

    if (data.dim == _v.data.dim)
    {
        for (int i = 0; i < data.dim; i++)
            data.data[i] = _v.data.data[i];
    }

    else if (_v.data.dim == 0)
    {
        if (data.dim > 0)
            delete[] data.data;
        data.dim = 0;
        data.data = 0;
    }
    else
    {
        if (data.dim > 0)
            delete[] data.data;
        data.dim = _v.data.dim;
        data.data = new double[data.dim];
        for (int i = 0; i < data.dim; i++)
            data.data[i] = _v.data.data[i];
    }
}

double& TMonom::operator[](int i)
{
    return data.data[i];
}

TMonom TMonom::operator*(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    TMonom tmp(*this);
    tmp.data.K = data.K * _v.data.K;

    for (int i = 0; i < tmp.data.dim; i++)
        tmp.data.data[i] = this->data.data[i] + _v.data.data[i];

    return tmp;
}

TMonom TMonom::operator/(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    TMonom tmp(*this);
    tmp.data.K = data.K / _v.data.K;

    for (int i = 0; i < data.dim; i++)
        tmp.data.data[i] = this->data.data[i] - _v.data.data[i];

    return tmp;
}

TMonom* TMonom::operator+(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    TMonom* tmp;
    if (*this == _v)
    {
        tmp = new TMonom(*this);
        tmp->data.K = this->data.K + _v.data.K;
    }
    else
    {
        tmp = new TMonom[2];
        if (*this > _v)
        {
            tmp[0] = *this;
            tmp[1] = _v;
        }
        else
        {
            tmp[0] = _v;
            tmp[1] = *this;

        }
    }
    return tmp;
}

TMonom* TMonom::operator-(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    TMonom* tmp = 0;
    if (*this == _v)
    {
        tmp = new TMonom(*this);
        tmp->data.K = this->data.K - _v.data.K;
    }
    else
    {
        tmp = new TMonom[2];
        if (*this > _v)
        {
            tmp[0] = *this;
            tmp[1] = _v;
        }
        else
        {
            tmp[0] = _v;
            tmp[1] = *this;

        }
    }
    return tmp;
}

bool TMonom::operator>(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    if (data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
        {
            if (data.data[i] > _v.data.data[i])
                return true;
            else if (data.data[i] < _v.data.data[i])
                return false;
            else
                continue;
        }
        return true;
    }
    else
    {
        return data.K > _v.data.K;
    }
}

bool TMonom::operator<(const TMonom& _v)
{
    if (data.dim != _v.data.dim)
        throw new exception;

    if (data.dim > 0)
    {
        for (int i = 0; i < data.dim; i++)
        {
            if (data.data[i] < _v.data.data[i])
                return true;
            else if (data.data[i] > _v.data.data[i])
                return false;
            else
                continue;
        }
        return true;
    }
    else
    {
        return data.K < _v.data.K;
    }
}

TMonomData::TMonomData(int t)
{
    if (t < 0)
        throw new exception;
    else if (t == 0)
    {
        dim = 0;
        data = 0;
    }
    else
    {
        data = new double[dim];
        for (int i = 0; i < dim; i++)
            data[i] = 0;
    }
}

TMonomData::TMonomData(double* _data, int _dim, double _K)
{
    if (_dim < 0)
        throw new exception;
    dim = _dim;
    K = _K;
    if (dim > 0)
    {
        data = new double[dim];
        for (int i = 0; i < dim; i++)
            data[i] = 0;
    }
}

TMonomData::TMonomData(TMonomData& _v)
{
    dim = _v.dim;
    K = _v.K;

    if (dim > 0)
    {
        data = new double[dim];
        for (int i = 0; i < dim; i++)
            data[i] = _v.data[i];
    }
}

TMonomData::~TMonomData()
{
    if (data != 0)
    {
        delete[] data;
        data = 0;
        dim = 0;
        K = 0;
    }
}

TMonom* TMonom::Clone()
{
    TMonom* res = new TMonom(*this);
    return res;
}