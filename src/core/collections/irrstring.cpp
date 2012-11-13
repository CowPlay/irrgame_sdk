/*
 * string.cpp
 *
 *  Created on: Oct 30, 2012
 *      Author: gregorytkach
 */

#include "core/collections/stringc.h"
#include "core/utils/SharedCoreUtils.h"

#include "threads/irrgameMonitor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace irrgame
{
	namespace core
	{
		//! Returns empty string
		const stringc& stringc::getEmpty(void)
		{
			static const stringc empty;
			return empty;
		}

		//! Default constructor
		stringc::stringc() :
				Array(0), Allocated(1), Used(1), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			Array = Allocator.allocate(1); // new T[1];
			Array[0] = 0x0;
		}

		//! Copy constructor
		stringc::stringc(const stringc& other) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
			*this = other;
		}

		//! Constructs a string from a float
		stringc::stringc(const double number) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			c8 tmpbuf[255];
			snprintf(tmpbuf, 255, "%0.6f", number);
			*this = tmpbuf;
		}

		//! Constructs a string from an int
		stringc::stringc(s32 number) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			// store if negative and make positive
			bool negative = false;

			if (number < 0)
			{
				number *= -1;
				negative = true;
			}

			// temporary buffer for 16 numbers
			c8 tmpbuf[16] =
			{ 0 };
			u32 idx = 15;

			// special case '0'
			if (!number)
			{
				tmpbuf[14] = '0';
				*this = &tmpbuf[14];
				return;
			}

			// add numbers
			while (number && idx)
			{
				--idx;
				tmpbuf[idx] = (c8) ('0' + (number % 10));
				number /= 10;
			}

			// add sign
			if (negative)
			{
				--idx;
				tmpbuf[idx] = '-';
			}

			*this = &tmpbuf[idx];
		}

		//! Constructs a string from an unsigned int
		stringc::stringc(u32 number) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			// temporary buffer for 16 numbers
			c8 tmpbuf[16] =
			{ 0 };
			u32 idx = 15;

			// special case '0'
			if (!number)
			{
				tmpbuf[14] = '0';
				*this = &tmpbuf[14];
				return;
			}

			// add numbers
			while (number && idx)
			{
				--idx;
				tmpbuf[idx] = (c8) ('0' + (number % 10));
				number /= 10;
			}

			*this = &tmpbuf[idx];
		}

		//! Constructor for copying a string from a pointer with a given length
		stringc::stringc(const c8* const c, u32 length) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			if (!c)
			{
				// correctly init the string to an empty one
				*this = "";
				return;
			}

			Allocated = Used = length + 1;
			Array = Allocator.allocate(Used); // new T[Used];

			for (u32 l = 0; l < length; ++l)
				Array[l] = (c8) c[l];

			Array[length] = 0;
		}

		//! Constructor for unicode strings
		stringc::stringc(const c8* const c) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			*this = c;
		}

		//! Destructor
		stringc::~stringc()
		{
			Monitor->enter();
			Allocator.deallocate(Array); // delete [] Array;
			Monitor->exit();

			if (Monitor)
				Monitor->drop();
		}

		//! Assignment operator
		stringc& stringc::operator=(const stringc& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			other.Monitor->enter();

			stringc& result = stringc::operator =(other.Array);

			other.Monitor->exit();

			return result;
		}

		//! Assignment operator for strings, ascii and unicode
		stringc& stringc::operator=(const c8* const c)
		{
			Monitor->enter();

			if (!c)
			{

				if (!Array)
				{
					Array = Allocator.allocate(1); //new T[1];
					Allocated = 1;
				}
				Used = 1;
				Array[0] = 0x0;

				Monitor->exit();
				return *this;
			}

			if ((void*) c == (void*) Array)
			{
				Monitor->exit();
				return *this;
			}

			u32 len = 0;
			const c8* p = c;
			do
			{
				++len;
			} while (*p++);

			// we'll keep the old string for a while, because the new
			// string could be a part of the current string.
			c8* oldArray = Array;

			Used = len;
			if (Used > Allocated)
			{
				Allocated = Used;
				Array = Allocator.allocate(Used); //new T[Used];
			}

			for (u32 l = 0; l < len; ++l)
				Array[l] = c[l];

			if (oldArray != Array)
				Allocator.deallocate(oldArray); // delete [] oldArray;

			Monitor->exit();
			return *this;
		}

		//! Append operator for other strings
		stringc stringc::operator+(const stringc& other) const
		{
			Monitor->enter();
			stringc result(*this);
			result.append(other);
			Monitor->exit();

			return result;
		}

		//! Append operator for strings, ascii and unicode
		stringc stringc::operator+(const c8* const c) const
		{
			Monitor->enter();
			stringc result(*this);
			result.append(c);
			Monitor->exit();

			return result;
		}

		//! Direct access operator
		c8& stringc::operator [](const u32 index)
		{
			Monitor->enter();

			// bad index
			IRR_ASSERT(index >= 0 && index < Used)

			c8& result = Array[index];

			Monitor->exit();

			return result;
		}

		//! Direct access operator
		const c8& stringc::operator [](const u32 index) const
		{
			Monitor->enter();

			// bad index
			IRR_ASSERT(index >= 0 && index < Used)

			const c8& result = Array[index];

			Monitor->exit();

			return result;
		}

		//! Equality operator
		bool stringc::operator ==(const stringc& other) const
		{
			if (this == &other)
				return true;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return stringc::operator==(other.Array);
		}

		//! Equality operator
		bool stringc::operator ==(const c8* const str) const
		{
			if (!str)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			Monitor->enter();

			u32 i;
			for (i = 0; Array[i] && str[i]; ++i)
				if (Array[i] != str[i])
				{
					Monitor->exit();
					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
					return false;
				}

			bool result = !Array[i] && !str[i];

			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Is smaller comparator
		bool stringc::operator <(const stringc& other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			Monitor->enter();

			for (u32 i = 0; Array[i] && other.Array[i]; ++i)
			{
				s32 diff = Array[i] - other.Array[i];
				if (diff)
				{
					Monitor->exit();
					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX
					return diff < 0;
				}
			}

			bool result = Used < other.Used;

			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Inequality operator
		bool stringc::operator !=(const c8* const str) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !(*this == str);
		}

		//! Inequality operator
		bool stringc::operator !=(const stringc& other) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !(*this == other);
		}

		//! Returns length of the string's content
		/** \return Length of the string's content in characters, excluding
		 the trailing NUL. */
		u32 stringc::size() const
		{
			Monitor->enter();
			u32 result = Used - 1;
			Monitor->exit();

			return result;
		}

		//! Return True if this string is empty. Otherwise return False.
		bool stringc::empty()
		{
			bool result = false;

			Monitor->enter();

			result = Used - 1 == 0;

			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Returns character string
		/** \return pointer to C-style NUL terminated string. */
		const c8* stringc::cStr() const
		{
			Monitor->enter();
			const c8* result = Array;
			Monitor->exit();

			return result;
		}

		//! Makes the string lower case.
		void stringc::makeLower()
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				Array[i] = SharedCoreUtils::getInstance().localeLower(Array[i]);

			Monitor->exit();
		}

		//! Makes the string upper case.
		void stringc::makeUpper()
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				Array[i] = SharedCoreUtils::getInstance().localeUpper(Array[i]);

			Monitor->exit();
		}

		//! Compares the strings ignoring case.
		bool stringc::equalsIgnoreCase(const stringc& other,
				const u32 sourcePos) const
		{
			if (this == &other)
				return true;

			Monitor->enter();
			other.Monitor->enter();

			IRR_ASSERT(sourcePos < Used);

			u32 i;
			for (i = 0; Array[sourcePos + i] && other.Array[i]; ++i)
				if (SharedCoreUtils::getInstance().localeLower(
						Array[sourcePos + i])
						!= SharedCoreUtils::getInstance().localeLower(
								other.Array[i]))
				{
					Monitor->exit();
					other.Monitor->exit();
					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
					return false;
				}

			bool result = Array[sourcePos + i] == 0 && other.Array[i] == 0;

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Compares the strings ignoring case.
		bool stringc::lowerIgnoreCase(const stringc& other) const
		{
			if (this == &other)
			{
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			Monitor->enter();
			other.Monitor->enter();

			for (u32 i = 0; Array[i] && other.Array[i]; ++i)
			{
				s32 diff = (s32) SharedCoreUtils::getInstance().localeLower(
						Array[i])
						- (s32) SharedCoreUtils::getInstance().localeLower(
								other.Array[i]);

				if (diff)
				{
					Monitor->exit();
					other.Monitor->exit();

					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
					return diff < 0;
				}
			}

			bool result = Used < other.Used;

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! compares the first n characters of the strings
		bool stringc::equalsn(const stringc& other, u32 n) const
		{
			if (this == &other)
				return true;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return stringc::equalsn(other.Array, n);
		}

		//! compares the first n characters of the strings
		bool stringc::equalsn(const c8* const str, u32 n) const
		{
			Monitor->enter();

			IRR_ASSERT(n < Used);

			if (!str)
			{
				Monitor->exit();
				_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
				return false;
			}

			u32 i;
			for (i = 0; Array[i] && str[i] && i < n; ++i)
				if (Array[i] != str[i])
				{
					Monitor->exit();
					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
					return false;
				}

			// if one (or both) of the strings was smaller then they
			// are only equal if they have the same length
			bool result = (i == n) || (Array[i] == 0 && str[i] == 0);
			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Appends a string to this string
		void stringc::append(const stringc& other)
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			--Used;
			u32 len = other.Used;

			if (Used + len > Allocated)
				reallocate(Used + len);

			for (u32 l = 0; l < len; ++l)
				Array[Used + l] = other.Array[l];

			Used += len;

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();
		}

		//! Appends a character to this string
		void stringc::append(c8 character)
		{
			Monitor->enter();

			if (Used + 1 > Allocated)
				reallocate(Used + 1);

			++Used;

			Array[Used - 2] = character;
			Array[Used - 1] = 0;

			Monitor->exit();
		}

		//! Appends a char string to this string
		void stringc::append(const c8* const other)
		{
			Monitor->enter();

			IRR_ASSERT(other != 0);

			u32 len = 0;
			const c8* p = other;
			while (*p)
			{
				++len;
				++p;
			}

			if (Used + len > Allocated)
				reallocate(Used + len);

			--Used;
			++len;

			for (u32 l = 0; l < len; ++l)
				Array[l + Used] = *(other + l);

			Used += len;

			Monitor->exit();
		}

		//! Appends a string of the length l to this string.
		void stringc::append(const stringc& other, u32 length)
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			IRR_ASSERT((other.Used - 1) > length);

			if (Used + length > Allocated)
				reallocate(Used + length);

			--Used;

			for (u32 l = 0; l < length; ++l)
				Array[l + Used] = other.Array[l];
			Used += length;

			// ensure proper termination
			Array[Used] = 0;
			++Used;

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();
		}

		//! finds next occurrence of character in string
		s32 stringc::findFirst(c8 c, u32 startPos) const
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			IRR_ASSERT(startPos < Used);

			for (u32 i = startPos; i < Used; ++i)
				if (Array[i] == c)
				{
					result = i;
					break;
				}

			Monitor->exit();

			return result;
		}

		//! finds last occurrence of character in string
		s32 stringc::findLast(c8 c) const
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			for (u32 i = Used - 1; i > 0; --i)
			{
				if (Array[i] == c)
				{
					result = i;
					break;
				}
			}

			Monitor->exit();

			return result;
		}

		//! finds another string in this string
		s32 stringc::find(const c8* const str, const u32 start) const
		{
			s32 result = IrrNotFound;

			Monitor->enter();

			IRR_ASSERT(str != 0);
			IRR_ASSERT(start < Used);

			if (!(*str))
			{
				Monitor->exit();
				return result;
			}

			u32 len = 0;

			while (str[len])
				++len;

			if (len > Used - 1)
			{
				Monitor->exit();
				return result;
			}

			for (u32 i = start; i < Used - len; ++i)
			{
				u32 j = 0;

				while (str[j] && Array[i + j] == str[j])
					++j;

				if (!str[j])
				{
					result = i;
					break;
				}
			}

			Monitor->exit();
			return result;
		}

		//! Returns a substring
		stringc stringc::subString(u32 begin, u32 length) const
		{
			stringc result;

			Monitor->enter();

			// no proper substring length
			IRR_ASSERT(length > 0);

			// or if start after string
			IRR_ASSERT(begin < (Used - 1));

			// clamp length to maximal value
			if ((length + begin) > (Used - 1))
				length = (Used - 1) - begin;

			result.reallocate(length + 1);

			for (u32 i = 0; i < length; ++i)
				result.Array[i] = Array[i + begin];

			result.Array[length] = 0;
			result.Used = result.Allocated;

			Monitor->exit();
			return result;
		}

		//! Appends a string to this string
		stringc& stringc::operator +=(const stringc& other)
		{
			append(other);
			return *this;
		}

		//! Appends a character to this string
		stringc& stringc::operator +=(c8 c)
		{
			append(c);
			return *this;
		}

		//! Appends a char string to this string
		stringc& stringc::operator +=(const c8* const c)
		{
			append(c);
			return *this;
		}

		//! Appends a string representation of a number to this string
		stringc& stringc::operator +=(const s32 i)
		{
			append(stringc(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		stringc& stringc::operator +=(const u32 i)
		{
			append(stringc(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		stringc& stringc::operator +=(const double i)
		{
			append(stringc(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		stringc& stringc::operator +=(const f32 i)
		{
			append(stringc(i));
			return *this;
		}

		//! Replaces all characters of a special type with another one
		void stringc::replace(c8 toReplace, c8 replaceWith)
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
			{
				if (Array[i] == toReplace)
				{
					Array[i] = replaceWith;
				}
			}

			Monitor->exit();
		}

		//! Removes characters from a string.
		void stringc::remove(c8 c)
		{
			Monitor->enter();

			u32 pos = 0;
			u32 found = 0;
			for (u32 i = 0; i < Used; ++i)
			{
				if (Array[i] == c)
				{
					++found;
					continue;
				}

				Array[pos++] = Array[i];
			}
			Used -= found;
			Array[Used] = 0;

			Monitor->exit();
		}

		//		//! Returns new string which trims this string.
		//		 string& string::trim(const string& whitespace)
		//		{
		//			Monitor->enter();
		//
		//			//for clear - use string::clear()
		//			IRR_ASSERT(this != &whitespace);
		//			//trim empty was
		//			IRR_ASSERT(Used - 1 > 0);
		//
		//			whitespace.Monitor->enter();
		//
		//			// find start and end of the substring without the specified characters
		//			const s32 begin = findFirstCharNotInList(whitespace.Array,
		//					whitespace.Used);
		//
		//			if (begin == irrNotFound)
		//			{
		//				Monitor->exit();
		//				return (*this = "");
		//			}
		//
		//			const s32 end = findLastCharNotInList(whitespace.Array,
		//					whitespace.Used);
		//
		//			string* result = new string;
		//
		//			(*result) = subString(begin, (end + 1) - begin);
		//
		//			Monitor->exit();
		//
		//			return *result;
		//		}

		//! Erases a character from the string.
		void stringc::erase(u32 index)
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index < Used)

			for (u32 i = index + 1; i < Used; ++i)
				Array[i - 1] = Array[i];

			--Used;

			Monitor->exit();
		}

		//! gets the last char of a string or null
		c8 stringc::lastChar() const
		{
			Monitor->enter();
			c8 result = Used > 1 ? Array[Used - 2] : 0;
			Monitor->exit();

			return result;
		}

		//! split string into parts.
		void stringc::split(ICollection<stringc>& ret, const c8* const c,
				u32 count, bool ignoreEmptyTokens, bool keepSeparators) const
		{
			IRR_ASSERT(c != 0);

			u32 lastpos = 0;
			bool lastWasSeparator = false;
			for (u32 i = 0; i < Used; ++i)
			{
				bool foundSeparator = false;
				for (u32 j = 0; j < count; ++j)
				{
					if (Array[i] == c[j])
					{
						if ((!ignoreEmptyTokens || i - lastpos != 0)
								&& !lastWasSeparator)
							ret.pushBack(stringc(&Array[lastpos], i - lastpos));
						foundSeparator = true;
						lastpos = (keepSeparators ? i : i + 1);
						break;
					}
				}
				lastWasSeparator = foundSeparator;
			}

			if ((Used - 1) > lastpos)
				ret.pushBack(stringc(&Array[lastpos], (Used - 1) - lastpos));
		}

		//! Reallocate the Array, make it bigger or smaller
		void stringc::reallocate(u32 newSize)
		{
			c8* oldArray = Array;

			Array = Allocator.allocate(newSize); //new T[newSize];
			Allocated = newSize;

			u32 amount = Used < newSize ? Used : newSize;
			for (u32 i = 0; i < amount; ++i)
				Array[i] = oldArray[i];

			if (Allocated < Used)
				Used = Allocated;

			Allocator.deallocate(oldArray); // delete [] old_Array;
		}

	} // namespace core
}  // namespace irrgame

