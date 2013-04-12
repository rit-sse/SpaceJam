import std.stdio;
import std.socket;

import lightcrafter;
import std.file;


class Lightcrafter {

    private Socket socket;

    this(Address address = new InternetAddress("192.168.1.100", 0x5555)) {
        this.socket = new TcpSocket(address);
    }

    ~this() {
        socket.close();
    }
	  
    /**
	 * set the color of the LightCrafter to the given rgb color value
	 * @param r the red component
	 * @param g the green component
	 * @param b the blue component 
	 */
    void setSolidColor(ubyte r, ubyte g, ubyte b) {
        Packet packet;
        packet.packetType = PacketType.WRITE_COMMAND;
        packet.command = Command.STATIC_COLOR;
        packet.flags = CommandFlag.PAYLOAD_COMPLETE_DATA;

        packet.payloadLength = 4;
        packet.payload ~= b;
        packet.payload ~= g;
        packet.payload ~= r;
        packet.payload ~= 0x00;

        sendPacket(packet);
    }

    /**
	 * Set the display mode of the lightcrafter to the
	 * given mode
     * @see section 3.5 in the lightcrafter document
	 *
	 */
	void setDisplayMode(DisplayMode mode){
		 Packet p;
		 p.packetType = PacketType.WRITE_COMMAND;
		 p.command = Command.CURRENT_DISPLAY_MODE;
		 p.flags = CommandFlag.PAYLOAD_COMPLETE_DATA;
		 
		 p.payload = [ mode ];;
		 sendPacket( p  );
		  
	}

    /**
	 * send an image file to the buffer
	 * @param imageFileName the name of the image file (or 
	 *  absolute path)
	 */
	static void sendImageToBuffer(char[] imageFileName){
	    
		// this doesn't take into account maxiumum size, but since
		// we're only expecting one bit images, we can safely(?) 
		// ignore it
		
	    // TODO make sure the file exists before attempting a read
		ubyte[] contents = cast(ubyte[])read( imageFileName );
	    //contents = contents.reverse;   // should we be reversing the payload?
		
		Packet packet;
		packet.packetType = PacketType.WRITE_COMMAND;
	    packet.command =  Command.STATIC_IMAGE;
		packet.payload = contents;
	    packet.payloadLength = cast(ushort)contents.length; // same issue with size, we might get overflow
	    
	    // sendPacket( packet ); 
	}
	  
	   
    void sendPacket(Packet packet) {
        uint packetSize = packet.payloadLength + 7;
        ubyte[] data;
        data.length = packetSize;

        // Create the header
        data[0] = packet.packetType;
        data[1] = (packet.command & 0xff00) >> 8;
        data[2] = packet.command & 0x00ff;
        data[3] = packet.flags;
        data[4] = cast(ubyte)packet.payloadLength;
        data[5] = 0x00;

        // Add the payload
        for (int i = 0; i < packet.payloadLength; i++) {
            data[i + 6] = packet.payload[i];
        }

        // Compute the checksum
        ubyte checksum = 0;
        for (int i = 0; i < packetSize - 1; i++) {
            checksum += data[i];
        }
        data[packetSize - 1] = checksum % 0x100;

        // Send the packet
        this.socket.send(data);
    }

	void setImageMode() {

	}

}

unittest {
    Lightcrafter.sendImageToBuffer( cast(char[])"sample.bmp" );
	
	 auto lightcrafter = new Lightcrafter();
     // lightcrafter.setSolidColor(0xff, 0x00, 0xff);
   

    lightcrafter.setImageMode( );
	writefln("done");
}
