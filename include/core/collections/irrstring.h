// Copyright (C) 2002-2009 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine" and the "irrXML" project.
// For conditions of distribution and use, see copyright notice in irrlicht.h and irrXML.h

#ifndef __IRR_STRING_H_INCLUDED__
#define __IRR_STRING_H_INCLUDED__

#include "core/base/baseTypes.h"
#include "core/base/irrAllocator.h"
#include "ICollection.h"

namespace irrgame
{
	namespace threads
	{
		class irrgameMonitor;
	}  // namespace threads

	namespace core
	{
		//! Very simple unicode threadsafe string class with some useful features.
		/** so you can assign Unicode to this string*/
		class stringc
		{
			public:
				//! Returns empty string
				static const stringc& getEmpty(void);

			public:

				//! Default constructor
				stringc();
				//! Copy constructor
				stringc(const stringc& other);

				//! Constructs a string from a float
				explicit stringc(const double number);
				//! Constructs a string from an int
				explicit stringc(s32 number);
				//! Constructs a string from an unsigned int
				explicit stringc(u32 number);

				//! Constructor for copying a string from a pointer with a given length
				stringc(const c8* const c, u32 length);
				//! Constructor for unicode and ascii strings
				stringc(const c8* const c);

				//! Destructor
				virtual ~stringc();

				//! Assignment operator
				stringc& operator=(const stringc& other);
				//! Assignment operator for strings, ascii and unicode
				stringc& operator=(const c8* const c);

				//! Append operator for other strings
				stringc operator+(const stringc& other) const;
				//! Append operator for strings, ascii and unicode
				stringc operator+(const c8* const c) const;

				//! Direct access operator
				c8& operator [](const u32 index);
				//! Direct access operator
				const c8& operator [](const u32 index) const;

				//! Equality operator
				bool operator ==(const stringc& other) const;
				//! Equality operator
				bool operator ==(const c8* const str) const;

				//! Is smaller comparator
				bool operator <(const stringc& other) const;

				//! Inequality operator
				bool operator !=(const c8* const str) const;
				//! Inequality operator
				bool operator !=(const stringc& other) const;

				//! Returns length of the string's content
				/** \return Length of the string's content in characters, excluding
				 the trailing NUL. */
				u32 size() const;

				//! Return True if this string is empty. Otherwise return False.
				bool empty();

				//! Returns character string
				/** \return pointer to C-style NUL terminated string. */
				const c8* cStr() const;

				//! Makes the string lower case.
				void makeLower();
				//! Makes the string upper case.
				void makeUpper();

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \param sourcePos: where to start to compare in the string
				 \return True if the strings are equal ignoring case. */
				bool equalsIgnoreCase(const stringc& other, const u32 sourcePos =
						0) const;

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if this string is smaller ignoring case. */
				bool lowerIgnoreCase(const stringc& other) const;

				//! compares the first n characters of the strings
				/** \param other Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				bool equalsn(const stringc& other, u32 n) const;
				//! compares the first n characters of the strings
				/** \param str Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				bool equalsn(const c8* const str, u32 n) const;

				//! Appends a string to this string
				/** \param other: String to append. */
				void append(const stringc& other);
				//! Appends a string of the length l to this string.
				/** \param other: other String to append to this string.
				 \param length: How much characters of the other string to add to this one. */
				void append(const stringc& other, u32 length);
				//! Appends a character to this string
				/** \param character: Character to append. */
				void append(c8 character);
				//! Appends a char string to this string
				/** \param other: Char string to append. */
				void append(const c8* const other);

				//! finds next occurrence of character in string
				/** \param c: Character to search for.
				 \param startPos: Position in string to start searching.
				 \return Position where the character has been found,
				 or irrNotFound if not found. */
				s32 findFirst(c8 c, u32 startPos = 0) const;

				//! finds last occurrence of character in string
				/** \param c: Character to search for.
				 \return Position where the character has been found,
				 or irrNotFound if not found. */
				s32 findLast(c8 c) const;

				//! finds another string in this string
				/** \param str: Another string
				 \param start: Start position of the search
				 \return Positions where the string has been found,
				 or -1 if not found. */
				s32 find(const c8* const str, const u32 start = 0) const;

				//! Returns a substring
				/** \param begin: Start of substring.
				 \param length: Length of substring. */
				stringc subString(u32 begin, u32 length) const;

				//! Appends a string to this string
				/** \param other String to append. */
				stringc& operator +=(const stringc& other);
				//! Appends a character to this string
				/** \param c Character to append. */
				stringc& operator +=(c8 c);
				//! Appends a char string to this string
				/** \param c Char string to append. */
				stringc& operator +=(const c8* const c);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringc& operator +=(const s32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringc& operator +=(const u32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringc& operator +=(const double i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringc& operator +=(const f32 i);

				//! Replaces all characters of a specify type with another one
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
				void split(ICollection<stringc>& ret, const c8* const c,
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

	}
// end namespace core
}// end namespace irr

#endif

