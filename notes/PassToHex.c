void KeyToHex(const char* ascii_str, char* hex_str) {
    int len = strlen(ascii_str);

    // If the input string is longer than 24 characters, truncate it
    if (len > 24) {
        len = 24;
    }

    // Convert each ASCII character to its hex equivalent
    for (int i = 0; i < len; ++i) {
        sprintf(hex_str + (i * 2), "%02x", (unsigned char)ascii_str[i]);
    }

    // Pad with zeros if the string is shorter than 24 characters
    for (int i = len; i < 24; ++i) {
        sprintf(hex_str + (i * 2), "00");
    }

    // Null-terminate the resulting hex string
    hex_str[48] = '\0';
}