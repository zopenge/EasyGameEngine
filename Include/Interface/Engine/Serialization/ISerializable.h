#pragma once

namespace EGE {

class ISerializable : public IObject {
public:
	//!	Import properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Import(ISerializableNode* node) PURE;
	//!	Export properties.
	//!	@param		node	The serializable node.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool Export(ISerializableNode* node) const PURE;

	//!	Import properties from stream.
	//!	@param		streamReader	The stream reader.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ImportFromStream(IStreamReader* streamReader) PURE;
	//!	Export properties to stream.
	//!	@param		streamWriter	The stream writer.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToStream(IStreamWriter* streamWriter) const PURE;
};

} // namespace EGE