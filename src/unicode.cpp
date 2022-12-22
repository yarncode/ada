#include <set>

namespace ada::unicode {

  // A forbidden host code point is U+0000 NULL, U+0009 TAB, U+000A LF, U+000D CR, U+0020 SPACE, U+0023 (#),
  // U+002F (/), U+003A (:), U+003C (<), U+003E (>), U+003F (?), U+0040 (@), U+005B ([), U+005C (\), U+005D (]),
  // U+005E (^), or U+007C (|).
  static const std::set<char> FORBIDDEN_HOST_CODE_POINTS {
    '\u0000', '\u0009', '\u000A', '\u000D', ' ', '#', '/', ':', '<', '>', '?', '@', '[', '\\', ']', '^', '|'
  };

  bool is_in_code_points(char value, std::set<char> code_points) {
    return code_points.find(value) != code_points.end();
  }

  // An ASCII upper alpha is a code point in the range U+0041 (A) to U+005A (Z), inclusive.
  bool is_ascii_upper_alpha(const char c) {
    return c >= 'A' && c <= 'Z';
  }

  // An ASCII lower alpha is a code point in the range U+0061 (a) to U+007A (z), inclusive.
  bool is_ascii_lower_alpha(const char c) {
    return c >= 'a' && c <= 'z';
  }

  // An ASCII alpha is an ASCII upper alpha or ASCII lower alpha.
  bool is_ascii_alpha(const char c) {
    return is_ascii_upper_alpha(c) || is_ascii_lower_alpha(c);
  }

  // An ASCII digit is a code point in the range U+0030 (0) to U+0039 (9), inclusive.
  bool is_ascii_digit(const char c) {
    return c >= '0' && c <= '9';
  }

  // An ASCII upper hex digit is an ASCII digit or a code point in the range U+0041 (A) to U+0046 (F), inclusive.
  bool is_ascii_upper_hex_digit(const char c) {
    return is_ascii_digit(c) || (c >= 'A' && c <= 'F');
  }

  // An ASCII lower hex digit is an ASCII digit or a code point in the range U+0061 (a) to U+0066 (f), inclusive.
  bool is_ascii_lower_hex_digit(const char c) {
    return is_ascii_digit(c) || (c >= 'a' && c<= 'f');
  }

  // An ASCII hex digit is an ASCII upper hex digit or ASCII lower hex digit.
  bool is_ascii_hex_digit(const char c) {
    return is_ascii_upper_hex_digit(c) || is_ascii_lower_hex_digit(c);
  }

  // An ASCII alphanumeric is an ASCII digit or ASCII alpha.
  bool is_ascii_alphanumeric(const char c) {
    return is_ascii_digit(c) || is_ascii_alpha(c);
  }

  // A C0 control or space is a C0 control or U+0020 SPACE.
  // A C0 control is a code point in the range U+0000 NULL to U+001F INFORMATION SEPARATOR ONE, inclusive.
  bool is_c0_control_or_space(const char c) {
    return (unsigned char) c <= ' ';
  }

  // An ASCII tab or newline is U+0009 TAB, U+000A LF, or U+000D CR.
  bool is_ascii_tab_or_newline(const char c) {
    return c == '\t' || c == '\n' || c == '\r';
  }

  unsigned convert_hex_to_binary(const char c) {
    if (c >= '0' && c <= '9')
      return c - '0';
    if (c >= 'A' && c <= 'F')
      return 10 + (c - 'A');
    if (c >= 'a' && c <= 'f')
      return 10 + (c - 'a');
  }

  /**
   * Taken from Node.js
   * https://github.com/nodejs/node/blob/main/src/node_url.cc#L245
   *
   * @see https://encoding.spec.whatwg.org/#utf-8-decode-without-bom
   */
  std::string utf8_decode_without_bom(const std::string_view input) {
    std::string output;

    if (input.empty()) {
      return "";
    }

    output.reserve(input.length());

    for (auto pointer = input.begin(); pointer < input.end(); pointer++) {
      size_t remaining = std::distance(pointer, input.end());

      if (*pointer != '%' || remaining < 2 ||
          (*pointer == '%' &&
           (!is_ascii_hex_digit(pointer[1]) ||
            !is_ascii_hex_digit(pointer[2])))) {
        output += *pointer;
        pointer++;
        continue;
      }

      unsigned a = convert_hex_to_binary(pointer[1]);
      unsigned b = convert_hex_to_binary(pointer[2]);
      output += static_cast<char>(a * 16 + b);
      pointer += 3;
    }

    return output;
  }

  std::string utf8_percent_encode(const std::string_view input, const uint8_t character_set[]) {
    // TODO: Implement this.
    return "";
  }

} // namespace ada::unicode
