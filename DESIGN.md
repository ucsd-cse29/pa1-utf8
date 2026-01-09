## PA Design Questions

You will answer the following questions in your DESIGN.md file. Answer each of these with a few sentences or paragraphs; don't write a whole essay, but use good writing practice to communicate the essence of the idea. A good response doesn't need to be long, but it needs to have attention to detail and be clear. Examples help!

**Question 1**

Consider these two bytes: `11000001 10000001`

Based on the definition of UTF-8 we used in PA1, what code point does it encode? What are 1-byte, 3-byte, and 4-byte encodings of the same code point? Which of these are valid UTF-8 encodings of this code point? Why are they valid or not valid? (This requires some outside research – "valid" is a technical term here)

Describe how you would write a function that detects if a UTF-8 string has any invalid code points like these.

**Question 2**

Consider a comparison of UTF-8 with the alternate encoding UTF-32 (https://en.wikipedia.org/wiki/UTF-32).

For a string `s` that is n+1 bytes long (n bytes of data with a 1-byte null terminator), `strlen(s)` must be equal to n.

- Is this property true for UTF-8? Explain why or give a counterexample.
- Is this property true for UTF-32? Explain why or give a counterexample.

For a string `s` that is n+1 bytes long (n bytes of data with a 1-byte null terminator) with the n bytes encoding 2c code points (that is, it is even length in terms of unicode characters), there is a valid code point starting at byte `s[n / 2]`.

- Is this property true for UTF-8? Explain why or give a counterexample.
- Is this property true for UTF-32? Explain why or give a counterexample.

_HINT_: Write out the UTF-8 and UTF-32 encoding of a few short strings, including characters in the ASCII range and outside it.
