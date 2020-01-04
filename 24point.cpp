#include <iostream>
#include <string>
#include "fraction.h"
using namespace std;
class CacuClass
{
	//�ڲ������� ˫������ ͬʱ��¼��ֵ(fraction���Լ��õ������ֵ�ķ���(string)
public:
	fraction f;
	string str;
	CacuClass *Prev, *Next;
//================================================

//���캯��
	CacuClass()
	{
		f = 0;
		str = "";
		Prev = NULL;
		Next = NULL;
	}
	CacuClass(int i)
	{
		f = i;
		str = to_string(i);
		Prev = NULL;
		Next = NULL;
	}
//=======================================
	//����
	CacuClass *insert()  //����
	{
		CacuClass *p;
		p = new CacuClass;
		p->Prev = this;
		if (Next != NULL)
		{
			Next->Prev = p;
			p->Next = Next;
		}
		Next = p;

		return p;
	}
	CacuClass *insert(CacuClass *p)  //����
	{
		if (p != NULL)
		{
			p->Prev = this;
			if (Next != NULL)
			{
				Next->Prev = p;
				p->Next = Next;
			}
			Next = p;
		}
		return p;
	}
	CacuClass *Remove() //ɾ���ڵ�
	{
		CacuClass *p;
	    p = Prev;
		if (Next!=NULL)	Next->Prev = Prev;
		if (Prev != NULL) Prev->Next = Next;

		return p;
	}

	CacuClass *Copy()  //��������
	{
		CacuClass *p,*q,*r;
		p = this;
		while(p->Prev != NULL)
		{
			p = p->Prev;
		}
		q = new CacuClass;
		r = q;
		q->f = p->f;
		q->str = p->str;
		while (p->Next!=NULL)
		{
			p = p->Next;
			q = q->insert();
			q->f = p->f;
			q->str = p->str;
		}

		return r;
	}
	void Del()  //ɾ������
	{
		CacuClass *p,*q;
		p = this;
		while (p->Prev != NULL)
		{
			p = p->Prev;
		}
 
		while (p!=NULL)
		{
			q = p->Next;
			delete p;
			p = q;
		}
	}
//==============================================

	CacuClass operator+(CacuClass CC)
	{
		CacuClass outCC;
		outCC.f = f + CC.f;
		outCC.str = (string)"(" + str + (string)"+" + CC.str + (string)")";
		return outCC;
	}
	CacuClass operator-(CacuClass CC)
	{
		CacuClass outCC;
		outCC.f = f - CC.f;
		outCC.str = (string)"(" + str + (string)"-" + CC.str + (string)")";
		return outCC;
	}
	CacuClass operator*(CacuClass CC)
	{
		CacuClass outCC;
		outCC.f = f * CC.f;
		outCC.str = (string)"(" + str + (string)"*" + CC.str + (string)")";
		return outCC;
	}
	CacuClass operator/(CacuClass CC)
	{
		CacuClass outCC;
		outCC.f = f / CC.f;
		outCC.str = (string)"(" + str + (string)"/" + CC.str + (string)")";
		return outCC;
	}

	void operator=(CacuClass CC)
	{

		f = CC.f;
		str = CC.str;
	}

	friend ostream &operator<<(ostream &output, CacuClass CC)
	{
		output << CC.str;
		return output;
	}

};
//=========================================================================================
void Cacu2(int isize, CacuClass *CCo, int aim)
{
	CacuClass *CC,*p,*q,*w;
	CacuClass *pPrev,*qPrev;

	p = CCo->Next;
	if (isize == 1)
	{
		if (p->f == aim)
		{
			cout << p->str << " = " << aim << endl;
		}
	}
	else
	{
		CC = CCo->Copy();
		p = CC->Next;
		while (p->Next != NULL)
		{
			q = p->Next;
			while (q != NULL)
			{
				w = new CacuClass;
				pPrev=p->Remove();
				qPrev=q->Remove();

				CC->insert(w);

				*w = *p + *q;
				Cacu2(isize - 1, CC, aim);

				*w = *p - *q;
				Cacu2(isize - 1, CC, aim);

				*w = *q - *p;
				Cacu2(isize - 1, CC, aim);

				*w = (*p) * (*q);
				Cacu2(isize - 1, CC, aim);

				if (q->f != 0)
				{
					*w = *p / *q;
					Cacu2(isize - 1, CC, aim);
				}

				if (p->f!=0)
				{
				    *w = *q / *p;
			    	Cacu2(isize - 1, CC, aim);
				}
				qPrev->insert(q);
				pPrev->insert(p);
				w->Remove();
				delete w;

				q = q->Next;
			}
			p = p->Next;
		}
		CC->Del();
	}
}
void Cacu(int isize, int *a, int aim)
{
	int i;
	CacuClass *CC,*p;
	CC = new CacuClass;
	p = CC;
	for (i = 0; i < isize; i++)
	{
		p=p->insert();
		*p = a[i];
	}
	Cacu2(isize, CC, aim);
}
int main()
{
	int a[4] = { 1,2,3,4 };
	Cacu(4, a, 24);
	system("pause");
}