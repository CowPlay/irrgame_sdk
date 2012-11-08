/*
 * coreutils.cpp
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#include "core/utils/SharedCoreUtils.h"

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
				CurrentLocale(ELID_ANSI)
		{
		}

		//! Destructor. Should use only one time.
		SharedCoreUtils::~SharedCoreUtils()
		{
		}

		void SharedCoreUtils::localeSet(ELocaleID id)
		{
			CurrentLocale = id;
		}

		//! Returns a character converted to lower case
		u32 SharedCoreUtils::localeLower(u32 x) const
		{
			switch (CurrentLocale)
			{
				case ELID_GERMAN:
				case ELID_ANSI:
				{
					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			}
			// ansi
			return x >= 'A' && x <= 'Z' ? x + 0x20 : x;
		}

		//! Returns a character converted to upper case
		u32 SharedCoreUtils::localeUpper(u32 x) const
		{
			switch (CurrentLocale)
			{
				case ELID_GERMAN:
				case ELID_ANSI:
				{
					break;
				}
				default:
				{
					//Not implemented
					IRR_ASSERT(false);
					break;
				}
			}

			// ansi
			return x >= 'a' && x <= 'z' ? x + ('A' - 'a') : x;
		}
	}  // namespace core

}  // namespace irrgame

