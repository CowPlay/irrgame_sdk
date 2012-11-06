/*
 * coreutils.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "core/utils/coreutils.h"

namespace irrgame
{
	namespace core
	{
		//! Singleton realization
		SharedCoreUtils& SharedCoreUtils::getInstance()
		{
			static SharedCoreUtils instance;
			return instance;
		}

		//! Default constructor. Should use only one time.
		SharedCoreUtils::SharedCoreUtils() :
				locale_current(IRR_LOCALE_ANSI)
		{
		}

		//! Destructor. Should use only one time.
		SharedCoreUtils::~SharedCoreUtils()
		{
		}

		void SharedCoreUtils::localeSet(ELocaleID id)
		{
			locale_current = id;
		}

		//! Returns a character converted to lower case
		u32 SharedCoreUtils::localeLower(u32 x) const
		{
			switch (locale_current)
			{
				case IRR_LOCALE_GERMAN:
				case IRR_LOCALE_ANSI:
					break;
			}
			// ansi
			return x >= 'A' && x <= 'Z' ? x + 0x20 : x;
		}

		//! Returns a character converted to upper case
		u32 SharedCoreUtils::localeUpper(u32 x) const
		{
			switch (locale_current)
			{
				case IRR_LOCALE_GERMAN:
				case IRR_LOCALE_ANSI:
					break;
			}

			// ansi
			return x >= 'a' && x <= 'z' ? x + ('A' - 'a') : x;
		}
	}  // namespace core

}  // namespace irrgame

