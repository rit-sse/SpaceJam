import std.file;
import std.stdio;
import std.socket;

import lightcrafter.constants;



/**
 * A class that interfaces with the lightcrafter
 */
class Projector {

    private Socket socket;
	  
    /**
	 * Create a new Projector
	 *
	 * address = the address of the lightcrafter, defaults to 192.168.1.100 (the 
	 * hardcoded default)
	 */	
	this(Address address = new InternetAddress("192.168.1.100", 0x5555)) {
        this.socket = new TcpSocket(address);
    }
   

    /**
	 * desctructor
	 *
	 * closes the socket connection
	 */
    ~this() {
        socket.close();
    }

   
    /**
	 * tell the lightcrafter to start the pattern sequence
	 * 
	 */
	void start(){
	  sendCommand( Command.START_PATTERN_SEQUENCE, [0x1] );  
	}

   
    /**
	 * tell the lightcrafter to stop the pattern sequence
	 */
	void stop(){
	  sendCommand( Command.START_PATTERN_SEQUENCE, [0x0] );
	}
  
    
	/**
	 * Set the projector to a specific display mode
	 *
	 * params:
	 * mode = the display mode, options are STATIC_IMAGE, 
	 * STATIC_COLOR, HDMI_VIDEO, or PATTERN_SEQUENCE
	 */
	void setDisplayMode(DisplayMode mode) {
        ubyte[] payload;
        payload ~= mode;

        sendCommand(Command.CURRENT_DISPLAY_MODE, payload);
    }

     
	void loadTestPatternSettings() {
        ubyte[] payload = [
            0x01,       // bit depth
            0x60, 0x00, // number of images (1-96)
            0x00,       // no inverted images
            0x01,       // auto advance
            0x00, 0x00, 0x00, 0x00,     // trigger delay
            0x00, 0x00, 0x00, 0x00,     // trigger period
            0x00, 0x00, 0x00, 0x00,     // exposure time
            0x02,        // blue is best color
            0x01,        // display the pattern in a loop
            0x00         // the documentation lies - we need 20 bytes.  Not sure what for
        ];

        sendCommand(Command.EX_PATTERN_SEQUENCE_SETTING, payload);
    }

	/**
	 * Load a directory of 96 images into the buffer
	 *
	 * The directory should contain 96 .bmp files
	 *
	 * note:
	 * the display mode has to be reset after images are loaded into the buffer, 
	 * do this by calling start()
	 * 
	 * params:
	 * directory = the location of a directory
	 */
    void loadImages(string directory) {
	  auto dirListing = dirEntries(directory, "*.bmp", SpanMode.shallow);
	  writefln("got a directory listing...");

      ubyte curImage = 0;
	  foreach (DirEntry d; dirListing) {
		 auto filename = d.name();
		 writefln("got an image: %s", filename);

		 loadFrame(filename, curImage);
         curImage++;
	  }





	}

	
    /** 
	 * load a single frame into the buffer
	 *
	 * params:
	 * filename = the filename (or file location) of the image to load
	 * i = the location in the image buffer
	 */	
	private void loadFrame(string filename, ubyte i) {
		ubyte[] payload;
		payload ~= i;
        payload ~= cast(ubyte[])read(filename);
		
	    writefln("loading pattern frame %d with %s", i, filename);
		sendCommand(Command.PATTERN_DEFINITION, payload);		
	}

   
   
    void setPositiveTrigger(){
		 
	  ubyte[] payload = [TriggerType.EXTERNAL_POSITIVE];
	  sendCommand( Command.TRIGGER_OUTPUT_SETTING, payload );
	}
    	
		
	/**
	 * tell this projector to display a solid color
	 *
	 * params:
	 * r = red component
	 * g = green component
	 * b = blue component
	 *
	 */
	void setSolidColor(ubyte r, ubyte g, ubyte b) {
        ubyte[] payload = [b, g, r, 0x00];
        sendCommand(Command.STATIC_COLOR, payload);
    }

    private void sendCommand(Command command, ubyte[] payload) {
        ubyte[] packet;

        // Construct the header
        packet ~= PacketType.WRITE_COMMAND;
        packet ~= (command & 0xff00) >> 8;
        packet ~= (command & 0x00ff);
        packet ~= CommandFlag.PAYLOAD_COMPLETE_DATA;
        //packet ~= (payload.length & 0xff00) >> 8;
        packet ~= (payload.length & 0x00ff);
        packet ~= (payload.length & 0xff00) >> 8;

        // Add the payload
        packet ~= payload;

        // Compute the checksum
        ubyte checksum = 0;
        foreach (ubyte data; packet) {
            checksum += data;
        }
        packet ~= checksum % 0x100;

        // Send the packet
        this.socket.send(packet);
		writefln("send a packet (size %d)", packet.length);
    }


}
