#ifndef __XML_VALIDATOR_H__
#define __XML_VALIDATOR_H__
// The following code was found at
// https://sivachandranp.wordpress.com/2010/10/10/xml-schema-validation-using-xerces-c/
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <iostream>
#include <stdio.h>
#include <string>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/validators/common/Grammar.hpp>

XERCES_CPP_NAMESPACE_USE

///
/// display errors to terminal when validating
///
/// Note: this should be sent to a log file instead of a terminal
///
class ParserErrorHandler : public ErrorHandler {
private:
  void reportParseException(const SAXParseException &ex) {
    char *msg = XMLString::transcode(ex.getMessage());

    std::cout << "at line " << ex.getColumnNumber() << " column "
              << ex.getColumnNumber() << ", " << msg << std::endl;

    XMLString::release(&msg);
  }

public:
  void warning(const SAXParseException &ex) { reportParseException(ex); }

  void error(const SAXParseException &ex) { reportParseException(ex); }

  void fatalError(const SAXParseException &ex) { reportParseException(ex); }

  void resetErrors() {}
};

///
/// The XmlValidator is a utility class to validate xml based on the configured
/// XML schema.
///
class XmlValidator {
public:
  XmlValidator(const std::string &xsd_path);
  ~XmlValidator();
  bool ValidateXml(const std::string &xml_str);

private:
  XercesDOMParser *dom_parser_;
  ParserErrorHandler *parser_error_handler_;
  const char *schema_location_;
};

#endif // __XML_VALIDATOR_H__
