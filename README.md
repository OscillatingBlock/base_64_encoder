# Base64 Encoder in C

This project implements a simple **Base64 encoder** in C. It reads a string from the user, converts it into binary, and then encodes it using the Base64 encoding scheme.

---

## 🔧 How It Works

1. **Text to Binary**: Each character from the input string is converted to its 8-bit binary ASCII representation.
2. **Binary to Base64**: The binary stream is grouped into 24-bit chunks, each split into 6-bit segments.
3. **Encoding**: Each 6-bit segment is mapped to a Base64 character using the standard Base64 character set.
4. **Padding**: If the last chunk is smaller than 24 bits, `=` padding is added to make the output length a multiple of 4.

---

## 🧠 Base64 Recap

- Input: 3 bytes (24 bits) → Output: 4 Base64 characters (4 × 6 bits)
- Padding:
  - 1 byte → 2 `=` signs
  - 2 bytes → 1 `=` sign

---

## 📦 Usage

### 🔨 Compile

```bash
gcc -o base64_encoder base64_encoder.c -lm
````

### 🚀 Run

```bash
./base64_encoder
```

### 💬 Example

```text
Enter a string to encode: Hello
Encoded string: SGVsbG8=
```

---

## 📁 Files

* `base64_encoder.c`: The C source code implementing the encoder.
* `README.md`: This file.

---

## 🧪 Test Cases

| Input    | Output     |
| -------- | ---------- |
| `A`      | `QQ==`     |
| `AB`     | `QUI=`     |
| `ABC`    | `QUJD`     |
| `Hello`  | `SGVsbG8=` |
| `foobar` | `Zm9vYmFy` |

---

## 🛠️ Future goals:

* Add support for decoding Base64 strings back to ASCII.
* Handle file input/output for encoding files.
* Implement bitwise operations instead of arrays for memory efficiency.

---
