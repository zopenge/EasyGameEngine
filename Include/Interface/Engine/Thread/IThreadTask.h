#pragma once

namespace EGE {

/// <summary>
/// The thread task interface.
/// </summary>
class IThreadTask : public ITask {
public:
	//!	When process the task in thread.
	//!	@param		threadid	The thread ID.
	//!	@param		err_id		The error ID, 0 indicates no error occurred.
	//! @return		True indicates finished or some error occurred, false indicates keep and run it on the next time.
	virtual _ubool OnProcess(_thread_id threadid, _dword& err_id) PURE;
};

} // namespace EGE