/*
   main.cpp

   Test application for the DOM parser class.

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

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include "xmldom.h"

int main(int argc, char** argv)
{
    string value;
    XmlDOMParser* parser = XmlDOMParser::getInstance();
    if (parser) {
        XmlDOMDocument* doc = new XmlDOMDocument(parser, "./bookstore.xml");
        if (doc) {
            for (int i = 0; i < doc->getChildCount("book"); i++) {
                printf("Book %d\n", i+1);
                value = doc->getAttributeValue("book", i, "category");
                printf("book category - %s\n", value.c_str());
                value = doc->getChildValue("book", i, "title");
                printf("book title    - %s\n", value.c_str());
                value = doc->getChildValue("book", i, "author");
                printf("book author   - %s\n", value.c_str());
                value = doc->getChildValue("book", i, "year");
                printf("book year     - %s\n", value.c_str());
                value = doc->getChildValue("book", i, "price");
                printf("book price    - %s\n", value.c_str());
            }
            delete doc;
        }
        delete parser;
    }
    exit(0);
}
