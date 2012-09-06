// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __IRR_STRING_H_INCLUDED__
#define __IRR_STRING_H_INCLUDED__

#include "core/base/irrAllocator.h"
#include "core/math/irrMath.h"
#include "core/collections/ICollection.h"
#include "core/coreutil.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

namespace irrgame
{
	namespace core
	{
		//! Very simple unicode string class with some useful features.
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
				virtual string& operator=(const string& other);
				//! Assignment operator for strings, ascii and unicode
				virtual string& operator=(const c8* const c);

				//! Append operator for other strings
				virtual string operator+(const string& other) const;
				//! Append operator for strings, ascii and unicode
				string operator+(const c8* const c) const;

				//! Direct access operator
				virtual c8& operator [](const u32 index);
				//! Direct access operator
				virtual const c8& operator [](const u32 index) const;

				//! Equality operator
				virtual bool operator ==(const string& other) const;
				//! Equality operator
				virtual bool operator ==(const c8* const str) const;

				//! Is smaller comparator
				virtual bool operator <(const string& other) const;

				//! Inequality operator
				virtual bool operator !=(const c8* const str) const;
				//! Inequality operator
				virtual bool operator !=(const string& other) const;

				//! Returns length of the string's content
				/** \return Length of the string's content in characters, excluding
				 the trailing NUL. */
				virtual u32 size() const;

				//! Returns character string
				/** \return pointer to C-style NUL terminated string. */
				virtual const c8* c_str() const;

				//! Makes the string lower case.
				virtual void make_lower();
				//! Makes the string upper case.
				virtual void make_upper();

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if the strings are equal ignoring case. */
				virtual bool equals_ignore_case(const string& other) const;
				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \param sourcePos: where to start to compare in the string
				 \return True if the strings are equal ignoring case. */
				virtual bool equals_substring_ignore_case(const string& other,
						const u32 sourcePos = 0) const;

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if this string is smaller ignoring case. */
				virtual bool lower_ignore_case(const string& other) const;

				//! compares the first n characters of the strings
				/** \param other Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				virtual bool equalsn(const string& other, u32 n) const;
				//! compares the first n characters of the strings
				/** \param str Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				virtual bool equalsn(const c8* const str, u32 n) const;

				//! Appends a string to this string
				/** \param other: String to append. */
				virtual void append(const string& other);
				//! Appends a string of the length l to this string.
				/** \param other: other String to append to this string.
				 \param length: How much characters of the other string to add to this one. */
				virtual void append(const string& other, u32 length);
				//! Appends a character to this string
				/** \param character: Character to append. */
				virtual void append(c8 character);
				//! Appends a char string to this string
				/** \param other: Char string to append. */
				virtual void append(const c8* const other);

				//! Reserves some memory.
				/** \param count: Amount of characters to reserve. */
				void reserve(u32 count);

				//! finds first occurrence of character in string
				/** \param c: Character to search for.
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findFirst(c8 c) const;

				//! finds first occurrence of a character of a list in string
				/** \param c: List of characters to find. For example if the method
				 should find the first occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				s32 findFirstChar(const c8* const c, u32 count) const;

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

				//! finds last occurrence of character in string
				/** \param c: Character to search for.
				 \param start: start to search reverse ( default = -1, on end )
				 \return Position where the character has been found,
				 or -1 if not found. */
				s32 findLast(c8 c, s32 start = -1) const;

				//! finds last occurrence of a character of a list in string
				/** \param c: List of strings to find. For example if the method
				 should find the last occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				s32 findLastChar(const c8* const c, u32 count) const;

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

				//! Appends a character to this string
				/** \param c Character to append. */
				string& operator +=(c8 c);
				//! Appends a char string to this string
				/** \param c Char string to append. */
				string& operator +=(const c8* const c);
				//! Appends a string to this string
				/** \param other String to append. */
				string& operator +=(const string& other);
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
				//! Removes a string from the string.
				/** \param toRemove: String to remove. */
				void remove(const string toRemove);

				//! Removes characters from a string.
				/** \param characters: Characters to remove. */
				void removeChars(const string & characters);

