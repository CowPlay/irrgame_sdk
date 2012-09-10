/*
 * stringsafe.h
 *
 *  Created on: Sep 5, 2012
 *      Author: gregorytkach
 */

#ifndef STRINGSAFE_H_
#define STRINGSAFE_H_

#include "core/collections/string.h"
#include "threads/irrgameMonitor.h"

namespace irrgame
{
	namespace core
	{
		class stringsafe: public string
		{
			public:
				//! Default constructor
				stringsafe();
				//! Copy constructor
				stringsafe(const stringsafe& other);

				//! Constructs a threadsafe string from unsafe string
				explicit stringsafe(const string& other);
				//! Constructs a threadsafe string from a float
				explicit stringsafe(const double number);
				//! Constructs a threadsafe string from an int
				explicit stringsafe(s32 number);
				//! Constructs a threadsafe string from an unsigned int
				explicit stringsafe(u32 number);

				//! Constructor for copying a string from a pointer with a given length
				stringsafe(const c8* const c, u32 length);
				//! Constructor for unicode and ascii strings
				stringsafe(const c8* const c);

				//! Destructor
				virtual ~stringsafe();

				//! Assignment operator
				virtual stringsafe& operator=(const stringsafe& other);
				//! Assignment operator for unicode unsafe strings
				virtual stringsafe& operator=(const string& other);
				//! Assignment operator for unicode strings
				virtual stringsafe& operator=(const c8* const c);

				//! Append operator for other strings
				virtual stringsafe operator+(const stringsafe& other) const;
				//! Append operator for strings, ascii and unicode
				stringsafe operator+(const c8* const c) const;

				//! Direct access operator
				virtual c8& operator [](const u32 index);
				//! Direct access operator
				virtual const c8& operator [](const u32 index) const;

				//! Equality operator
				virtual bool operator ==(const stringsafe& other) const;
				//! Equality operator
				virtual bool operator ==(const c8* const str) const;

				//! Is smaller comparator
				virtual bool operator <(const stringsafe& other) const;

				//! Inequality operator
				virtual bool operator !=(const c8* const str) const;
				//! Inequality operator
				virtual bool operator !=(const stringsafe& other) const;

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
				virtual bool equals_ignore_case(const stringsafe& other) const;
				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \param sourcePos: where to start to compare in the string
				 \return True if the strings are equal ignoring case. */
				virtual bool equals_substring_ignore_case(
						const stringsafe& other, const u32 sourcePos = 0) const;

				//! Compares the strings ignoring case.
				/** \param other: Other string to compare.
				 \return True if this string is smaller ignoring case. */
				virtual bool lower_ignore_case(const stringsafe& other) const;

				//! compares the first n characters of the strings
				/** \param other Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				virtual bool equalsn(const stringsafe& other, u32 n) const;
				//! compares the first n characters of the strings
				/** \param str Other string to compare.
				 \param n Number of characters to compare
				 \return True if the n first characters of both strings are equal. */
				virtual bool equalsn(const c8* const str, u32 n) const;

				//! Appends a string to this string
				/** \param other: String to append. */
				virtual void append(const stringsafe& other);
				//! Appends a string of the length l to this string.
				/** \param other: other String to append to this string.
				 \param length: How much characters of the other string to add to this one. */
				virtual void append(const stringsafe& other, u32 length);
				//! Appends a character to this string
				/** \param character: Character to append. */
				virtual void append(c8 character);
				//! Appends a char string to this string
				/** \param other: Char string to append. */
				virtual void append(const c8* const other);

				//! Reserves some memory.
				/** \param count: Amount of characters to reserve. */
				virtual void reserve(u32 count);

				//! finds first occurrence of character in string
				/** \param c: Character to search for.
				 \return Position where the character has been found,
				 or -1 if not found. */
				virtual s32 findFirst(c8 c) const;
				//! finds last occurrence of character in string
				/** \param c: Character to search for.
				 \param start: start to search reverse ( default = -1, on end )
				 \return Position where the character has been found,
				 or -1 if not found. */
				virtual s32 findLast(c8 c, s32 start = -1) const;

