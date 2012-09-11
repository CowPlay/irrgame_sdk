// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __IRR_STRING_H_INCLUDED__
#define __IRR_STRING_H_INCLUDED__

#include "core/base/irrAllocator.h"
#include "core/math/irrMath.h"
#include "core/collections/ICollection.h"
#include "core/coreutil.h"
#include "threads/irrgameMonitor.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace irrgame
{
	namespace core
	{
		//! Very simple unicode threadsafe string class with some useful features.
		/** so you can assign Unicode to this string*/
		class string
		{
			public:
				//! Returns empty string
				static const string& getEmpty(void);

			public:

				//! Default constructor
				string();
				//! Copy constructor
				string(const string& other);

				//! Constructs a string from a float
				explicit string(const double number);
				//! Constructs a string from an int
				explicit string(s32 number);
				//! Constructs a string from an unsigned int
				explicit string(u32 number);

				//! Constructor for copying a string from a pointer with a given length
				string(const c8* const c, u32 length);
				//! Constructor for unicode and ascii strings
				string(const c8* const c);

				//! Destructor
				virtual ~string();

				//! Assignment operator
				string& operator=(const string& other);
				//! Assignment operator for strings, ascii and unicode
				string& operator=(const c8* const c);

				//! Append operator for other strings
				string operator+(const string& other) const;
				//! Append operator for strings, ascii and unicode
				string operator+(const c8* const c) const;

				//! Direct access operator
				c8& operator [](const u32 index);
				//! Direct access operator
				const c8& operator [](const u32 index) const;

				//! Equality operator
				bool operator ==(const string& other) const;
				//! Equality operator
				bool operator ==(const c8* const str) const;

				//! Is smaller comparator
				bool operator <(const string& other) const;

				//! Inequality operator
				bool operator !=(const c8* const str) const;
				//! Inequality operator
				bool operator !=(const string& other) const;

				//! Returns length of the string's content
				/** \return Length of the string's content in characters, excluding
				 the trailing NUL. */
				u32 size() const;

				//! Return True if this string is empty. Otherwise return False.
				bool empty();

				//! Return True if this string have only whitespaces. Otherwise returns False.
				bool blank();

				//! Returns character string
				/** \return pointer to C-style NUL terminated string. */
				const c8* cStr() const;

				//! Makes the string lower case.
				void makeLower();
				//! Makes the string upper case.
				void makeUpper();

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if the strings are equal ignoring case. */
				bool equalsIgnoreCase(const string& other) const;
				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \param sourcePos: where to start to compare in the string
				 \return True if the strings are equal ignoring case. */
				bool equalsSubstringIgnoreCase(const string& other,
						const u32 sourcePos = 0) const;

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if this string is smaller ignoring case. */
				bool lowerIgnoreCase(const string& other) const;

				//! compares the first n characters of the strings
				/** \param other Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				bool equalsn(const string& other, u32 n) const;
				//! compares the first n characters of the strings
				/** \param str Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				bool equalsn(const c8* const str, u32 n) const;

				//! Appends a string to this string
				/** \param other: String to append. */
				void append(const string& other);
				//! Appends a string of the length l to this string.
				/** \param other: other String to append to this string.
				 \param length: How much characters of the other string to add to this one. */
				void append(const string& other, u32 length);
				//! Appends a character to this string
				/** \param character: Character to append. */
				void append(c8 character);
				//! Appends a char string to this string
				/** \param other: Char string to append. */
				void append(const c8* const other);

				//! finds first occurrence of character in string
				/** \param c: Character to search for.
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findFirst(c8 c) const;
				//! finds last occurrence of character in string
				/** \param c: Character to search for.
				 \param start: start to search reverse ( default = -1, on end )
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findLast(c8 c, s32 start = -1) const;

				//! finds first occurrence of a character of a list in string
				/** \param c: List of characters to find. For example if the method
				 should find the first occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				s32 findFirstChar(const c8* const c, u32 count) const;
				//! finds last occurrence of a character of a list in string
				/** \param c: List of strings to find. For example if the method
				 should find the last occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				s32 findLastChar(const c8* const c, u32 count) const;

				//! Finds first position of a character not in a given list.
				/** \param c: List of characters not to find. For example if the method
				 should find the first occurrence of a character not 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findFirstCharNotInList(const c8* const c, u32 count) const;
				//! Finds last position of a character not in a given list.
				/** \param c: List of characters not to find. For example if the method
				 should find the first occurrence of a character not 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findLastCharNotInList(const c8* const c, u32 count) const;

				//! finds next occurrence of character in string
				/** \param c: Character to search for.
				 \param startPos: Position in string to start searching.
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findNext(c8 c, u32 startPos) const;

				//! finds another string in this string
				/** \param str: Another string
				 \param start: Start position of the search
				 \return Positions where the string has been found,
				 or -1 if not found. */
				s32 find(const c8* const str, const u32 start = 0) const;

				//! Returns a substring
				/** \param begin: Start of substring.
				 \param length: Length of substring. */
				string subString(u32 begin, s32 length) const;

				//! Appends a string to this string
				/** \param other String to append. */
				string& operator +=(const string& other);
				//! Appends a character to this string
				/** \param c Character to append. */
				string& operator +=(c8 c);
				//! Appends a char string to this string
				/** \param c Char string to append. */
				string& operator +=(const c8* const c);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				string& operator +=(const s32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				string& operator +=(const u32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				string& operator +=(const double i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				string& operator +=(const f32 i);

				//! Replaces all characters of a special type with another one
				/** \param toReplace Character to replace.
				 \param replaceWith Character replacing the old one. */
				void replace(c8 toReplace, c8 replaceWith);

				//! Removes characters from a string.
				/** \param c: Character to remove. */
				void remove(c8 c);

				//! Returns new string which trims this string.
				/** Returns new string which not contains the specified characters (by default, Latin-1 whitespace)
				 from the begining and the end of the string. */
//				string& trim(const string& whitespace = " \t\n\r");
//
//
//
				//! Erases a character from the string.
				/** May be slow, because all elements
				 following after the erased element have to be copied.
				 \param index: Index of element to be erased. */
				void erase(u32 index);

				//! verify the existing string.
				void validate();

				//! gets the last char of a string or null
				c8 lastChar() const;

				//! split string into parts.
				/** This method will split a string at certain delimiter characters
				 into the container passed in as reference.
				 \param ret The result container
				 \param c C-style string of delimiter characters
				 \param count Number of delimiter characters
				 \param ignoreEmptyTokens Flag to avoid empty substrings in the result
				 container. If two delimiters occur without a character in between, an
				 empty substring would be placed in the result. If this flag is set,
				 only non-empty strings are stored.
				 \param keepSeparators Flag which allows to add the separator to the
				 result string. If this flag is true, the concatenation of the
				 substrings results in the original string. Otherwise, only the
				 characters between the delimiters are returned.
				 */
				void split(ICollection<string>& ret, const c8* const c,
						u32 count = 1, bool ignoreEmptyTokens = true,
						bool keepSeparators = false) const;

			private:

				//! Reallocate the Array, make it bigger or smaller
				void reallocate(u32 newSize);

			private:
				//--- member variables
				c8* Array;
				u32 Allocated;
				u32 Used;
				irrAllocator<c8> Allocator;
				threads::irrgameMonitor* Monitor;
		};

		//! Returns empty string
		inline const string& string::getEmpty(void)
		{
			static const string empty;
			return empty;
		}

		//! Default constructor
		inline string::string() :
				Array(0), Allocated(1), Used(1), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			Array = Allocator.allocate(1); // new T[1];
			Array[0] = 0x0;
		}

		//! Copy constructor
		inline string::string(const string& other) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
			*this = other;
		}

		//! Constructs a string from a float
		inline string::string(const double number) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			c8 tmpbuf[255];
			snprintf(tmpbuf, 255, "%0.6f", number);
			*this = tmpbuf;
		}

		//! Constructs a string from an int
		inline string::string(s32 number) :
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
		inline string::string(u32 number) :
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
		inline string::string(const c8* const c, u32 length) :
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
		inline string::string(const c8* const c) :
				Array(0), Allocated(0), Used(0), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();

			*this = c;
		}

		//! Destructor
		inline string::~string()
		{
			Monitor->enter();
			Allocator.deallocate(Array); // delete [] Array;
			Monitor->exit();

			if (Monitor)
				Monitor->drop();
		}

		//! Assignment operator
		inline string& string::operator=(const string& other)
		{
			if (this == &other)
				return *this;

			other.Monitor->enter();

			string& result = string::operator =(other.Array);

			other.Monitor->exit();

			return result;
		}

		//! Assignment operator for strings, ascii and unicode
		inline string& string::operator=(const c8* const c)
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
		inline string string::operator+(const string& other) const
		{
			return string::operator +(other.Array);
		}

		//! Append operator for strings, ascii and unicode
		inline string string::operator+(const c8* const c) const
		{
			Monitor->enter();
			string result(*this);
			result.append(c);
			Monitor->exit();

			return result;
		}

		//! Direct access operator
		inline c8& string::operator [](const u32 index)
		{
			Monitor->enter();

			// bad index
			IRR_ASSERT(index >= 0 && index < Used)

			c8& result = Array[index];

			Monitor->exit();

			return result;
		}

		//! Direct access operator
		inline const c8& string::operator [](const u32 index) const
		{
			Monitor->enter();

			// bad index
			IRR_ASSERT(index >= 0 && index<Used)

			const c8& result = Array[index];

			Monitor->exit();

			return result;
		}

		//! Equality operator
		inline bool string::operator ==(const string& other) const
		{
			if (this == &other)
				return true;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return string::operator==(other.Array);
		}

		//! Equality operator
		inline bool string::operator ==(const c8* const str) const
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
		inline bool string::operator <(const string& other) const
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
		inline bool string::operator !=(const c8* const str) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !(*this == str);
		}

		//! Inequality operator
		inline bool string::operator !=(const string& other) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return !(*this == other);
		}

		//! Returns length of the string's content
		/** \return Length of the string's content in characters, excluding
		 the trailing NUL. */
		inline u32 string::size() const
		{
			Monitor->enter();
			u32 result = Used - 1;
			Monitor->exit();

			return result;
		}

		//! Return True if this string is empty. Otherwise return False.
		inline bool string::empty()
		{
			bool result = false;

			Monitor->enter();

			result = Used - 1 > 0;

			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Return True if this string have only whitespaces. Otherwise returns False.
		inline bool string::blank()
		{
			IRR_ASSERT(false);
			bool result = false;

			Monitor->enter();

			//TODO implement it

			Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Returns character string
		/** \return pointer to C-style NUL terminated string. */
		inline const c8* string::cStr() const
		{
			Monitor->enter();
			const c8* result = Array;
			Monitor->exit();

			return result;
		}

		//! Makes the string lower case.
		inline void string::makeLower()
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				Array[i] = localeLower(Array[i]);

			Monitor->exit();
		}

		//! Makes the string upper case.
		inline void string::makeUpper()
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				Array[i] = localeUpper(Array[i]);

			Monitor->exit();
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \return True if the strings are equal ignoring case. */
		inline bool string::equalsIgnoreCase(const string& other) const
		{
			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return equalsSubstringIgnoreCase(other, 0);
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \param sourcePos: where to start to compare in the string
		 \return True if the strings are equal ignoring case. */
		inline bool string::equalsSubstringIgnoreCase(const string& other,
				const u32 sourcePos) const
		{
			if (this == &other)
				return true;

			Monitor->enter();
			other.Monitor->enter();

			IRR_ASSERT(sourcePos < Used);

			u32 i;
			for (i = 0; Array[sourcePos + i] && other[i]; ++i)
				if (localeLower(Array[sourcePos + i]) != localeLower(other[i]))
				{
					Monitor->exit();
					other.Monitor->exit();
					_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
					return false;
				}

			bool result = Array[sourcePos + i] == 0 && other[i] == 0;

			Monitor->exit();
			other.Monitor->exit();

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return result;
		}

		//! Compares the strings ignoring case.
		inline bool string::lowerIgnoreCase(const string& other) const
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
				s32 diff = (s32) localeLower(Array[i])
						- (s32) localeLower(other.Array[i]);

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
		inline bool string::equalsn(const string& other, u32 n) const
		{
			if (this == &other)
				return true;

			_IRR_IMPLEMENT_MANAGED_MARSHALLING_BUGFIX;
			return string::equalsn(other.Array, n);
		}

		//! compares the first n characters of the strings
		inline bool string::equalsn(const c8* const str, u32 n) const
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
		inline void string::append(const string& other)
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
		inline void string::append(c8 character)
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
		inline void string::append(const c8* const other)
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
		inline void string::append(const string& other, u32 length)
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			IRR_ASSERT((other.Used-1) > length);

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

		//! finds first occurrence of character in string
		inline s32 string::findFirst(c8 c) const
		{
			s32 result = -1;

			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				if (Array[i] == c)
				{
					result = i;
					break;
				}

			Monitor->exit();

			return result;
		}

		//! finds last occurrence of character in string
		inline s32 string::findLast(c8 c, s32 start) const
		{
			s32 result = -1;

			Monitor->enter();

			start = core::clamp(start < 0 ? (s32) (Used) - 1 : start, 0,
					(s32) (Used) - 1);
			for (s32 i = start; i >= 0; --i)
				if (Array[i] == c)
				{
					result = i;
					break;
				}

			Monitor->exit();

			return result;
		}

		//! finds first occurrence of a character of a list in string
		inline s32 string::findFirstChar(const c8* const c, u32 count) const
		{
			s32 result = -1;

			Monitor->enter();

			IRR_ASSERT(c != 0);

			for (u32 i = 0; i < Used; ++i)
				for (u32 j = 0; j < count; ++j)
					if (Array[i] == c[j])
					{
						result = i;
						break;
					}

			Monitor->exit();

			return result;
		}

		//! finds last occurrence of a character of a list in string
		inline s32 string::findLastChar(const c8* const c, u32 count) const
		{
			s32 result = -1;

			Monitor->enter();

			IRR_ASSERT(c != 0);

			for (s32 i = Used - 1; i >= 0; --i)
				for (u32 j = 0; j < count; ++j)
					if (Array[i] == c[j])
					{
						result = i;
						break;
					}

			Monitor->exit();

			return result;
		}

		//! Finds first position of a character not in a given list.
		inline s32 string::findFirstCharNotInList(const c8* const c,
				u32 count) const
		{
			s32 result = -1;

			Monitor->enter();

			for (u32 i = 0; i < Used - 1; ++i)
			{
				u32 j;
				for (j = 0; j < count; ++j)
					if (Array[i] == c[j])
						break;

				if (j == count)
				{
					result = i;
					break;
				}
			}

			Monitor->exit();

			return result;
		}

		//! Finds last position of a character not in a given list.
		inline s32 string::findLastCharNotInList(const c8* const c,
				u32 count) const
		{
			s32 result = -1;

			Monitor->enter();

			for (s32 i = (s32) (Used - 2); i >= 0; --i)
			{
				u32 j;
				for (j = 0; j < count; ++j)
					if (Array[i] == c[j])
						break;

				if (j == count)
				{
					result = i;
					break;
				}
			}

			Monitor->exit();

			return result;
		}

		//! finds next occurrence of character in string
		inline s32 string::findNext(c8 c, u32 startPos) const
		{
			s32 result = irrNotFound;

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

		//! finds another string in this string
		inline s32 string::find(const c8* const str, const u32 start) const
		{
			s32 result = irrNotFound;

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
		inline string string::subString(u32 begin, s32 length) const
		{
			string result;

			Monitor->enter();

			// if start after string
			IRR_ASSERT(length <= 0);
			// or no proper substring length
			IRR_ASSERT(begin >= (Used - 1));

			// clamp length to maximal value
			if ((length + begin) > (Used - 1))
				length = (Used - 1) - begin;

			result.reallocate(length + 1);

			for (s32 i = 0; i < length; ++i)
				result.Array[i] = Array[i + begin];

			result.Array[length] = 0;
			result.Used = result.Allocated;

			Monitor->exit();
			return result;
		}

		//! Appends a string to this string
		inline string& string::operator +=(const string& other)
		{
			append(other);
			return *this;
		}

		//! Appends a character to this string
		inline string& string::operator +=(c8 c)
		{
			append(c);
			return *this;
		}

		//! Appends a char string to this string
		inline string& string::operator +=(const c8* const c)
		{
			append(c);
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline string& string::operator +=(const s32 i)
		{
			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline string& string::operator +=(const u32 i)
		{
			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline string& string::operator +=(const double i)
		{
			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline string& string::operator +=(const f32 i)
		{
			append(string(i));
			return *this;
		}

		//! Replaces all characters of a special type with another one
		inline void string::replace(c8 toReplace, c8 replaceWith)
		{
			Monitor->enter();

			for (u32 i = 0; i < Used; ++i)
				if (Array[i] == toReplace)
					Array[i] = replaceWith;

			Monitor->exit();
		}

		//! Removes characters from a string.
		inline void string::remove(c8 c)
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
//		inline string& string::trim(const string& whitespace)
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
		inline void string::erase(u32 index)
		{
			Monitor->enter();

			// access violation
			IRR_ASSERT(index >= 0 && index < Used)

			for (u32 i = index + 1; i < Used; ++i)
				Array[i - 1] = Array[i];

			--Used;

			Monitor->exit();
		}

		//! verify the existing string.
		inline void string::validate()
		{
			Monitor->enter();

			// terminate on existing null
			for (u32 i = 0; i < Allocated; ++i)
			{
				if (Array[i] == 0)
				{
					Used = i + 1;
					Monitor->exit();
					return;
				}
			}

			// terminate
			if (Allocated > 0)
			{
				Used = Allocated - 1;
				Array[Used] = 0;
			}
			else
			{
				Used = 0;
			}

			Monitor->exit();
		}

		//! gets the last char of a string or null
		inline c8 string::lastChar() const
		{
			Monitor->enter();
			c8 result = Used > 1 ? Array[Used - 2] : 0;
			Monitor->exit();

			return result;
		}

		//! split string into parts.
		inline void string::split(ICollection<string>& ret, const c8* const c,
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
							ret.pushBack(string(&Array[lastpos], i - lastpos));
						foundSeparator = true;
						lastpos = (keepSeparators ? i : i + 1);
						break;
					}
				}
				lastWasSeparator = foundSeparator;
			}

			if ((Used - 1) > lastpos)
				ret.pushBack(string(&Array[lastpos], (Used - 1) - lastpos));
		}

		//! Reallocate the Array, make it bigger or smaller
		inline void string::reallocate(u32 newSize)
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
	}
// end namespace core
}// end namespace irr

#endif

