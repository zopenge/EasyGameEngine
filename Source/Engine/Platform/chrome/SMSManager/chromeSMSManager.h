#pragma once

namespace EGE
{

class chromeSMSManager : public TObject< ISMSManager >
{
public:
	virtual void SendSMS(WStringPtr phoneNumber, WStringPtr text, ISMSResultCallback* cb) override;
};

}