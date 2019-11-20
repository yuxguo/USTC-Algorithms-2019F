def main():
    ascii_char = [chr(x) for x in range(97,123)] + [chr(x) for x in range(65,91)] + [chr(x) for x in range(48,58)]
    ascii_dict = {}
    for i in range(len(ascii_char)):
        ascii_dict[ascii_char[i]] = i
    text = input("input text:\n")
    pattern = input("input pattern:\n")
    base = len(ascii_dict)
    l_pattern = len(pattern)
    l_text = len(text)
    pattern_hash = my_hash(pattern, ascii_dict, l_pattern)
    hash_p = my_hash(pattern, ascii_dict, l_pattern)
    hash_t = my_hash(text, ascii_dict, l_pattern)
    idx = -1
    for i in range(0,l_text):
        if hash_t == hash_p:
            idx = i
            break
        if i+l_pattern >= l_text:
            break
        hash_t = (hash_t - ascii_dict[text[i]]*(base**(l_pattern-1)))*base + ascii_dict[text[i+l_pattern]]
    print(idx+1)
    return 


def my_hash(str, hash_dict, length, prime=997):
    base = len(hash_dict)
    result = 0
    s = str[0:length]
    for x in s:
        result = result * base + hash_dict[x]
    return result

if __name__ == "__main__":
    main()