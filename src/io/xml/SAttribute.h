/*
 * SAttribute.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef SATTRIBUTE_H_
#define SATTRIBUTE_H_

#include "core/collections/stringc.h"

namespace irrgame
{
	namespace io
	{
		// structure for storing attribute-name pairs
		struct SAttribute
		{
			public:
				/*
				 * Operators
				 */
				//! Equality operator
				bool operator ==(const SAttribute& other) const;

				//! Inequality operator
				bool operator !=(const SAttribute& other) const;

				//! Is smaller comparator. Copmared only attributes lengths.
				bool operator <(const SAttribute& other) const;

				//! Is bigger comparator. Copmared only attributes lengths.
				bool operator >(const SAttribute& other) const;

			public:
				core::stringc Name;
				core::stringc Value;
		};
	}  // namespace io
}  // namespace irrgame

#endif /* SATTRIBUTE_H_ */
