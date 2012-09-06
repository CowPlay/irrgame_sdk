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

				//! Constructor for unicode and ascii strings
				stringsafe(const c8* const c);

				//! Constructs a string from a float
				explicit stringsafe(const double number);

				//! Constructs a string from an int
				explicit stringsafe(s32 number);

				//! Constructs a string from an unsigned int
				explicit stringsafe(u32 number);

				//! Constructor for copying a string from a pointer with a given length
				stringsafe(const c8* const c, u32 length);

				//! Destructor
				virtual ~stringsafe();

				//! Assignment operator
				virtual stringsafe& operator=(const stringsafe& other);

				//! Assignment operator for strings, ascii and unicode
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
				virtual bool operator ==(const c8* const str) const;

				//! Equality operator
				virtual bool operator ==(const stringsafe& other) const;

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

				//! Appends a character to this string
				/** \param character: Character to append. */
				virtual void append(c8 character);

				//! Appends a char string to this string
				/** \param other: Char string to append. */
				virtual void append(const c8* const other);

				//! Appends a string to this string
				/** \param other: String to append. */
				virtual void append(const stringsafe& other);

				//! Appends a string of the length l to this string.
				/** \param other: other String to append to this string.
				 \param length: How much characters of the other string to add to this one. */
				virtual void append(const stringsafe& other, u32 length);

			protected:
				threads::irrgameMonitor* Monitor;
		};

		//! Default constructor
		inline stringsafe::stringsafe() :
				string(), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Copy constructor
		inline stringsafe::stringsafe(const stringsafe& other) :
				Monitor(0)
		{
			*this = other;
		}

		//! Constructor for unicode and ascii strings
		inline stringsafe::stringsafe(const c8* const c)
		{
			*this = c;
		}

		//! Constructs a string from a float
		inline stringsafe::stringsafe(const double number) :
				string(number), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructs a string from an int
		inline stringsafe::stringsafe(s32 number) :
				string(number), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructs a string from an unsigned int
		inline stringsafe::stringsafe(u32 number) :
				string(number), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Constructor for copying a string from a pointer with a given length
		inline stringsafe::stringsafe(const c8* const c, u32 length) :
				string(c, length), Monitor(0)
		{
			Monitor = threads::createIrrgameMonitor();
		}

		//! Destructor
		inline stringsafe::~stringsafe()
		{
			if (Monitor)
				Monitor->drop();
		}

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

			(*this) = static_cast<stringsafe&>(string::operator=(c));
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

	}		// end namespace core
} // end namespace irrgame

#endif /* STRINGSAFE_H_ */
