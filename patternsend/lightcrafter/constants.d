/**
 * Defines the type of packet
 */
enum PacketType : ubyte {
    SYSTEM_BUSY                 = 0x00,
    ERROR                       = 0x01,
    WRITE_COMMAND               = 0x02,
    WRITE_RESPONSE              = 0x03,
    READ_COMMAND                = 0x04,
    READ_RESPONSE               = 0x05
}


/**
 * Error codes used in error packets
 */
enum ErrorCode : ubyte {
    UNKNOWN_ERROR               = 0x01,	
	INVALID_COMMAND             = 0x02,
    INVALID_PARAMETER           = 0x03,
    OUT_OF_MEMORY               = 0x04,
    DEVICE_FAILURE              = 0x05,
    SYSTEM_BUSY                 = 0x06,
    NOT_INITIALIZED             = 0x07,
    OBJECT_NOT_FOUND            = 0x08,
    CHECKSUM_ERROR              = 0x09,
    INCORRECT_PACKET_SIZE       = 0x0a,
    INCORRECT_CONTINUATION_FLAG = 0x0b
}


/**
 * Command flags are used when data spans
 * multiple packets
 */
enum CommandFlag : ubyte {
    PAYLOAD_COMPLETE_DATA       = 0x00,
    PAYLOAD_START_DATA          = 0x01,
    PAYLOAD_INTERMEDIATE_DATA   = 0x02,
    PAYLOAD_END_DATA            = 0x03
}


/**
 * defines the difference commands
 */
enum Command : ushort {
    VERSION_STRING              = 0x0100,
    CURRENT_DISPLAY_MODE        = 0x0101,
    CURRENT_TEST_PATTERN        = 0x0103,
    LED_CURRENT_SETTING         = 0x0104,
    STATIC_IMAGE                = 0x0105,
    STATIC_COLOR                = 0x0106,
    DISPLAY_SETTING             = 0x0107,

    VIDEO_INPUT_SETTING         = 0x0200,
    VIDEO_MODE_SETTING          = 0x0201,

    PATTERN_SEQUENCE_SETTING    = 0x0400,
    PATTERN_DEFINITION          = 0x0401,
    START_PATTERN_SEQUENCE      = 0x0402,
    ADVANCE_PATTERN_SEQUENCE    = 0x0403,
    TRIGGER_OUTPUT_SETTING      = 0x0404,
    DISPLAY_PATTERN             = 0x0405,
    EX_PATTERN_SEQUENCE_SETTING = 0x0480,
    EX_PATTERN_DEFINITION       = 0x0481,

    CAMERA_CAPTURE              = 0x0500,

    SAVE_READ_SOLUTION          = 0x0600,
    MANAGE_SOLUTION             = 0x0601,

    INSTALLATION_FILE           = 0x0700,

    SET_IP_ADDRESS              = 0x0800,

    DLPC300_REGISTER            = 0xff00
}

/**
 * Display modes
 */
enum DisplayMode : ubyte {
    STATIC_IMAGE                = 0x00,
    INTERNAL_TEST_PATTERN       = 0x01,
    HDMI_VIDEO                  = 0x02,
    // Reserverd                = 0x03,
    PATTERN_SEQUENCE            = 0x04
}

// enum InternalTestPattern

enum TriggerType : ubyte {
    COMMAND                     = 0x00,
    AUTO                        = 0x01,
    EXTERNAL_POSITIVE           = 0x02,
    EXTERNAL_NEGATIVE           = 0x03,
    CAMERA_POSITIVE             = 0x04,
    CAMERA_NEGATIVE             = 0x05,
    EXTERNAL_WITH_EXPOSURE      = 0x06
}


struct PatternSequenceSetting {
    ubyte bitDepth;
    ubyte numPatterns;
    ubyte includeInvertedPatterns;
    TriggerType inputTriggerType;
    ubyte[4] triggerDelay;
    ubyte[4] triggerPeriod;
    ubyte[4] exposureTime;
    ubyte ledSelect;
}

