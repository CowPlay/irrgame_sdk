/*
 * SharedMeshLoader3DS.h
 *
 *  Created on: Nov 12, 2012
 *      Author: gregorytkach
 */

#ifndef SHAREDMESHLOADER3DS_H_
#define SHAREDMESHLOADER3DS_H_

namespace irrgame
{
	namespace scene
	{

		class SharedMeshLoader3DS
		{
			public:
				//! Singleton realization
				static SharedMeshLoader3DS& getInstance();

			private:
				//! Default constructor. Should use only one time.
				SharedMeshLoader3DS();

				//! Destructor. Should use only one time.
				virtual ~SharedMeshLoader3DS();

				//! Copy constructor. Do not implement.
				SharedMeshLoader3DS(const SharedMeshLoader3DS& root);

				//! Override equal operator. Do not implement.
				const SharedMeshLoader3DS& operator=(SharedMeshLoader3DS&);

				/*
				 * Methods
				 */

			public:

//				//! Returns PNG image
//				IImage* createImage(io::IReadFile* file);

		};

	} /* namespace scene */
} /* namespace irrgame */
#endif /* SHAREDMESHLOADER3DS_H_ */