				//! finds first occurrence of a character of a list in string
				/** \param c: List of characters to find. For example if the method
				 should find the first occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				virtual s32 findFirstChar(const c8* const c, u32 count) const;
				//! finds last occurrence of a character of a list in string
				/** \param c: List of strings to find. For example if the method
				 should find the last occurrence of 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where one of the characters has been found,
				 or -1 if not found. */
				virtual s32 findLastChar(const c8* const c, u32 count) const;

				//! Finds first position of a character not in a given list.
				/** \param c: List of characters not to find. For example if the method
				 should find the first occurrence of a character not 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where the character has been found,
				 or -1 if not found. */
				virtual s32 findFirstCharNotInList(const c8* const c,
						u32 count) const;
				//! Finds last position of a character not in a given list.
				/** \param c: List of characters not to find. For example if the method
				 should find the first occurrence of a character not 'a' or 'b', this parameter should be "ab".
				 \param count: Amount of characters in the list. Usually,
				 this should be strlen(c)
				 \return Position where the character has been found,
				 or -1 if not found. */
				virtual s32 findLastCharNotInList(const c8* const c,
						u32 count) const;

				//! finds next occurrence of character in string
				/** \param c: Character to search for.
				 \param startPos: Position in string to start searching.
				 \return Position where the character has been found,
				 or -1 if not found. */
				virtual s32 findNext(c8 c, u32 startPos) const;

				//! finds another string in this string
				/** \param str: Another string
				 \param start: Start position of the search
				 \return Positions where the string has been found,
				 or -1 if not found. */
				virtual s32 find(const c8* const str,
						const u32 start = 0) const;

				//! Appends a string to this string
				/** \param other String to append. */
				stringsafe& operator +=(const stringsafe& other);
				//! Appends a character to this string
				/** \param c Character to append. */
				stringsafe& operator +=(c8 c);
				//! Appends a char string to this string
				/** \param c Char string to append. */
				stringsafe& operator +=(const c8* const c);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringsafe& operator +=(const s32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringsafe& operator +=(const u32 i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringsafe& operator +=(const double i);
				//! Appends a string representation of a number to this string
				/** \param i Number to append. */
				stringsafe& operator +=(const f32 i);

				//! Replaces all characters of a special type with another one
				/** \param toReplace Character to replace.
				 \param replaceWith Character replacing the old one. */
				virtual void replace(c8 toReplace, c8 replaceWith);

				//! Removes characters from a string.
				/** \param c: Character to remove. */
				virtual void remove(c8 c);

				//! Trims the string.
				/** Removes the specified characters (by default, Latin-1 whitespace)
				 from the begining and the end of the string. */
				virtual string& trim(const string& whitespace = " \t\n\r");

				//! Erases a character from the string.
				/** May be slow, because all elements
				 following after the erased element have to be copied.
				 \param index: Index of element to be erased. */
				virtual void erase(u32 index);

				//! verify the existing string.
				virtual void validate();

				//! gets the last char of a string or null
				virtual c8 lastChar() const;

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
				virtual u32 split(ICollection<stringsafe>& ret,
						const c8* const c, u32 count = 1,
						bool ignoreEmptyTokens = true, bool keepSeparators =
								false) const;

			protected:
				threads::irrgameMonitor* Monitor;
		};

//		//! Default constructor
//		inline stringsafe::stringsafe() :
//				string(), Monitor(0)
//		{
//			Monitor = threads::createIrrgameMonitor();
//		}

//		//! Copy constructor
//		inline stringsafe::stringsafe(const stringsafe& other) :
//				Monitor(0)
//		{
//			*this = other;
//		}

//		//! Constructor for unicode and ascii strings
//		inline stringsafe::stringsafe(const c8* const c) :
//				Monitor(0)
//		{
//			*this = c;
//		}
//
//		//! Constructs a threadsafe string from unsafe string
//		inline stringsafe::stringsafe(const string& other) :
//				Monitor(0)
//		{
//			*this = other.c_str();
//		}

//		//! Constructs a string from a float
//		inline stringsafe::stringsafe(const double number) :
//				string(number), Monitor(0)
//		{
//			Monitor = threads::createIrrgameMonitor();
//		}

//		//! Constructs a string from an int
//		inline stringsafe::stringsafe(s32 number) :
//				string(number), Monitor(0)
//		{
//			Monitor = threads::createIrrgameMonitor();
//		}
//
//		//! Constructs a string from an unsigned int
//		inline stringsafe::stringsafe(u32 number) :
//				string(number), Monitor(0)
//		{
//			Monitor = threads::createIrrgameMonitor();
//		}
//
//		//! Constructor for copying a string from a pointer with a given length
//		inline stringsafe::stringsafe(const c8* const c, u32 length) :
//				string(c, length), Monitor(0)
//		{
//			Monitor = threads::createIrrgameMonitor();
//		}
//
//		//! Destructor
//		inline stringsafe::~stringsafe()
//		{
//			if (Monitor)
//				Monitor->drop();
//		}

		//! Assignment operator
		inline stringsafe& stringsafe::operator=(const stringsafe& other)
		{
			//handle self-assignment
			if (this == &other)
				return *this;

			if (Monitor)
				Monitor->drop();

			other.Monitor->enter();

			(*this) = static_cast<stringsafe&>(string::operator=(other));
			this->Monitor = threads::createIrrgameMonitor();

			other.Monitor->exit();

			return (*this);
		}

		//! Assignment operator for strings, ascii and unicode
		inline stringsafe& stringsafe::operator=(const c8* const c)
		{
			//handle self-assignment
			if ((void*) c == (void*) array)
				return *this;

			if (Monitor)
				Monitor->drop();

			stringsafe other(c);
			(*this) = static_cast<stringsafe&>(string::operator=(other));
			this->Monitor = threads::createIrrgameMonitor();

			return (*this);
		}

		//! Append operator for other strings
		inline stringsafe stringsafe::operator+(const stringsafe& other) const
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			stringsafe str(string::operator +(other).c_str());

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();

			return str;
		}

