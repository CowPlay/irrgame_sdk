/*
 * IActionReceiver.h
 *
 *  Created on: Sep 12, 2012
 *      Author: gregorytkach
 */

#ifndef IACTIONRECEIVER_H_
#define IACTIONRECEIVER_H_

namespace irrgame
{

	namespace actions
	{
		//!
		class IActionReceiver
		{
			public:

				virtual ~IActionReceiver()
				{
				}

				virtual bool onAction() = 0;

			private:
		};
	}  // namespace actions

}  // namespace irrgame

#endif /* IACTIONRECEIVER_H_ */
