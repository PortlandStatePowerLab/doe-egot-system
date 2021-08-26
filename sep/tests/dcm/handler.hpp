#ifndef __HANDLER_H__
#define __HANDLER_H__
#include <iostream>
#include <string>
#include <boost/property_tree/ptree.hpp>

namespace handler
{
  //
  // The Handler interface declares a method for building the chain of handlers.
  // It also declares a method for executing a request.
  //
  class Handler
  {
  public:
    virtual Handler *SetNext(Handler *handler) = 0;
    virtual boost::property_tree::ptree Handle(const boost::property_tree::ptree &pt) = 0;
  };

  //
  // The default chaining behavior can be implemented inside a base handler class.
  //
  class AbstractHandler : public Handler
  {
  public:
    AbstractHandler() : next_handler_(nullptr)
    {
    }

    Handler *SetNext(Handler *handler) override
    {
      this->next_handler_ = handler;
      // Returning a handler from here will let us link handlers in a convenient
      // way like this:
      // $dcap->setNext($edev)->setNext($sdev);
      return handler;
    }

    boost::property_tree::ptree Handle(const boost::property_tree::ptree &pt) override
    {
      if (this->next_handler_)
      {
        return this->next_handler_->Handle(pt);
      }
      std::cout << "Couldn't Handle\n";
      return {};
    }

  private:
    Handler *next_handler_;
  };

  class DeviceCapability : public AbstractHandler
  {
  public:
    boost::property_tree::ptree Handle(const boost::property_tree::ptree &pt) override
    {
      if (pt.begin()->first == "DeviceCapability")
      {
        std::cout << "Handle DeviceCapability\n";
        return pt;
      }
      else
      {
        std::cout << "NOT Handle DeviceCapability\n";
        return AbstractHandler::Handle(pt);
      }
    }
  };

} // namespace handler

#endif // __HANDLER_H__