/*
 * coreutils.h
 *
 *  Created on: Nov 2, 2012
 *      Author: gregorytkach
 */

#ifndef COREUTILS_H_
#define COREUTILS_H_

#include "compileConfig.h"
#include "ELocaleID.h"

namespace irrgame
{
	namespace core
	{
		class SharedCoreUtils
		{

			public:

				//! Singleton realization
				static SharedCoreUtils& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedCoreUtils();

				//! Destructor. Should use only one time.
				virtual ~SharedCoreUtils();

				//! Copy constructor. Do not implement.
				SharedCoreUtils(const SharedCoreUtils& root);

				//! Override equal operator. Do not implement.
				const SharedCoreUtils& operator=(SharedCoreUtils&);

			public:
				void localeSet(ELocaleID id);

				//! Returns a character converted to lower case
				u32 localeLower(u32 x) const;

				//! Returns a character converted to upper case
				u32 localeUpper(u32 x) const;

			public:

				ELocaleID locale_current;
		};
	}  // namespace core
}  // namespace irrgame

#endif /* COREUTILS_H_ */
