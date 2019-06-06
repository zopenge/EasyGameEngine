#pragma once

namespace EGE
{

/// <summary>
/// The resource object interface.
/// </summary>
class IResourceObject : public IObject
{
public:
	//!	Set the resource name.
	//!	@param		name	The resource name.
	//!	@return		none.
	virtual _void SetResName( const WStringObj& name ) PURE;
	//!	Get the resource name.
	//!	@param		none.
	//!	@return		The resource name.
	virtual const WStringObj& GetResName( ) const PURE;

	//! Load resources from loader.
	//!	@remark		We should not call this interface actively, it's only for resource loader to call.
	//! @param		stream_reader		The stream reader.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool LoadResourcesFromLoader( IStreamReader* stream_reader ) PURE;
	//! Load resources from loader in main thread.
	//!	@remark		We should not call this interface actively, it's only for resource loader to call.
	//! @param		stream_reader		The stream reader.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool LoadResourcesFromLoaderInMainThread( ) PURE;
	//! Unload resources.
	//!	@remark		We should not call this interface actively, it's only for resource loader to call.
	//! @param		default_res_obj		The default resource object.
	//! @return		none.
	virtual _void UnloadResourcesFromLoader( IResObject* default_res_obj ) PURE;

	//! Load resources.
	//! @param		none.
	//! @return		The load result.
	virtual _void LoadResources( ) PURE;
	//! Unload resources.
	//! @param		none.
	//! @return		none.
	virtual _void UnloadResources( ) PURE;

	//! Check whether all resources are loaded.
	//! @param		none.
	//! @return		True indicates all resources are loaded.
	virtual _ubool AreAllResourcesLoaded( ) const PURE;
	//!	Get the resources loaded progression [0.0, 1.0].
	//!	@param		none.
	//!	@return		The range of loaded progression resources, range is [Loaded resources number, Total resources number].
	virtual DwordRange GetResourcesLoadedProgression( ) const PURE;

	//!	Export properties to file.
	//!	@param		filename	The file name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToFile( WStringPtr filename ) const PURE;
	//!	Export properties to file.
	//!	@param		filename	The file name.
	//!	@param		root_name	The root name.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToFile( WStringPtr filename, WStringPtr root_name ) const PURE;
	//!	Export properties to XML string.
	//!	@param		xml_string	The XML string.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToXMLString( WString& xml_string ) const PURE;
	//!	Export properties to XML string.
	//!	@param		root_name	The root name.
	//!	@param		xml_string	The XML string.
	//!	@return		True indicates successful, otherwise indicates failure.
	virtual _ubool ExportToXMLString( WStringPtr root_name, WString& xml_string ) const PURE;
};

}