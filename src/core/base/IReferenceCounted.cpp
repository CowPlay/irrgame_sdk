/*
 * IReferenceCounted.cpp
 *
 *  Created on: Aug 14, 2012
 *      Author: gregorytkach
 */

#include "core/irrgamebase.h"
#include "threads/irrgameThread.h"
namespace irrgame
{

	//! Constructor.
	IReferenceCounted::IReferenceCounted() :
			DebugName(0), ReferenceCounter(1)
	{
//		s32 threadID = threads::irrgameThread::getCurrentThreadID();
//		ThreadsReferenceCounters.insert(threadID, 1);
	}

	//! Destructor.
	IReferenceCounted::~IReferenceCounted()
	{
	}

	//! Grabs the object. Increments the reference counter by one.
	/** Someone who calls grab() to an object, should later also
	 call drop() to it. If an object never gets as much drop() as
	 grab() calls, it will never be destroyed. The
	 IReferenceCounted class provides a basic reference counting
	 mechanism with its methods grab() and drop(). Most objects of
	 the Irrlicht Engine are derived from IReferenceCounted, and so
	 they are reference counted.

	 When you create an object in the Irrlicht engine, calling a
	 method which starts with 'create', an object is created, and
	 you get a pointer to the new object. If you no longer need the
	 object, you have to call drop(). This will destroy the object,
	 if grab() was not called in another part of you program,
	 because this part still needs the object. Note, that you only
	 need to call drop() to the object, if you created it, and the
	 method had a 'create' in it.

	 A simple example:

	 If you want to create a texture, you may want to call an
	 imaginable method IDriver::createTexture. You call
	 ITexture* texture = driver->createTexture(dimension2d<u32>(128, 128));
	 If you no longer need the texture, call texture->drop().
	 If you want to load a texture, you may want to call imaginable
	 method IDriver::loadTexture. You do this like
	 ITexture* texture = driver->loadTexture("example.jpg");
	 You will not have to drop the pointer to the loaded texture,
	 because the name of the method does not start with 'create'.
	 The texture is stored somewhere by the driver. */
	void IReferenceCounted::grab() const
	{
//		s32 threadID = threads::irrgameThread::getCurrentThreadID();

//		if (haveDependiesFromThread(threadID))
//		{
//			DictIntInt::Node* node = ThreadsReferenceCounters.find(threadID);
//			node->setValue(node->getValue() + 1);
//		}
//		else
//			ThreadsReferenceCounters.insert(threadID, 1);

		++ReferenceCounter;

	}

	//! Drops the object. Decrements the reference counter by one.
	/** The IReferenceCounted class provides a basic reference
	 counting mechanism with its methods grab() and drop(). Most
	 objects of the Irrlicht Engine are derived from
	 IReferenceCounted, and so they are reference counted.

	 When you create an object in the Irrlicht engine, calling a
	 method which starts with 'create', an object is created, and
	 you get a pointer to the new object. If you no longer need the
	 object, you have to call drop(). This will destroy the object,
	 if grab() was not called in another part of you program,
	 because this part still needs the object. Note, that you only
	 need to call drop() to the object, if you created it, and the
	 method had a 'create' in it.

	 A simple example:

	 If you want to create a texture, you may want to call an
	 imaginable method IDriver::createTexture. You call
	 ITexture* texture = driver->createTexture(dimension2d<u32>(128, 128));
	 If you no longer need the texture, call texture->drop().
	 If you want to load a texture, you may want to call imaginable
	 method IDriver::loadTexture. You do this like
	 ITexture* texture = driver->loadTexture("example.jpg");
	 You will not have to drop the pointer to the loaded texture,
	 because the name of the method does not start with 'create'.
	 The texture is stored somewhere by the driver.
	 \return True, if the object was deleted. */
	bool IReferenceCounted::drop() const
	{
		// someone is doing bad reference counting.
		IRR_ASSERT(ReferenceCounter > 0)

//		s32 threadID = threads::irrgameThread::getCurrentThreadID();

//		if (haveDependiesFromThread(threadID))
//		{
//			DictIntInt::Node* node = ThreadsReferenceCounters.find(threadID);
//			node->setValue(node->getValue() - 1);

		--ReferenceCounter;
//		}
//		else
//		{
//			//something wrong
//			IRR_ASSERT(false);
//		}

		if (!ReferenceCounter)
		{
			delete this;
			return true;
		}

		return false;
	}

	//! Get the reference count.
	/** \return Current value of the reference counter. */
	s32 IReferenceCounted::getReferenceCount() const
	{
		return ReferenceCounter;
	}

	//! Return True if object have dependies(reference count more 0) from specify thread.
	//! Otherwise return False.
	//@ param0 - thread id
	bool IReferenceCounted::haveDependiesFromThread(s32 threadID) const
	{
//		return ThreadsReferenceCounters.find(threadID) != 0;
		return false;
	}

	//! Returns the debug name of the object.
	/** The Debugname may only be set and changed by the object
	 itself. This method should only be used in Debug mode.
	 \return Returns a string, previously set by setDebugName(); */
	const c8* IReferenceCounted::getDebugName() const
	{
		return DebugName;
	}

	//! Sets the debug name of the object.
	/** The Debugname may only be set and changed by the object
	 itself. This method should only be used in Debug mode.
	 \param newName: New debug name to set. */
	void IReferenceCounted::setDebugName(const c8* newName)
	{
		DebugName = newName;
	}
}

