/*
 * EComparisonFunc.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef ECOMPARISONFUNC_H_
#define ECOMPARISONFUNC_H_

namespace irrgame
{
	namespace video
	{
		//! Comparison function, e.g. for depth buffer test
		enum E_COMPARISON_FUNC
		{
			//! Test never succeeds, this equals disable
			ECFN_NEVER = 0,
			//! <= test, default for e.g. depth test
			ECFN_LESSEQUAL = 1,
			//! Exact equality
			ECFN_EQUAL = 2,
			//! exclusive less comparison, i.e. <
			ECFN_LESS,
			//! Succeeds almost always, except for exact equality
			ECFN_NOTEQUAL,
			//! >= test
			ECFN_GREATEREQUAL,
			//! inverse of <=
			ECFN_GREATER,
			//! test succeeds always
			ECFN_ALWAYS
		};

	}  // namespace video

}  // namespace irrgame

#endif /* ECOMPARISONFUNC_H_ */
