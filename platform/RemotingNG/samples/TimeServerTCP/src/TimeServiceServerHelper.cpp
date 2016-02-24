//
// TimeServiceServerHelper.cpp
//
// Package: Generated
// Module:  TimeServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "TimeServiceServerHelper.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"
#include "TimeServiceEventDispatcher.h"
#include "TimeServiceSkeleton.h"


namespace Services {


namespace
{
	static Poco::SingletonHolder<TimeServiceServerHelper> shTimeServiceServerHelper;
}


TimeServiceServerHelper::TimeServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("TimeService", new TimeServiceSkeleton);
}


TimeServiceServerHelper::~TimeServiceServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("TimeService", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TimeServiceServerHelper::registerRemoteObject(Poco::AutoPtr<Services::TimeServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return TimeServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<Services::TimeServiceRemoteObject> TimeServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<Services::TimeService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new TimeServiceRemoteObject(oid, pServiceObject);
}


void TimeServiceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<TimeServiceRemoteObject> pRemoteObject = pIdentifiable.cast<TimeServiceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


TimeServiceServerHelper& TimeServiceServerHelper::instance()
{
	return *shTimeServiceServerHelper.get();
}


std::string TimeServiceServerHelper::registerObjectImpl(Poco::AutoPtr<Services::TimeServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void TimeServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Services

