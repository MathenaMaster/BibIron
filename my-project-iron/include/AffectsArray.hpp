

#ifndef AFFECTSARRAY_HPP
#define AFFECTSARRAY_HPP

template<class Affect>
class Array
{
	protected :
		Affect	** affects;
		int limit;
	
	public :
		Array(int limit);
		int AffectCount();
		void AddAffect(Affect *);
		void RetireAffect(int);
		Affect ** GetAffects();
		Affect * GetIdx(int);
};

/*

#include "Effects.hpp"
#include "Attack.hpp"

template class Array<Effect>;
template class Array<Attack>;

*/


#endif

