
import std.stdio;
import core.thread;

import lightcrafter.projector;
import lightcrafter.constants;


void usage() {
    writeln("usage: patternsend <pattern folder>");
    writeln("\tSends all the images in a folder as a pattern to a lightcrafter");
    writeln("\tprojector.  Images should be in bmp format and numbered in order");
}


int main(string[] args) {
    // Check the arguments for a folder name
    if (args.length < 2) {
        usage();
        return 1;
    }

    // Connect to the projector and load the patten settings
    Projector lightcrafter = new Projector();
    writeln("connected to projector");

    lightcrafter.loadTestPatternSettings();
    writeln("settings loaded");

    // Load the requested sequence into the projector
    writeln("sending pattern sequence");
    lightcrafter.loadImages(args[1]);

    // Show the pattern
    writeln("showing pattern sequence");
    lightcrafter.setDisplayMode(DisplayMode.PATTERN_SEQUENCE);
    lightcrafter.start();

    Thread.sleep(dur!("msecs")(400));

    lightcrafter.close();

    return 0;
}
