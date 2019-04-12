#pragma once

namespace EGE {

class GarbageCollector : public TObject<IGarbageCollector> {
private:
	typedef TObject<IGarbageCollector> BaseClass;

private:
	typedef Queue<IObject*> GCObjectQueue;

private:
	//!	True indicates it's self releasing ( to skip GC manager )
	_ubool mIsReleasing;
	//!	True indicates enable
	_ubool mIsEnable;

	//!	The thread locker
	Lock mLock;

	//!	The cleanup max time
	_dword mCleanupMaxTime;

	//!	The GC objects
	GCObjectQueue mGCObjects;

public:
	GarbageCollector();
	virtual ~GarbageCollector();

	// IObject Interface
public:
	virtual _void Tick(_dword limited_elapse, _dword elapse) override;

	virtual _dword Release() override;

	// IGarbageCollector Interface
public:
	virtual _void Enable(_ubool enable) override;
	virtual _ubool IsEnabled() const override;

	virtual _void Cleanup(_dword timeout) override;
	virtual _void SetCleanupMaxTime(_dword time) override;

	virtual _void AddObject(IObject* object) override;
};

} // namespace EGE