				//! Trims the string.
				/** Removes the specified characters (by default, Latin-1 whitespace)
				 from the begining and the end of the string. */
				string& trim(const string & whitespace = " \t\n\r");

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
				 into the container passed in as reference. The type of the container
				 has to be given as template parameter. It must provide a push_back and
				 a size method.
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
				 \return The number of resulting substrings
				 */
				u32 split(ICollection<string>& ret, const c8* const c,
						u32 count = 1, bool ignoreEmptyTokens = true,
						bool keepSeparators = false) const;

			private:

				//! Reallocate the array, make it bigger or smaller
				void reallocate(u32 new_size);

			protected:
				//--- member variables
				c8* array;
				u32 allocated;
				u32 used;
				irrAllocator<c8> allocator;
		};

		//! Returns empty string
		inline const string& string::getEmpty(void)
		{
			static const string empty;
			return empty;
		}

		//! Default constructor
		inline string::string() :
				array(0), allocated(1), used(1)
		{
			array = allocator.allocate(1); // new T[1];
			array[0] = 0x0;
		}

		//! Copy constructor
		inline string::string(const string& other) :
				array(0), allocated(0), used(0)
		{
			*this = other;
		}

		//! Constructs a string from a float
		inline string::string(const double number) :
				array(0), allocated(0), used(0)
		{
			c8 tmpbuf[255];
			snprintf(tmpbuf, 255, "%0.6f", number);
			*this = tmpbuf;
		}

