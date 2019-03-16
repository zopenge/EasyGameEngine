#pragma once

namespace EGE
{

class ISMSResultCallback : public IObject
{
public:
	virtual void OnResult(_ubool success) PURE;
};

class ISMSManager : public IObject
{
public:
	virtual void SendSMS(WStringPtr phoneNumber, WStringPtr text, ISMSResultCallback* cb) PURE;
};

}