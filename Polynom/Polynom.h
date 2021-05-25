#ifndef _POLYNOM_
#define _POLYNOM_

#include "Monom.h"
#include "List.h"

#include <iostream>

using namespace std;

class TPolynomial : public TList<TMonomData>
{
public:
	TPolynomial();
	TPolynomial( TPolynomial& _v);
	~TPolynomial();

	TPolynomial& operator +=(TMonom & _v);

	TPolynomial operator *(TPolynomial& _v);
	TPolynomial operator +(TPolynomial & _v);
	TPolynomial operator -(TPolynomial & _v);

	void LoadToFile();

};
TPolynomial::TPolynomial() : TList<TMonomData>()
{

}

TPolynomial::TPolynomial(TPolynomial& _v) : TList<TMonomData>()
{
}

TPolynomial::~TPolynomial()
{
}

TPolynomial& TPolynomial::operator+=(TMonom& _v)
{
	if (this->root == 0)
	{
		this->root = _v.Clone();
		this->end = this->root;
	}
	else
	{
		TMonom* tmp = static_cast<TMonom*>(this->root);
		while (tmp != 0)
		{
			if (*tmp == _v)
			{
				tmp->SetK(tmp->GetK() + _v.GetK());
				return *this;
			}
			else
			{
				TMonom* _v2 = _v.Clone();
				if (*tmp < _v)
				{
					_v2->SetPrev(tmp->GetPrev());
					_v2->SetNext(tmp);

					if (tmp->GetPrev() != 0)
						tmp->GetPrev()->SetNext(_v2);
					else
						this->root = _v2;

					tmp->SetPrev(_v2);

					return *this;
				}
				else
				{
					if (tmp->GetNext() == 0)
					{
						_v2->SetPrev(tmp);
						tmp->SetNext(_v2);
						this->end = _v2;
						return *this;
					}
					else
						tmp = static_cast<TMonom*>(tmp->GetNext());

				}
			}
		}
	}
	return *this;
}

TPolynomial TPolynomial::operator*(TPolynomial& _v)
{
	TPolynomial res;
	TMonom* tmp1 = static_cast<TMonom*>(this->root);
	if (this->root == 0 && _v.root == 0)
		throw new exception;
	while (tmp1 != 0)
	{
		TMonom* tmp2 = static_cast<TMonom*>(_v.root);
		while (tmp2 != 0)
		{
			TMonom tmp3;
			tmp3 = (static_cast<TMonom&>(*tmp2)) * (static_cast<TMonom&>(*tmp1));
			res += tmp3;
			tmp2 = static_cast<TMonom*>(tmp2->GetNext());
		}
		tmp1 = static_cast<TMonom*>(tmp1->GetNext());
	}
	return res;
}

TPolynomial TPolynomial::operator+(TPolynomial& _v)
{
	if (_v.root == 0)
		throw new exception;
	if (root == 0)
		throw new exception;
	TPolynomial polynomRes;
	TMonom* tmp = static_cast<TMonom*>(_v.root);
	TMonom* tmp2 = static_cast<TMonom*>(root);
	TMonom* r = 0;
	while (tmp != 0 && tmp2 != 0)
	{
		TMonom tmp3;
		if (*tmp == *tmp2)
		{
			tmp3 = ((*tmp) + (*tmp2))[0];
			tmp = static_cast<TMonom*>(tmp->GetNext());
			tmp2 = static_cast<TMonom*>(tmp2->GetNext());
		}
		else if (*tmp < *tmp2)
		{
			tmp3 = *tmp2;
			tmp2 = static_cast<TMonom*>(tmp2->GetNext());
		}
		else
		{
			tmp3 = *tmp;
			tmp = static_cast<TMonom*>(tmp->GetNext());
		}
		if (r == 0)
		{
			polynomRes += tmp3;
			r = static_cast<TMonom*>(polynomRes.root);
		}
		else
		{
			r->SetNext(tmp3.Clone());
			r->GetNext()->SetPrev(static_cast<TMonom*>(r));
			r = static_cast<TMonom*>(r->GetNext());
		}
	}
	if (tmp != 0)
	{
		while (tmp != 0)
		{
			r->SetNext(new TMonom(*tmp));
			r->GetNext()->SetPrev(r);
			r = static_cast<TMonom*>(r->GetNext());
			tmp = static_cast<TMonom*>(tmp->GetNext());
		}
	}
	else if (tmp2 != 0)
	{
		while (tmp2 != 0)
		{
			r->SetNext(new TMonom(*tmp2));
			r->GetNext()->SetPrev(r);
			r = static_cast<TMonom*>(r->GetNext());
			tmp2 = static_cast<TMonom*>(tmp->GetNext());

		}
	}
	return polynomRes;
}

TPolynomial TPolynomial::operator-(TPolynomial& _v)
{
	if (_v.root == 0 || root == 0)
		throw new exception;

	TPolynomial res;
	TMonom* tmp = static_cast<TMonom*>(_v.root);
	TMonom* tmp2 = static_cast<TMonom*>(root);
	TMonom* r = 0;

	while (tmp != 0 && tmp2 != 0)
	{
		TMonom tmp3;
		if (*tmp == *tmp2)
		{
			tmp3 = ((*tmp) - (*tmp2))[0];
			tmp = static_cast<TMonom*>(tmp->GetNext());
			tmp2 = static_cast<TMonom*>(tmp2->GetNext());
		}
		else if (*tmp > *tmp2)
		{
			tmp3 = *tmp;
			tmp = static_cast<TMonom*>(tmp->GetNext());
		}
		else
		{
			tmp3 = *tmp2;
			tmp2 = static_cast<TMonom*>(tmp2->GetNext());
		}

		if (r == 0)
		{
			res += tmp3;
			r = static_cast<TMonom*>(res.root);
		}
		else
		{
			r->SetNext(tmp3.Clone());
			r->GetNext()->SetPrev(static_cast<TMonom*>(r));
			r = static_cast<TMonom*>(r->GetNext());
		}
	}
	if (tmp != 0)
	{
		while (tmp != 0)
		{
			r->SetNext(new TMonom(*tmp));
			r->GetNext()->SetPrev(r);
			r = static_cast<TMonom*>(r->GetNext());
			tmp = static_cast<TMonom*>(tmp->GetNext());
		}
	}
	else if (tmp2 != 0)
	{
		while (tmp2 != 0)
		{
			r->SetNext(new TMonom(*tmp2));
			r->GetNext()->SetPrev(r);
			r = static_cast<TMonom*>(r->GetNext());
			tmp = static_cast<TMonom*>(tmp2->GetNext());
		}
	}
	return res;
}

void TPolynomial::LoadToFile()
{
	ofstream fout("Polynom.txt");
	if (!fout)
		throw new exception;
	if (this->root == 0)
		return;
	TMonom* tmp = static_cast<TMonom*>(this->root);
	while (tmp != NULL)
	{
		fout << *(tmp) << " ";
		tmp = static_cast<TMonom*>(tmp->GetNext());
	}
	return;
}

#endif 
