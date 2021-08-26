#ifndef __XML_VALIDATOR_H__
#define __XML_VALIDATOR_H__
// The following code was found at
// https://sivachandranp.wordpress.com/2010/10/10/xml-schema-validation-using-xerces-c/
#include <stdio.h>
#include <string>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

XERCES_CPP_NAMESPACE_USE

// Display errors to terminal when validating
class ParserErrorHandler : public ErrorHandler
{
private:
    void reportParseException(const SAXParseException &ex)
    {
        char *msg = XMLString::transcode(ex.getMessage());
        fprintf(stderr, "at line %llu column %llu, %s\n",
                ex.getColumnNumber(), ex.getLineNumber(), msg);
        XMLString::release(&msg);
    }

public:
    void warning(const SAXParseException &ex)
    {
        reportParseException(ex);
    }

    void error(const SAXParseException &ex)
    {
        reportParseException(ex);
    }

    void fatalError(const SAXParseException &ex)
    {
        reportParseException(ex);
    }

    void resetErrors()
    {
    }
};

class XmlValidator
{
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