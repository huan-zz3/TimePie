#ifndef APPLICATIONCORE_H
#define APPLICATIONCORE_H

#include "predefine.h"

#include "iepd_app.h"
#include "iphysicalkey.h"
#include "iinternetime.h"
#include "i4gdtu.h"
#include "itimebook.h"
#include "idatabase.h"

#include <iostream>
#include <memory>

class ApplicationCore {
public:
    explicit ApplicationCore();

    void finishInitObject();

    void setEPDApp(std::unique_ptr<IEPD_app> epdApp);
    void setPhysicalKey(std::unique_ptr<IPhysicalKey> physicalKey);
    void setInternalTime(std::unique_ptr<IInternetTime> internalTime);
    void set4GDTU(std::unique_ptr<I4GDTU> dtu);
    void setTimeBook(std::unique_ptr<ITimeBook> timeBook);
    void setDatabase(std::unique_ptr<IDatabase> database);

private:
    std::unique_ptr<IEPD_app> m_pEPDApp_;
    std::unique_ptr<IPhysicalKey> m_pPhysicalKey_;
    std::unique_ptr<IInternetTime> m_pInternalTime_;
    std::unique_ptr<I4GDTU> m_p4GDTU_;
    std::unique_ptr<ITimeBook> m_pTimeBook_;
    std::unique_ptr<IDatabase> m_pDatabase_;
};


#endif