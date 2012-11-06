/*
 * CStringAttribute.cpp
 *
 *  Created on: Aug 8, 2012
 *      Author: gregorytkach
 */
#include "CStringAttribute.h"
#include "io/utils/ioutils.h"
#include "core/math/SharedConverter.h"

namespace irrgame
{
	namespace io
	{

		//! Default constructor
		CStringAttribute::CStringAttribute(const c8* name, const c8* value)
		{
			Name = name;
			setString(value);
		}

		//! Extended constructor for work with binary data
		CStringAttribute::CStringAttribute(const c8* name, void* binaryData,
				s32 lenghtInBytes)
		{
			Name = name;
			setBinary(binaryData, lenghtInBytes);
		}

		s32 CStringAttribute::getInt()
		{
			return atoi(Value.cStr());
		}

		f32 CStringAttribute::getFloat()
		{
			return core::SharedConverter::getInstance().convertToFloat(Value.cStr());
		}

		bool CStringAttribute::getBool()
		{
			return Value.equalsIgnoreCase("true");
		}

		core::stringc CStringAttribute::getString()
		{
			return Value;
		}

		void CStringAttribute::setInt(s32 intValue)
		{
			Value = core::stringc(intValue);
		}

		void CStringAttribute::setFloat(f32 floatValue)
		{
			Value = core::stringc(floatValue);

		}

		void CStringAttribute::setString(const c8* text)
		{
			Value = text;
		}

		EAttributeType CStringAttribute::getType() const
		{
			return EAT_STRING;
		}

		const c8* CStringAttribute::getTypeString() const
		{
			return "string";
		}

		void CStringAttribute::getBinary(void* outdata, s32 maxLength)
		{
			s32 dataSize = maxLength;
			c8* datac8 = (c8*) (outdata);
			s32 p = 0;
			const c8* dataString = Value.cStr();

			for (s32 i = 0; i < dataSize; ++i)
				datac8[i] = 0;

			while (dataString[p] && p < dataSize)
			{
				s32 v = ioutils::getByteFromHex((c8) dataString[p * 2]) * 16;

				if (dataString[(p * 2) + 1])
					v += ioutils::getByteFromHex((c8) dataString[(p * 2) + 1]);

				datac8[p] = v;
				++p;
			}
		}

		void CStringAttribute::setBinary(void* data, s32 maxLength)
		{
			s32 dataSize = maxLength;
			c8* datac8 = (c8*) (data);
			char tmp[3];
			tmp[2] = 0;
			Value = "";

			for (s32 b = 0; b < dataSize; ++b)
			{
				ioutils::getHexStrFromByte(datac8[b], tmp);
				Value.append(tmp);
			}
		}
	} //end namespace io
} //end namespace irrgame

