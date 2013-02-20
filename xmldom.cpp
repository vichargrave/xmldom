/*
   xmldom.cpp

   DOM parsing class definitions.

   ------------------------------------------

   Copyright @ 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "xmldom.h"

class XmlDOMErrorHandler : public HandlerBase
{
  public:
    void fatalError(const SAXParseException &exc) {
        printf("Fatal parsing error at line %d\n", (int)exc.getLineNumber());
        exit(-1);
    }
};

XmlDOMParser* domParser;

XmlDOMParser* XmlDOMParser::getInstance()
{
  if (domParser  == NULL) {
        domParser = new XmlDOMParser();
	}
    return domParser;
}

XmlDOMParser::XmlDOMParser() : m_parser(NULL), m_errHandler(NULL)
{
    XMLPlatformUtils::Initialize();
	m_parser = new XercesDOMParser();
    m_errHandler = (ErrorHandler*) new XmlDOMErrorHandler();
    m_parser->setErrorHandler(m_errHandler);
}

XmlDOMParser::~XmlDOMParser()
{
    if (m_parser) {
        delete m_parser;
        delete m_errHandler;
        XMLPlatformUtils::Terminate();
        domParser = NULL;
    }
}

DOMDocument* XmlDOMParser::parse(const char* xmlfile)
{
    if (m_parser == NULL) {
        return NULL;
    }
    m_parser->parse(xmlfile);
    return m_parser->adoptDocument();
}

XmlDOMDocument::XmlDOMDocument(XmlDOMParser* parser, const char* xmlfile) : m_doc(NULL)
{
    m_doc = parser->parse(xmlfile);
}

XmlDOMDocument::~XmlDOMDocument()
{
    if (m_doc) m_doc->release();
}

string XmlDOMDocument::getChildValue(const char* parentTag, int parentIndex, const char* childTag)
{
	XMLCh* temp = XMLString::transcode(parentTag);
	DOMNodeList* list = m_doc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* parent = dynamic_cast<DOMElement*>(list->item(parentIndex));
	DOMElement* child = 
        dynamic_cast<DOMElement*>(parent->getElementsByTagName(XMLString::transcode(childTag))->item(0));
	string value;
	if (child) {
		char* temp2 = XMLString::transcode(child->getTextContent());
		value = temp2;
        XMLString::release(&temp2);
	}
	else {
		value = "";
	}
	return value;
}

string XmlDOMDocument::getAttributeValue(const char* elementTag,  int elementIndex, const char* attributeTag)
{
	XMLCh* temp = XMLString::transcode(elementTag);
	DOMNodeList* list = m_doc->getElementsByTagName(temp);
	XMLString::release(&temp);

	DOMElement* element = dynamic_cast<DOMElement*>(list->item(elementIndex));
	temp = XMLString::transcode(attributeTag);
	char* temp2 = XMLString::transcode(element->getAttribute(temp));

	string value = temp2;
	XMLString::release(&temp);
	XMLString::release(&temp2);
	return value;
}

int XmlDOMDocument::getElementCount(const char* elementTag)
{
	DOMNodeList* list = m_doc->getElementsByTagName(XMLString::transcode(elementTag));
	return (int)list->getLength();
}
