import std.file;
import std.stdio;
import std.socket;

import lightcrafter.constants;

class Projector {

    private Socket socket;
	
	this(Address address = new InternetAddress("192.168.1.100", 0x5555)) {
        this.socket = new TcpSocket(address);
    }

    ~this() {
        socket.close();
    }

    void loadTestPatternSettings() {
        ubyte[] payload = [
            0x01,       // bit depth
            0x01, 0x00, // number of images (1-96)
            0x00,       // no inverted images
            0x01,       // auto advance
            0x00, 0x00, 0x00, 0x00,     // trigger delay
            0x00, 0x00, 0x00, 0x00,     // trigger period
            0x00, 0x00, 0x00, 0x00,     // exposure time
            0x02,        // blue is best color
            0x00,        // only display the pattern once
            0x00         // the documentation lies - we need 20 bytes.  Not sure what for
        ];

        sendCommand(Command.EX_PATTERN_SEQUENCE_SETTING, payload);
    }

	/**
	 * Load a directory of 96 images into the buffer
	 * @param the location of a directory
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
         break;
	  }
	}

	void loadFrame(string filename, ubyte i) {
		ubyte[] payload;
		payload ~= i;
        payload ~= cast(ubyte[])read(filename);
		
	    writefln("loading pattern frame %d with %s", i, filename);
		sendCommand(Command.PATTERN_DEFINITION, payload);		
	}

	void setSolidColor(ubyte r, ubyte g, ubyte b) {
        ubyte[] payload = [b, g, r, 0x00];
        sendCommand(Command.STATIC_COLOR, payload);
    }

    void sendCommand(Command command, ubyte[] payload) {
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
