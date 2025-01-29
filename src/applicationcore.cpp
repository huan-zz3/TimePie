#include "applicationcore.h"

ApplicationCore::ApplicationCore(){

}

void ApplicationCore::finishInitObject(){
    
}

void ApplicationCore::setEPDApp(I_EPD_app* _epdapp){
    m_pEPDApp_ = _epdapp;
}

void ApplicationCore::setPhysicalKey(IPhysicalKey* _physicalkey){
    m_pPhysicalKey_ = _physicalkey;
}

void ApplicationCore::setInternalTime(IInternetTime* _internaltime){
    m_pInternalTime_ = _internaltime;
}

void ApplicationCore::set4GDTU(I4GDTU* _4gdtu){
    m_p4GDTU_ = _4gdtu;
}

void ApplicationCore::setTimeBook(ITimeBook* _timebook){
    m_pTimeBook_ = _timebook;
}

void ApplicationCore::setDatabase(IDatabase* _database){
    m_pDatabase_ = _database;
}