
#include <string.h>

#include "Effects.hpp"
#include "Attack.hpp"
#include "AffectsArray.hpp"


template<class Affect>
Array<Affect>::Array(int limit) : affects(nullptr), limit(limit)
{
	if (limit < 0) this->limit = 0; // 0 means no limit
}

template<class Affect>
int Array<Affect>::AffectCount()
{
	int affectCount = 0;
	
	if (this->affects == nullptr) return 0;
	for (; this->affects[affectCount]; ++affectCount) ;
	return affectCount;
}

template<class Affect>
void Array<Affect>::AddAffect(Affect * affect)
{
	if (affect == nullptr) return;
	//effect->ApplyTarget(this);
	int count = this->AffectCount();
	if (this->affects == nullptr) {
		this->affects = new Affect*[2];
		this->affects[0] = affect;
		this->affects[1] = nullptr;
	} else {
		if (this->limit && count >= this->limit) return ;
		Affect ** copy = new Affect*[count + 2];
		memcpy(copy, this->affects, count); // + 1);
		copy[count] = affect;
		copy[count + 1] = nullptr;
		delete this->affects;
		this->affects = copy;
	}
}

template<class Affect>
void Array<Affect>::RetireAffect(int pos)
{
	int resize = this->AffectCount();
	
	if (resize <= 1) {
		if (resize == 1) {
			delete this->affects;
		}
		this->affects = nullptr;
		return ;
	}
	Affect **copy = new Affect*[resize];
	for (int i = 0; i < pos; ++i) copy[i] = this->affects[i];
	for (int i = pos + 1; i < resize; ++i) copy[i - 1] = this->affects[i];
	copy[resize] = nullptr;
	delete this->affects;
	this->affects = copy;
}

template<class Affect>
Affect ** Array<Affect>::GetAffects()
{
	return this->affects;
}

template<class Affect>
Affect * Array<Affect>::GetIdx(int idx)
{
	if (idx >= this->AffectCount()) return nullptr;
	return this->affects[idx];
}
//template class Array<Effect>;
template class Array<Bonus>;
template class Array<Malus>;
template class Array<Attack>;

template class Array<CharacterBase>;
