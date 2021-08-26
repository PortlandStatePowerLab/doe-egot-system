#include <iostream>
#include <sstream>
#include "include/xml/xml_validator.hpp"

XmlValidator::XmlValidator(const std::string &xsd_path)
{
    std::string xsd_loc = "urn:ieee:std:2030.5:ns " + xsd_path;
    schema_location_ = xsd_loc.c_str();

    XMLPlatformUtils::Initialize();
    dom_parser_ = new XercesDOMParser();

    parser_error_handler_ = new ParserErrorHandler();
    dom_parser_->setErrorHandler(parser_error_handler_);
    dom_parser_->setValidationScheme(XercesDOMParser::Val_Always);
    dom_parser_->setExternalSchemaLocation(schema_location_); // this is required as the schema isn't avaiable from external source
    dom_parser_->setDoNamespaces(true);
    dom_parser_->setDoSchema(true);
    dom_parser_->setIgnoreAnnotations(true);
};

XmlValidator::~XmlValidator()
{
    delete parser_error_handler_;
    delete dom_parser_;
    XMLPlatformUtils::Terminate();
};

bool XmlValidator::ValidateXml(const std::string &xml_str)
{
    xercesc::MemBufInputSource *xml_buff = new MemBufInputSource(
        (const XMLByte *)xml_str.c_str(), strlen(xml_str.c_str()), "test", false);

    dom_parser_->parse(*xml_buff);
    if (dom_parser_->getErrorCount() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
};