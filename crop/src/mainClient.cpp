/*
 * @brief mainClient.cpp implementation of member functions
 */

#include "Modules/ClientModule.h"

#include "Modules/UniversalDecoder.h"

#include <sstream>
int main()
{
  ClientModule mars;
  mars.execute();


//  UniversalDecoder<Text> decoder;
//  for(unsigned int i = 0; i < 2; ++i )
//    for(unsigned int i = 20; i > 0; --i )
//    {
//      Text* text = new Text;
//      text->line = i;
//      text->text = "wir fahren nach: ";
//      std::stringstream ss;
//      ss << i;
//      text->text.append(ss.str());
//      text->text.append(" heute");
//
//      decoder.decode(((i%2==0)?0:1), i, text);
//    }



  return 0;
}
