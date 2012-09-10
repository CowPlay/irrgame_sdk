/*
 * coreutil.h
 *
 *  Created on: Sep 6, 2012
 *      Author: gregorytkach
 */

#ifndef COREUTIL_H_
#define COREUTIL_H_

namespace irrgame
{
	namespace core
	{
		enum eLocaleID
		{
			IRR_LOCALE_ANSI = 0, IRR_LOCALE_GERMAN = 1
		};

		static eLocaleID locale_current = IRR_LOCALE_ANSI;
		static inline void localeSet(eLocaleID id)
		{
			locale_current = id;
		}

		//! Returns a character converted to lower case
		static inline u32 localeLower(u32 x)
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
		static inline u32 localeUpper(u32 x)
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
	}
}

#endif /* COREUTIL_H_ */