		//! Append operator for strings, ascii and unicode
		//TODO: check result destruct or not
		inline stringsafe stringsafe::operator+(const c8* const c) const
		{
			Monitor->enter();
			stringsafe result(string::operator +(c).c_str());
			Monitor->exit();

			return result;
		}

		//! Direct access operator
		inline c8& stringsafe::operator [](const u32 index)
		{
			Monitor->enter();
			c8& result = string::operator [](index);
			Monitor->exit();

			return result;
		}

		//! Direct access operator
		inline const c8& stringsafe::operator [](const u32 index) const
		{
			Monitor->enter();
			const c8& result = string::operator [](index);
			Monitor->exit();

			return result;
		}

		//! Equality operator
		inline bool stringsafe::operator ==(const c8* const str) const
		{
			Monitor->enter();
			bool result = string::operator ==(str);
			Monitor->exit();

			return result;
		}

		//! Equality operator
		inline bool stringsafe::operator ==(const stringsafe& other) const
		{
			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::operator ==(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Is smaller comparator
		inline bool stringsafe::operator <(const stringsafe& other) const
		{
			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::operator <(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Inequality operator
		inline bool stringsafe::operator !=(const c8* const str) const
		{
			Monitor->enter();
			bool result = string::operator!=(str);
			Monitor->exit();

			return result;
		}

		//! Inequality operator
		inline bool stringsafe::operator !=(const stringsafe& other) const
		{
			if (this == &other)
				return false;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::operator!=(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Returns length of the string's content
		/** \return Length of the string's content in characters, excluding
		 the trailing NUL. */
		inline u32 stringsafe::size() const
		{
			Monitor->enter();
			u32 result = string::size();
			Monitor->exit();

			return result;
		}

		//! Returns character string
		/** \return pointer to C-style NUL terminated string. */
		inline const c8* stringsafe::c_str() const
		{
			Monitor->enter();
			const c8* result = string::c_str();
			Monitor->exit();

			return result;
		}

		//! Makes the string lower case.
		inline void stringsafe::make_lower()
		{
			Monitor->enter();
			string::make_lower();
			Monitor->exit();
		}

		//! Makes the string upper case.
		inline void stringsafe::make_upper()
		{
			Monitor->enter();
			string::make_upper();
			Monitor->exit();
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \return True if the strings are equal ignoring case. */
		inline bool stringsafe::equals_ignore_case(
				const stringsafe& other) const
		{
			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::equals_ignore_case(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \param sourcePos: where to start to compare in the string
		 \return True if the strings are equal ignoring case. */
		inline bool stringsafe::equals_substring_ignore_case(
				const stringsafe& other, const u32 sourcePos) const
		{
			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::equals_substring_ignore_case(other,
					sourcePos);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! Compares the strings ignoring case.
		/** \param other: Other string to compare.
		 \return True if this string is smaller ignoring case. */
		inline bool stringsafe::lower_ignore_case(const stringsafe& other) const
		{
			if (this == &other)
				return false;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::lower_ignore_case(other);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! compares the first n characters of the strings
		/** \param other Other string to compare.
		 \param n Number of characters to compare
		 \return True if the n first characters of both strings are equal. */
		inline bool stringsafe::equalsn(const stringsafe& other, u32 n) const
		{
			if (this == &other)
				return true;

			other.Monitor->enter();
			Monitor->enter();

			bool result = string::equalsn(other, n);

			other.Monitor->exit();
			Monitor->exit();

			return result;
		}

		//! compares the first n characters of the strings
		inline bool stringsafe::equalsn(const c8* const str, u32 n) const
		{
			Monitor->enter();
			bool result = string::equalsn(str, n);
			Monitor->exit();

			return result;
		}

		//! Appends a string to this string
		inline void stringsafe::append(const stringsafe& other)
		{
			Monitor->enter();
			string::append(other);
			Monitor->exit();
		}

		//! Appends a string of the length l to this string.
		inline void stringsafe::append(const stringsafe& other, u32 length)
		{
			bool selfAppending = false;

			//handle self-appending
			if (this == &other)
				selfAppending = true;

			if (!selfAppending)
				other.Monitor->enter();
			Monitor->enter();

			string::append(other, length);

			if (!selfAppending)
				other.Monitor->exit();
			Monitor->exit();
		}

		//! Appends a character to this string
		inline void stringsafe::append(c8 character)
		{
			Monitor->enter();
			string::append(character);
			Monitor->exit();
		}

		//! Appends a char string to this string
		inline void stringsafe::append(const c8* const other)
		{
			Monitor->enter();
			string::append(other);
			Monitor->exit();
		}

//		//! Reserves some memory.
//		inline void stringsafe::reserve(u32 count)
//		{
//			Monitor->enter();
//			string::reserve(count);
//			Monitor->exit();
//		}

		//! finds first occurrence of character in string
		inline s32 stringsafe::findFirst(c8 c) const
		{
			Monitor->enter();
			s32 result = string::findFirst(c);
			Monitor->exit();

			return result;
		}

		//! finds last occurrence of character in string
		inline s32 stringsafe::findLast(c8 c, s32 start) const
		{
			Monitor->enter();
			s32 result = string::findLast(c);
			Monitor->exit();

			return result;
		}

		//! finds first occurrence of a character of a list in string
		inline s32 stringsafe::findFirstChar(const c8* const c, u32 count) const
		{
			Monitor->enter();
			s32 result = string::findFirstChar(c, count);
			Monitor->exit();

			return result;
		}

		//! finds last occurrence of a character of a list in string
		inline s32 stringsafe::findLastChar(const c8* const c, u32 count) const
		{
			Monitor->enter();
			s32 result = string::findLastChar(c, count);
			Monitor->exit();

			return result;
		}

		//! Finds first position of a character not in a given list.
		inline s32 stringsafe::findFirstCharNotInList(const c8* const c,
				u32 count) const
		{
			Monitor->enter();
			s32 result = string::findFirstCharNotInList(c, count);
			Monitor->exit();

			return result;
		}

		//! Finds last position of a character not in a given list.
		inline s32 stringsafe::findLastCharNotInList(const c8* const c,
				u32 count) const
		{
			Monitor->enter();
			s32 result = string::findLastCharNotInList(c, count);
			Monitor->exit();

			return result;
		}

		//! finds next occurrence of character in string
		inline s32 stringsafe::findNext(c8 c, u32 startPos) const
		{
			Monitor->enter();
			s32 result = string::findNext(c, startPos);
			Monitor->exit();

			return result;
		}

		//! finds another string in this string
		inline s32 stringsafe::find(const c8* const str, const u32 start) const
		{
			Monitor->enter();
			s32 result = string::find(str, start);
			Monitor->exit();

			return result;
		}

//		//! Appends a string to this string
//		inline stringsafe& stringsafe::operator +=(const stringsafe& other)
//		{
//			bool selfAppending = false;
//
//			//handle self-appending
//			if (this == &other)
//				selfAppending = true;
//
//			if (!selfAppending)
//				other.Monitor->enter();
//			Monitor->enter();
//
//			stringsafe result = stringsafe(string::operator+=(other.c_str()));
//
//			if (!selfAppending)
//				other.Monitor->exit();
//			Monitor->exit();
//
//			return result;
//		}

		//! Appends a character to this string
		inline stringsafe& stringsafe::operator +=(c8 c)
		{
//			string::append(c);
			return *this;
		}

		//! Appends a char string to this string
		inline stringsafe& stringsafe::operator +=(const c8* const c)
		{
//			string::append(c);
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline stringsafe& stringsafe::operator +=(const s32 i)
		{
//			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline stringsafe& stringsafe::operator +=(const u32 i)
		{
//			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline stringsafe& stringsafe::operator +=(const double i)
		{
//			append(string(i));
			return *this;
		}

		//! Appends a string representation of a number to this string
		inline stringsafe& stringsafe::operator +=(const f32 i)
		{
//			append(string(i));
			return *this;
		}

		//! Replaces all characters of a special type with another one
		inline void stringsafe::replace(c8 toReplace, c8 replaceWith)
		{
			Monitor->enter();
			string::replace(toReplace, replaceWith);
			Monitor->exit();
		}

		//! Removes characters from a string.
		inline void stringsafe::remove(c8 c)
		{
			Monitor->enter();
			string::remove(c);
			Monitor->exit();
		}

//		//! Trims the string.
//		inline string& stringsafe::trim(const stringsafe& whitespace)
//		{
//			// find start and end of the substring without the specified characters
//			const s32 begin = findFirstCharNotInList(whitespace.array,
//					whitespace.used);
//			if (begin == -1)
//				return (*this = "");
//
//			const s32 end = findLastCharNotInList(whitespace.array,
//					whitespace.used);
//
//			return (*this = string::subString(begin, (end + 1) - begin));
//		}

		//! Erases a character from the string.
		inline void stringsafe::erase(u32 index)
		{
			// access violation
			IRR_ASSERT(index >= 0 && index < used)

			for (u32 i = index + 1; i < used; ++i)
				array[i - 1] = array[i];

			--used;
		}

		//! verify the existing string.
		inline void stringsafe::validate()
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
		inline c8 stringsafe::lastChar() const
		{
			return used > 1 ? array[used - 2] : 0;
		}

		//! split string into parts.
		inline u32 stringsafe::split(ICollection<stringsafe>& ret,
				const c8* const c, u32 count, bool ignoreEmptyTokens,
				bool keepSeparators) const
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
							ret.pushBack(stringsafe(&array[lastpos], i - lastpos));
						foundSeparator = true;
						lastpos = (keepSeparators ? i : i + 1);
						break;
					}
				}
				lastWasSeparator = foundSeparator;
			}
			if ((used - 1) > lastpos)
				ret.pushBack(stringsafe(&array[lastpos], (used - 1) - lastpos));
			return ret.size() - oldSize;
		}

//		//! Reallocate the array, make it bigger or smaller
//		inline void stringsafe::reallocate(u32 new_size)
//		{
//			c8* old_array = array;
//
//			array = allocator.allocate(new_size); //new T[new_size];
//			allocated = new_size;
//
//			u32 amount = used < new_size ? used : new_size;
//			for (u32 i = 0; i < amount; ++i)
//				array[i] = old_array[i];
//
//			if (allocated < used)
//				used = allocated;
//
//			allocator.deallocate(old_array); // delete [] old_array;
//		}

	}		// end namespace core
} // end namespace irrgame

#endif /* STRINGSAFE_H_ */