		//! Constructs a string from an int
		inline string::string(s32 number) :
				array(0), allocated(0), used(0)
		{
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
				array(0), allocated(0), used(0)
		{
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
				array(0), allocated(0), used(0)
		{
			if (!c)
			{
				// correctly init the string to an empty one
				*this = "";
				return;
			}

			allocated = used = length + 1;
			array = allocator.allocate(used); // new T[used];

			for (u32 l = 0; l < length; ++l)
				array[l] = (c8) c[l];

			array[length] = 0;
		}

		//! Constructor for unicode strings
		inline string::string(const c8* const c) :
				array(0), allocated(0), used(0)
		{
			*this = c;
		}

		//! Destructor
		inline string::~string()
		{
			allocator.deallocate(array); // delete [] array;
		}

		//! Assignment operator
		inline string& string::operator=(const string& other)
		{
			if (this == &other)
				return *this;

			used = other.size() + 1;
			if (used > allocated)
			{
				allocator.deallocate(array); // delete [] array;
				allocated = used;
				array = allocator.allocate(used); //new T[used];
			}

			const c8* p = other.c_str();
			for (u32 i = 0; i < used; ++i, ++p)
				array[i] = *p;

			return *this;
		}

		//! Assignment operator for strings, ascii and unicode
		inline string& string::operator=(const c8* const c)
		{
			if (!c)
			{
				if (!array)
				{
					array = allocator.allocate(1); //new T[1];
					allocated = 1;
				}
				used = 1;
				array[0] = 0x0;
				return *this;
			}

			if ((void*) c == (void*) array)
				return *this;

			u32 len = 0;
			const c8* p = c;
			do
			{
				++len;
			} while (*p++);

			// we'll keep the old string for a while, because the new
			// string could be a part of the current string.
			c8* oldArray = array;

			used = len;
			if (used > allocated)
			{
				allocated = used;
				array = allocator.allocate(used); //new T[used];
			}

			for (u32 l = 0; l < len; ++l)
				array[l] = (c8) c[l];

			if (oldArray != array)
				allocator.deallocate(oldArray); // delete [] oldArray;

			return *this;
		}

		//! Append operator for other strings
		inline string string::operator+(const string& other) const
		{
			return string::operator +(other.c_str());
		}

		//! Append operator for strings, ascii and unicode
		inline string string::operator+(const c8* const c) const
		{
			string str(*this);
			str.append(c);

			return str;
		}

		//! Direct access operator
		inline c8& string::operator [](const u32 index)
		{
			// bad index
			IRR_ASSERT(index >= 0 && index<used)

			return array[index];
		}

		//! Direct access operator
		inline const c8& string::operator [](const u32 index) const
		{
			// bad index
			IRR_ASSERT(index >= 0 && index<used)

			return array[index];
		}

		//! Equality operator
		inline bool string::operator ==(const string& other) const
		{
			if (this == &other)
				return true;

			return string::operator==(other.c_str());
		}

		//! Equality operator
		inline bool string::operator ==(const c8* const str) const
		{
			if (!str)
				return false;

			u32 i;
			for (i = 0; array[i] && str[i]; ++i)
				if (array[i] != str[i])
					return false;

			return !array[i] && !str[i];
		}

		//! Is smaller comparator
		inline bool string::operator <(const string& other) const
		{
			if (this == &other)
				return false;

			for (u32 i = 0; array[i] && other.array[i]; ++i)
			{
				s32 diff = array[i] - other.array[i];
				if (diff)
					return diff < 0;
			}

			return used < other.used;
		}

		//! Inequality operator
		inline bool string::operator !=(const c8* const str) const
		{
			return !(*this == str);
		}

		//! Inequality operator
		inline bool string::operator !=(const string& other) const
		{
			return !(*this == other);
		}

		//! Returns length of the string's content
		/** \return Length of the string's content in characters, excluding
		 the trailing NUL. */
		inline u32 string::size() const
		{
			return used - 1;
		}

		//! Returns character string
		/** \return pointer to C-style NUL terminated string. */
		inline const c8* string::c_str() const
		{
			return array;
		}

		//! Makes the string lower case.
		inline void string::make_lower()
		{
			for (u32 i = 0; i < used; ++i)
				array[i] = locale_lower(array[i]);
		}

		//! Makes the string upper case.
		inline void string::make_upper()
		{
			for (u32 i = 0; i < used; ++i)
				array[i] = locale_upper(array[i]);
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \return True if the strings are equal ignoring case. */
		inline bool string::equals_ignore_case(const string& other) const
		{
			return string::equals_substring_ignore_case(other, 0);
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \param sourcePos: where to start to compare in the string
		 \return True if the strings are equal ignoring case. */
		inline bool string::equals_substring_ignore_case(const string& other,
				const u32 sourcePos) const
		{
			IRR_ASSERT(sourcePos < used);

			if (this == &other)
				return true;

			u32 i;
			for (i = 0; array[sourcePos + i] && other[i]; ++i)
				if (locale_lower(array[sourcePos + i])
						!= locale_lower(other[i]))
					return false;

			return array[sourcePos + i] == 0 && other[i] == 0;
		}

		//! Compares the strings ignoring case.
		inline bool string::lower_ignore_case(const string& other) const
		{
			if (this == &other)
				return false;

			for (u32 i = 0; array[i] && other.array[i]; ++i)
			{
				s32 diff = (s32) locale_lower(array[i])
						- (s32) locale_lower(other.array[i]);
				if (diff)
					return diff < 0;
			}

			return used < other.used;
		}

		//! compares the first n characters of the strings
		inline bool string::equalsn(const string& other, u32 n) const
		{
			if (this == &other)
				return true;

			return string::equalsn(other.c_str(), n);
		}

		//! compares the first n characters of the strings
		inline bool string::equalsn(const c8* const str, u32 n) const
		{
			IRR_ASSERT(n < used);

			if (!str)
				return false;

			u32 i;
			for (i = 0; array[i] && str[i] && i < n; ++i)
				if (array[i] != str[i])
					return false;

			// if one (or both) of the strings was smaller then they
			// are only equal if they have the same length
			return (i == n) || (array[i] == 0 && str[i] == 0);
		}

		//! Appends a string to this string
		inline void string::append(const string& other)
		{
			--used;
			u32 len = other.size() + 1;

			if (used + len > allocated)
				string::reallocate(used + len);

			for (u32 l = 0; l < len; ++l)
				array[used + l] = other.array[l];

			used += len;
		}

		//! Appends a character to this string
		inline void string::append(c8 character)
		{
			if (used + 1 > allocated)
				string::reallocate(used + 1);

			++used;

			array[used - 2] = character;
			array[used - 1] = 0;
		}

		//! Appends a char string to this string
		inline void string::append(const c8* const other)
		{
			if (!other)
				return;

			u32 len = 0;
			const c8* p = other;
			while (*p)
			{
				++len;
				++p;
			}

			if (used + len > allocated)
				string::reallocate(used + len);

			--used;
			++len;

			for (u32 l = 0; l < len; ++l)
				array[l + used] = *(other + l);

			used += len;
		}

		//! Appends a string of the length l to this string.
		inline void string::append(const string& other, u32 length)
		{
			if (other.size() < length)
			{
				string::append(other);
				return;
			}

			if (used + length > allocated)
				string::reallocate(used + length);

			--used;

			for (u32 l = 0; l < length; ++l)
				array[l + used] = other.array[l];
			used += length;

			// ensure proper termination
			array[used] = 0;
			++used;
		}

		//! Reserves some memory.
		inline void string::reserve(u32 count)
		{
			IRR_ASSERT(count > allocated);

			string::reallocate(count);
		}

		//! finds first occurrence of character in string
		inline s32 string::findFirst(c8 c) const
		{
			for (u32 i = 0; i < used; ++i)
				if (array[i] == c)
					return i;

			return -1;
		}

		//! finds first occurrence of a character of a list in string
		inline s32 string::findFirstChar(const c8* const c, u32 count) const
		{
			if (!c)
				return -1;

			for (u32 i = 0; i < used; ++i)
				for (u32 j = 0; j < count; ++j)
					if (array[i] == c[j])
						return i;

			return -1;
		}

		//! Finds first position of a character not in a given list.
		inline s32 string::findFirstCharNotInList(const c8* const c,
				u32 count) const
		{
			for (u32 i = 0; i < used - 1; ++i)
			{
				u32 j;
				for (j = 0; j < count; ++j)
					if (array[i] == c[j])
						break;

				if (j == count)
					return i;
			}

			return -1;
		}

		//! Finds last position of a character not in a given list.
		inline s32 string::findLastCharNotInList(const c8* const c,
				u32 count) const
		{
			for (s32 i = (s32) (used - 2); i >= 0; --i)
			{
				u32 j;
				for (j = 0; j < count; ++j)
					if (array[i] == c[j])
						break;

				if (j == count)
					return i;
			}

			return -1;
		}

		//! finds next occurrence of character in string
		inline s32 string::findNext(c8 c, u32 startPos) const
		{
			for (u32 i = startPos; i < used; ++i)
				if (array[i] == c)
					return i;

			return -1;
		}

		//! finds last occurrence of character in string
		inline s32 string::findLast(c8 c, s32 start) const
		{
			start = core::clamp(start < 0 ? (s32) (used) - 1 : start, 0,
					(s32) (used) - 1);
			for (s32 i = start; i >= 0; --i)
				if (array[i] == c)
					return i;

			return -1;
		}

		//! finds last occurrence of a character of a list in string
		inline s32 string::findLastChar(const c8* const c, u32 count) const
		{
			if (!c)
				return -1;

			for (s32 i = used - 1; i >= 0; --i)
				for (u32 j = 0; j < count; ++j)
					if (array[i] == c[j])
						return i;

			return -1;
		}

		//! finds another string in this string
		inline s32 string::find(const c8* const str, const u32 start) const
		{
			if (str && *str)
			{
				u32 len = 0;

				while (str[len])
					++len;

				if (len > used - 1)
					return -1;

				for (u32 i = start; i < used - len; ++i)
				{
					u32 j = 0;

					while (str[j] && array[i + j] == str[j])
						++j;

					if (!str[j])
						return i;
				}
			}

			return -1;
		}

		//! Returns a substring
		inline string string::subString(u32 begin, s32 length) const
		{
			// if start after string
			// or no proper substring length
			if ((length <= 0) || (begin >= size()))
				return string("");
			// clamp length to maximal value
			if ((length + begin) > size())
				length = size() - begin;

			string o;
			o.reserve(length + 1);

			for (s32 i = 0; i < length; ++i)
				o.array[i] = array[i + begin];

			o.array[length] = 0;
			o.used = o.allocated;

			return o;
		}

		//! Appends a character to this string
		inline string& string::operator +=(c8 c)
		{
			string::append(c);
			return *this;
		}

		//! Appends a char string to this string
		inline string& string::operator +=(const c8* const c)
		{
			string::append(c);
			return *this;
		}

		//! Appends a string to this string
		inline string& string::operator +=(const string& other)
		{
			return string::operator +=(other.c_str());
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
			for (u32 i = 0; i < used; ++i)
				if (array[i] == toReplace)
					array[i] = replaceWith;
		}

		//! Removes characters from a string.
		inline void string::remove(c8 c)
		{
			u32 pos = 0;
			u32 found = 0;
			for (u32 i = 0; i < used; ++i)
			{
				if (array[i] == c)
				{
					++found;
					continue;
				}

				array[pos++] = array[i];
			}
			used -= found;
			array[used] = 0;
		}

		//! Removes a string from the string.
		inline void string::remove(const string toRemove)
		{
			u32 size = toRemove.size();
			u32 pos = 0;
			u32 found = 0;
			for (u32 i = 0; i < used; ++i)
			{
				u32 j = 0;
				while (j < size)
				{
					if (array[i + j] != toRemove[j])
						break;
					++j;
				}
				if (j == size)
				{
					found += size;
					i += size - 1;
					continue;
				}

				array[pos++] = array[i];
			}
			used -= found;
			array[used] = 0;
		}

		//! Removes characters from a string.
		inline void string::removeChars(const string & characters)
		{
			u32 pos = 0;
			u32 found = 0;
			for (u32 i = 0; i < used; ++i)
			{
				// Don't use characters.findFirst as it finds the \0,
				// causing used to become incorrect.
				bool docontinue = false;
				for (u32 j = 0; j < characters.size(); ++j)
				{
					if (characters[j] == array[i])
					{
						++found;
						docontinue = true;
						break;
					}
				}
				if (docontinue)
					continue;

				array[pos++] = array[i];
			}
			used -= found;
			array[used] = 0;
		}

		//! Trims the string.
		inline string& string::trim(const string& whitespace)
		{
			// find start and end of the substring without the specified characters
			const s32 begin = findFirstCharNotInList(whitespace.c_str(),
					whitespace.used);
			if (begin == -1)
				return (*this = "");

			const s32 end = findLastCharNotInList(whitespace.c_str(),
					whitespace.used);

			return (*this = subString(begin, (end + 1) - begin));
		}

		//! Erases a character from the string.
		inline void string::erase(u32 index)
		{
			// access violation
			IRR_ASSERT(index >= 0 && index < used)

			for (u32 i = index + 1; i < used; ++i)
				array[i - 1] = array[i];

			--used;
		}

		//! verify the existing string.
		inline void string::validate()
		{
			// terminate on existing null
			for (u32 i = 0; i < allocated; ++i)
			{
				if (array[i] == 0)
				{
					used = i + 1;
					return;
				}
			}

			// terminate
			if (allocated > 0)
			{
				used = allocated - 1;
				array[used] = 0;
			}
			else
			{
				used = 0;
			}
		}

		//! gets the last char of a string or null
		//TODO: return last char when used = 1
		inline c8 string::lastChar() const
		{
			return used > 1 ? array[used - 2] : 0;
		}

		//! split string into parts.
		inline u32 string::split(ICollection<string>& ret, const c8* const c,
				u32 count, bool ignoreEmptyTokens, bool keepSeparators) const
		{
			if (!c)
				return 0;

			const u32 oldSize = ret.size();
			u32 lastpos = 0;
			bool lastWasSeparator = false;
			for (u32 i = 0; i < used; ++i)
			{
				bool foundSeparator = false;
				for (u32 j = 0; j < count; ++j)
				{
					if (array[i] == c[j])
					{
						if ((!ignoreEmptyTokens || i - lastpos != 0)
								&& !lastWasSeparator)
							ret.push_back(string(&array[lastpos], i - lastpos));
						foundSeparator = true;
						lastpos = (keepSeparators ? i : i + 1);
						break;
					}
				}
				lastWasSeparator = foundSeparator;
			}
			if ((used - 1) > lastpos)
				ret.push_back(string(&array[lastpos], (used - 1) - lastpos));
			return ret.size() - oldSize;
		}

		//! Reallocate the array, make it bigger or smaller
		inline void string::reallocate(u32 new_size)
		{
			c8* old_array = array;

			array = allocator.allocate(new_size); //new T[new_size];
			allocated = new_size;

			u32 amount = used < new_size ? used : new_size;
			for (u32 i = 0; i < amount; ++i)
				array[i] = old_array[i];

			if (allocated < used)
				used = allocated;

			allocator.deallocate(old_array); // delete [] old_array;
		}
	}
// end namespace core
}// end namespace irr

#endif

