/*
 * EXmlNodeTypes.h
 *
 *  Created on: Aug 7, 2012
 *      Author: gregorytkach
 */

#ifndef EXMLNODETYPES_H_
#define EXMLNODETYPES_H_

namespace irrgame
{
	namespace io
	{
		//! Enumeration for all xml nodes which are parsed by IrrXMLReader
		enum EXML_NODE_TYPE
		{
			//! No xml node. This is usually the node if you did not read anything yet.
			EXNT_NONE,

			//! An xml element such as &lt;foo&gt;
			EXNT_ELEMENT,

			//! End of an xml element such as &lt;/foo&gt;
			EXNT_ELEMENT_END,

			//! Text within an xml element: &lt;foo&gt; this is the text. &lt;foo&gt;
			EXNT_TEXT,

			//! An xml comment like &lt;!-- I am a comment --&gt; or a DTD definition.
			EXNT_COMMENT,

			//! An xml cdata section like &lt;![CDATA[ this is some CDATA ]]&gt;
			EXNT_CDATA,

			//! Unknown element.
			EXNT_UNKNOWN
		};
	}
}

#endif /* EXMLNODETYPES_H_ */
