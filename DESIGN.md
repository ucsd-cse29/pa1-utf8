Another encoding of Unicode is UTF-32, which encodes all Unicode code points in 4 bytes. For things like ASCII, the leading 3 bytes are all 0's. What are some tradeoffs between UTF-32 and UTF-8?

UTF-8 uses less bytes to represent the same thing with UTF-32.

UTF-8 has a leading 10 on all the bytes past the first for multi-byte code points. This seems wasteful – if the encoding for 3 bytes were instead 1110XXXX XXXXXXXX XXXXXXXX (where X can be any bit), that would fit 20 bits, which is over a million code points worth of space, removing the need for a 4-byte encoding. What are some tradeoffs or reasons the leading 10 might be useful? Can you think of anything that could go wrong with some programs if the encoding didn't include this restriction on multi-byte code points?

In UTF-8 , if the beginning of the byte is 10, then it means this byte is a continuation byte. This can help people identify the continuation byte and beginning byte. If we don't have the 10 at the beginning of the continuation byte, the computer may didn't read the entire code point correctly.