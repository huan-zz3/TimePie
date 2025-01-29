#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include "predefine.h"

#include "iepd_app.h"
#include "iphysicalkey.h"
#include "iinternetime.h"
#include "i4gdtu.h"
#include "itimebook.h"
#include "idatabase.h"

class ApplicationCore
{
public:
    explicit ApplicationCore();
    void finishInitObject();

    void setEPDApp(I_EPD_app*);
    void setPhysicalKey(IPhysicalKey*);
    void setInternalTime(IInternetTime*);
    void set4GDTU(I4GDTU*);
    void setTimeBook(ITimeBook*);
    void setDatabase(IDatabase*);

private:
    I_EPD_app* m_pEPDApp_;
    IPhysicalKey* m_pPhysicalKey_;
    IInternetTime* m_pInternalTime_;
    I4GDTU* m_p4GDTU_;
    ITimeBook* m_pTimeBook_;
    IDatabase* m_pDatabase_;


};

#endif