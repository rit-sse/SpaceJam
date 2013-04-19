import std.stdio;
import std.string;
import std.regex;
import std.conv;

import lightcrafter.projector;
import lightcrafter.constants;


void main() {
    char[] input;
    Projector lightcrafter;

    readln(input);
    input = strip(input);

    while (input != "exit") {
        if (match(input, regex("^connect"))) {
            lightcrafter = new Projector();
            writefln("connected");
        } else if (match(input, regex("color [0-9]+ [0-9]+ [0-9]+"))) {
            auto match = match(input, regex("color ([0-9]+) ([0-9]+) ([0-9]+)"));
            auto r = to!ubyte(match.captures[1]);
            auto g = to!ubyte(match.captures[2]);
            auto b = to!ubyte(match.captures[3]);

            writefln( "setting the color to %d %d %d", r, g, b);
            lightcrafter.setSolidColor(r, g, b);
        } else if (match(input, regex("load sequence (.*)"))) {
            auto match = match( input, regex("load sequence (.*)"));
            auto dir = match.captures[1];

            writefln("load sequence---");
            writefln("loading from %s", dir);
            lightcrafter.loadImages(cast(string)dir);
        } else if (input == "load test settings") {
            lightcrafter.loadTestPatternSettings();
        } else if (input == "show pattern") {
            lightcrafter.setDisplayMode(DisplayMode.PATTERN_SEQUENCE);
        } else if( input == "start"){
			lightcrafter.start();
		} else if( input == "stop" ){
			
			lightcrafter.stop();			
			  
		}else {
            writefln("did not recognize input string");
        }

        stdout.flush();

        readln(input);
        input = strip(input);
    }
}
