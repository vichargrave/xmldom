/*
   xmldom.cpp

   DOM parsing class interfaces.

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

#ifndef __xmldom_h__
#define __xmldom_h__

#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/sax/HandlerBase.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <string>

using namespace std;
using namespace xercesc;

class XmlDOMParser
{
    XercesDOMParser* m_parser;
    ErrorHandler*    m_errHandler;

  public:
    ~XmlDOMParser();

    static XmlDOMParser* getInstance();
    DOMDocument* parse(const char* xmlfile);

  private:
    XmlDOMParser();
};

class XmlDOMDocument
{
    DOMDocument* m_doc;

  public:
    XmlDOMDocument(XmlDOMParser* parser, const char* xmlfile);
    ~XmlDOMDocument();

    string getChildValue(const char* elementTag, int elementIndex, const char* fieldTag);
    string getAttributeValue(const char* elementTag,  int elementIndex, const char* attrTag);
    int getChildCount(const char* elementName);

  private:
    XmlDOMDocument();
    XmlDOMDocument(const XmlDOMDocument&);
};

#endif
