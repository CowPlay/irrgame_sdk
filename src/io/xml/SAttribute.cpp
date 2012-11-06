/*
 * SAttribute.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "SAttribute.h"

namespace irrgame
{
	namespace io
	{
		//! Equality operator
		bool SAttribute::operator ==(const SAttribute& other) const
		{
			return this->Name == other.Name;
		}

		//! Inequality operator
		bool SAttribute::operator !=(const SAttribute& other) const
		{
			return !(*this == other);
		}

		//! Is smaller comparator. Copmared only attributes lengths.
		bool SAttribute::operator <(const SAttribute& other) const
		{
			return (this->Name < other.Name && this->Value < other.Value);
		}

		//! Is bigger comparator. Copmared only attributes lengths.
		bool SAttribute::operator >(const SAttribute& other) const
		{
			return !(*this < other);
		}
	}  // namespace io
}  // namespace irrgame

