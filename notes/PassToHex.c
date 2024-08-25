void KeyToHex(const char *ascii_str, char *hex_str) {
    // Ensure the input string is 24 characters long
    if (strlen(ascii_str) != 24) {
        printf("Input string must be exactly 24 characters long.\n");
        return;
    }

    for (int i = 0; i < 24; ++i) {
        // Convert each ASCII character to its hex equivalent
        sprintf(hex_str + (i * 2), "%02x", (unsigned char)ascii_str[i]);
    }

    // Null-terminate the resulting hex string
    hex_str[48] = '\0';
}