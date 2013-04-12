import std.stdio;
import std.string;
import std.regex;
import std.conv;
import patternsend; 


int main(){
  
  char[] input;
  Lightcrafter lightcrafter;  
   
  readln( input );  
  input = strip(input);
  
  while( input != "exit" ){
    

    if( match( input, regex("connect") ) ){
      lightcrafter = new Lightcrafter();
    }

    else if( match(input, regex("color [0-9]+ [0-9]+ [0-9]+") ) ){
      auto match = match( input, regex("color ([0-9]+) ([0-9]+) ([0-9]+)") );
      auto r= to!ubyte( match.captures[1] );  
      auto g = to!ubyte( match.captures[2] );  
      auto b = to!ubyte( match.captures[3] );  
      
      lightcrafter.setSolidColor( r, g, b );
      writefln( "setting the color to %d %d %d", r, g, b);
    }
    
    
    stdout.flush(); 
  
    readln( input );  
    input = strip(input);
  
  }

  return 1;
}
