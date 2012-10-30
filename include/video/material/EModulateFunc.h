/*
 * EModulateFunc.h
 *
 *  Created on: Oct 26, 2012
 *      Author: gregorytkach
 */

#ifndef EMODULATEFUNC_H_
#define EMODULATEFUNC_H_

namespace irrgame
{

	namespace video
	{

		//! MaterialTypeParam: e.g. DirectX: D3DTOP_MODULATE, D3DTOP_MODULATE2X, D3DTOP_MODULATE4X
		enum E_MODULATE_FUNC
		{
			EMFN_MODULATE_1X = 1, EMFN_MODULATE_2X = 2, EMFN_MODULATE_4X = 4
		};

	}  // namespace video

}  // namespace irrgame

#endif /* EMODULATEFUNC_H_ */
