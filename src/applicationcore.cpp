#include "applicationcore.h"

ApplicationCore::ApplicationCore(){

}

void ApplicationCore::finishInitObject(){
    
}

void ApplicationCore::setEPDApp(std::unique_ptr<IEPD_app> epdApp){
    m_pEPDApp_ = std::move(epdApp);
}

void ApplicationCore::setPhysicalKey(std::unique_ptr<IPhysicalKey> physicalKey){
    m_pPhysicalKey_ = std::move(physicalKey);
}

void ApplicationCore::setInternalTime(std::unique_ptr<IInternetTime> internalTime){
    m_pInternalTime_ = std::move(internalTime);
}

void ApplicationCore::set4GDTU(std::unique_ptr<I4GDTU> dtu){
    m_p4GDTU_ = std::move(dtu);
}

void ApplicationCore::setTimeBook(std::unique_ptr<ITimeBook> timeBook){
    m_pTimeBook_ = std::move(timeBook);
}

void ApplicationCore::setDatabase(std::unique_ptr<IDatabase> database){
    m_pDatabase_ = std::move(database);
}

