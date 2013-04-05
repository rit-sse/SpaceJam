
enum PacketType : ubyte {
    SYSTEM_BUSY                 = 0x00,
    ERROR                       = 0x01,
    WRITE_COMMAND               = 0x02,
    WRITE_RESPONSE              = 0x03,
    READ_COMMAND                = 0x04,
    READ_RESPONSE               = 0x05
}

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

enum CommandFlag : ubyte {
    PAYLOAD_COMPLETE_DATA       = 0x00,
    PAYLOAD_START_DATA          = 0x01,
    PAYLOAD_INTERMEDIATE_DATA   = 0x02,
    PAYLOAD_END_DATA            = 0x03
}

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

struct Packet {
    PacketType packetType;
    ubyte[2] command;
    ubyte flags;
    ushort payloadLength;
    ubyte[] payload;
    ubyte checksum;
}
